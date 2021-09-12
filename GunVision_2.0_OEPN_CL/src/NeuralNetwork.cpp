#include "NeuralNetwork.h"


NeuralNetwork::NeuralNetwork() {

   loadInputSource_ = "";
   inputToHiddenSource_ = "";
   hiddenToOutputSource_ = "";

   loadInputKernel_ = NULL;
   inputToHiddenKernel_ = NULL;
   hiddenToOutputKernel_ = NULL;
}


NeuralNetwork::~NeuralNetwork() {

}


void NeuralNetwork::setSourceCode() {

   // prepare input layer of neural network using area of original frame where gun was detected
   // reduce the size of this area from 190x135 (size of gun template) to 63x45 using blur filter
   // recenter pixel values from 0:255 to -5:5 and then perform sigmoid function
   // bias of 0.65 is used on last value of input layer
   loadInputSource_ =
   "__kernel void net_start(__global unsigned char* raw_frame, __global unsigned char* background, __global float* net_input_layer, __global int* gunTotals) {"\
      "size_t i = get_global_id(0);"\
      "if(i == 2835) { net_input_layer[8505] = 0.65f; }"\
      "else {"\
         "unsigned int netLoc = i*3;"\
         "unsigned int x = ((i%63) * 3) + 1;"\
         "unsigned int y = ((i/63) * 3) + 1;"\
         "float totalRed = 0.0f;"\
         "float totalBlue = 0.0f;"\
         "float totalGreen = 0.0f;"\

         "for(int xx = -1; xx<2; xx++) {"\
            "for(int yy = -1; yy<2; yy++) {"\

               "int xxx = x+xx+gunTotals[1];"\
               "int yyy = y+yy+gunTotals[2];"\
               "int subtractionLoc = (yyy*" + __WIDTH__ + ") + xxx;"\

               "if(background[subtractionLoc] == 0) {"\
                  "totalRed += 255.0f;"\
                  "totalBlue += 255.0f;"\
                  "totalGreen += 255.0f;"\
               "}"\
               "else {"\
                  "int rawLoc = subtractionLoc * 3;"\
                  "totalRed += (float)raw_frame[rawLoc];"\
                  "totalBlue += (float)raw_frame[rawLoc+1];"\
                  "totalGreen += (float)raw_frame[rawLoc+2];"\
               "}"\
            "}"\
         "}"\
         "net_input_layer[netLoc] = 1.0f / ( 1.0f + exp( -1.0f * ((totalRed/9.0f) * (10.0f/255.0f) - 5.0f)));"\
         "net_input_layer[netLoc+1] = 1.0f / ( 1.0f + exp( -1.0f * ((totalBlue/9.0f) * (10.0f/255.0f) - 5.0f)));"\
         "net_input_layer[netLoc+2] = 1.0f / ( 1.0f + exp( -1.0f * ((totalGreen/9.0f) * (10.0f/255.0f) - 5.0f)));"\
      "}"\
   "}";


   // matrix multiplication of input layer x weights to hidden layer
   // open cl programs run per value of hidden layer
   inputToHiddenSource_ =
   "__kernel void net_hidden(__global float* input, __global float* weights, __global float* hidden) {"\
      "size_t i = get_global_id(0);"\
      "if(i == 1500) { hidden[i] = 0.65f; }"\
      "else {"\
         "float total = 0.0f;"\
         "unsigned int weight_index = i * 8506;"\
         "for(unsigned int ii = 0; ii<8506; ii++) {"\
            "total += weights[weight_index] * input[ii];"\
            "weight_index += 1;"\
         "}"\
         "hidden[i] = 1.0f / (1.0f + exp(-1.0f * total));"\
      "}"\
   "}";


   // matrix multiplication of hidden layer x weights to output layer
   // open cl programs run per value of output layer
   hiddenToOutputSource_ =
   "__kernel void net_output(__global float* hidden, __global float* weights, __global float* output) {"\
      "float total = 0.0f;"\
      "for(unsigned int ii = 0; ii<1501; ii++) {"\
         "total += weights[ii] * hidden[ii];"\
      "}"\
      "output[0] = 1.0f / (1.0f + exp(-1.0f * total));"\
   "}";
}


bool NeuralNetwork::compile() {

   cl_int error;

   const char* loadInputPtr = loadInputSource_.c_str();
   cl_program inputProgram = clCreateProgramWithSource(context_, 1, (const char **) &loadInputPtr, NULL, &error);
   if (clBuildProgram(inputProgram, 0, NULL, NULL, NULL, NULL) != CL_SUCCESS) {
      std::cout << "Error compiling load neural net input" << std::endl;
      return false;
   }
   loadInputKernel_ = clCreateKernel(inputProgram, "net_start", &error);

   const char* hiddenPtr = inputToHiddenSource_.c_str();
   cl_program hiddenProgram = clCreateProgramWithSource(context_, 1, (const char **) &hiddenPtr, NULL, &error);
   if (clBuildProgram(hiddenProgram, 0, NULL, NULL, NULL, NULL) != CL_SUCCESS) {
      std::cout << "Error compiling neural network input to hidden" << std::endl;
      return false;
   }
   inputToHiddenKernel_ = clCreateKernel(hiddenProgram, "net_hidden", &error);

   const char* outputPtr = hiddenToOutputSource_.c_str();
   cl_program outputProgram = clCreateProgramWithSource(context_, 1, (const char **) &outputPtr, NULL, &error);
   if (clBuildProgram(outputProgram, 0, NULL, NULL, NULL, NULL) != CL_SUCCESS) {
      std::cout << "Error compiling neural network hidden to output" << std::endl;
      return false;
   }
   hiddenToOutputKernel_ = clCreateKernel(outputProgram, "net_output", &error);

   return true;
}


// run forward algorithm of pre-trained neural network
void NeuralNetwork::forward(float* outputHost) {

   // prepare input layer
   clSetKernelArg(loadInputKernel_, 0, sizeof(cl_mem), &clNewFrame_);
   clSetKernelArg(loadInputKernel_, 1, sizeof(cl_mem), &clSubtractedFiltered_);
   clSetKernelArg(loadInputKernel_, 2, sizeof(cl_mem), &clNetworkInput_);
   clSetKernelArg(loadInputKernel_, 3, sizeof(cl_mem), &clGunTotals_);

   clEnqueueNDRangeKernel(commandQueue_, loadInputKernel_, 1, NULL, &networkInputPixels_, NULL, 0, NULL, NULL);
   clFinish(commandQueue_);


   // multiply input layer x weights
   clSetKernelArg(inputToHiddenKernel_, 0, sizeof(cl_mem), &clNetworkInput_);
   clSetKernelArg(inputToHiddenKernel_, 1, sizeof(cl_mem), &clWeightsInputHidden_);
   clSetKernelArg(inputToHiddenKernel_, 2, sizeof(cl_mem), &clHiddenLayer_);

   clEnqueueNDRangeKernel(commandQueue_, inputToHiddenKernel_, 1, NULL, &hiddenLayerSize_, NULL, 0, NULL, NULL);
   clFinish(commandQueue_);


   // multiply hidden layer x weights
   clSetKernelArg(hiddenToOutputKernel_, 0, sizeof(cl_mem), &clHiddenLayer_);
   clSetKernelArg(hiddenToOutputKernel_, 1, sizeof(cl_mem), &clWeightsHiddenOutput_);
   clSetKernelArg(hiddenToOutputKernel_, 2, sizeof(cl_mem), &clNetworkOutput_);

   clEnqueueNDRangeKernel(commandQueue_, hiddenToOutputKernel_, 1, NULL, &networkOutputSize_, NULL, 0, NULL, NULL);
   clFinish(commandQueue_);


   // extract output layer from gpu
   clEnqueueReadBuffer(commandQueue_, clNetworkOutput_, CL_TRUE, 0, sizeof(float), outputHost, 0, NULL, NULL);

}




