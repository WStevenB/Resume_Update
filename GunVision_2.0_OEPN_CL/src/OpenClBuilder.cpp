#include "OpenClBuilder.h"

#include <sstream>

#include "GunTemplate.h"
#include "WeightsInputHidden.h"
#include "WeightsHiddenOutput.h"

cl_context OpenClBuilder::context_ = NULL;
cl_command_queue OpenClBuilder::commandQueue_ = NULL;

cl_mem OpenClBuilder::clRawFrame_ = NULL;
cl_mem OpenClBuilder::clNewFrame_ = NULL;
cl_mem OpenClBuilder::clFlippedFrame_ = NULL;
cl_mem OpenClBuilder::clBackground_ = NULL;
cl_mem OpenClBuilder::clCertainties_ = NULL;
cl_mem OpenClBuilder::clDropFactors_ = NULL;
cl_mem OpenClBuilder::clSubtracted_ = NULL;
cl_mem OpenClBuilder::clSubtractedFiltered_ = NULL;
cl_mem OpenClBuilder::clArmSubtotals_ = NULL;
cl_mem OpenClBuilder::clArmTotals_ = NULL;
cl_mem OpenClBuilder::clGunTemplate_ = NULL;
cl_mem OpenClBuilder::clGunSubtotals_ = NULL;
cl_mem OpenClBuilder::clGunTotals_ = NULL;
cl_mem OpenClBuilder::clWeightsInputHidden_ = NULL;
cl_mem OpenClBuilder::clWeightsHiddenOutput_ = NULL;
cl_mem OpenClBuilder::clNetworkInput_ = NULL;
cl_mem OpenClBuilder::clHiddenLayer_ = NULL;
cl_mem OpenClBuilder::clNetworkOutput_ = NULL;

unsigned long OpenClBuilder::width_ = 0;
unsigned long OpenClBuilder::height_ = 0;
unsigned long OpenClBuilder::pixelSize_ = 0;
unsigned long OpenClBuilder::bufferSize_ = 0;
unsigned long OpenClBuilder::clippedWidth_ = 0;
unsigned long OpenClBuilder::clippedHeight_ = 0;
unsigned long OpenClBuilder::gunSize_ = 0;
unsigned long OpenClBuilder::gunWidth_ = 0;
unsigned long OpenClBuilder::weightsInputHiddenSize_ = 0;
unsigned long OpenClBuilder::weightsHiddenOutputSize_ = 0;
unsigned long OpenClBuilder::networkInputSize_ = 0;
unsigned long OpenClBuilder::networkInputPixels_ = 0;
unsigned long OpenClBuilder::hiddenLayerSize_ = 0;
unsigned long OpenClBuilder::networkOutputSize_ = 0;

std::string OpenClBuilder::__WIDTH__ = "";
std::string OpenClBuilder::__HEIGHT__ = "";
std::string OpenClBuilder::__PIXEL_SIZE__ = "";
std::string OpenClBuilder::__BUFFER_SIZE__ = "";
std::string OpenClBuilder::__CLIPPED_WIDTH__ = "";
std::string OpenClBuilder::__CLIPPED_HEIGHT__ = "";


OpenClBuilder::OpenClBuilder() {

}


OpenClBuilder::~OpenClBuilder() {

}


// set dimensions, performs open cl setup tasks, and creates gpu buffers
bool OpenClBuilder::initialize(unsigned long width, unsigned long height) {

   width_ = width;
   height_ = height;
   pixelSize_ = width_ * height_;
   bufferSize_ = pixelSize_ * 3;
   clippedWidth_ = width_ - 3;
   clippedHeight_ = height_ - 3;

   gunSize_ = 25650; // template width 190 x height 135
   gunWidth_ = 190;
   weightsInputHiddenSize_ = 12767506;
   weightsHiddenOutputSize_ = 1501;
   networkInputSize_ = 8506; // non bias reduced gun template size x 3 plus 1 bias value
   networkInputPixels_ = 2836; // reduced gun template width 63 x height 45 plus 1 bias value
   hiddenLayerSize_ = 1501;
   networkOutputSize_ = 1;

   std::stringstream widthStream;
   widthStream << width_;
   __WIDTH__ = widthStream.str();

   std::stringstream heightStream;
   heightStream << height_;
   __HEIGHT__ = heightStream.str();

   std::stringstream pixelStream;
   pixelStream << pixelSize_;
   __PIXEL_SIZE__ = pixelStream.str();

   std::stringstream bufferStream;
   bufferStream << bufferSize_;
   __BUFFER_SIZE__ = bufferStream.str();

   std::stringstream clippedWidthStream;
   clippedWidthStream << clippedWidth_;
   __CLIPPED_WIDTH__ = clippedWidthStream.str();

   std::stringstream clippedHeightStream;
   clippedHeightStream << clippedHeight_;
   __CLIPPED_HEIGHT__ = clippedHeightStream.str();


   cl_context_properties properties[3];
   cl_uint numberOfPlatforms = 0;
   cl_platform_id platformId;
   cl_device_id deviceId;
   cl_uint numberOfDevices = 0;
   cl_int clError;

   if (clGetPlatformIDs(1, &platformId, &numberOfPlatforms) != CL_SUCCESS) {
      std::cout << "Unable to get platform id" << std::endl;
      return false;
   }

   if (clGetDeviceIDs(platformId, CL_DEVICE_TYPE_GPU, 1, &deviceId, &numberOfDevices) != CL_SUCCESS) {
      std::cout << "Unable to get device id" << std::endl;
      return false;
   }

   properties[0]= CL_CONTEXT_PLATFORM;
   properties[1]= (cl_context_properties) platformId;
   properties[2]= 0;

   context_ = clCreateContext(properties, 1, &deviceId, NULL, NULL, &clError);
   commandQueue_ = clCreateCommandQueue(context_, deviceId, 0, &clError);


   clRawFrame_            = clCreateBuffer(context_, CL_MEM_READ_ONLY,  sizeof(uint8_t) * bufferSize_, NULL, NULL);
   clFlippedFrame_        = clCreateBuffer(context_, CL_MEM_READ_WRITE, sizeof(uint8_t) * bufferSize_, NULL, NULL);
   clBackground_          = clCreateBuffer(context_, CL_MEM_READ_WRITE, sizeof(uint8_t) * bufferSize_, NULL, NULL);
   clCertainties_         = clCreateBuffer(context_, CL_MEM_READ_WRITE, sizeof(int)     * pixelSize_, NULL, NULL);
   clNewFrame_            = clCreateBuffer(context_, CL_MEM_READ_WRITE, sizeof(uint8_t) * bufferSize_, NULL, NULL);
   clSubtracted_          = clCreateBuffer(context_, CL_MEM_READ_WRITE, sizeof(uint8_t) * pixelSize_, NULL, NULL);
   clSubtractedFiltered_  = clCreateBuffer(context_, CL_MEM_READ_WRITE, sizeof(uint8_t) * pixelSize_, NULL, NULL);
   clDropFactors_         = clCreateBuffer(context_, CL_MEM_READ_WRITE, sizeof(uint8_t) * pixelSize_, NULL, NULL);
   clArmSubtotals_        = clCreateBuffer(context_, CL_MEM_READ_WRITE, sizeof(int)     * pixelSize_, NULL, NULL);
   clArmTotals_           = clCreateBuffer(context_, CL_MEM_READ_WRITE, sizeof(int)     * pixelSize_, NULL, NULL);
   clGunTemplate_         = clCreateBuffer(context_, CL_MEM_READ_ONLY,  sizeof(int)     * gunSize_, NULL, NULL);
   clGunSubtotals_        = clCreateBuffer(context_, CL_MEM_READ_WRITE, sizeof(int)     * pixelSize_ * gunWidth_, NULL, NULL);
   clGunTotals_           = clCreateBuffer(context_, CL_MEM_READ_WRITE, sizeof(int)     * pixelSize_, NULL, NULL);
   clWeightsInputHidden_  = clCreateBuffer(context_, CL_MEM_READ_ONLY,  sizeof(float)   * weightsInputHiddenSize_, NULL, NULL);
   clWeightsHiddenOutput_ = clCreateBuffer(context_, CL_MEM_READ_ONLY,  sizeof(float)   * weightsHiddenOutputSize_, NULL, NULL);
   clNetworkInput_        = clCreateBuffer(context_, CL_MEM_READ_WRITE, sizeof(float)   * networkInputSize_, NULL, NULL);
   clHiddenLayer_         = clCreateBuffer(context_, CL_MEM_READ_WRITE, sizeof(float)   * hiddenLayerSize_, NULL, NULL);
   clNetworkOutput_       = clCreateBuffer(context_, CL_MEM_READ_WRITE, sizeof(float)   * networkOutputSize_, NULL, NULL);

   clEnqueueWriteBuffer(commandQueue_, clGunTemplate_, CL_TRUE, 0, sizeof(int) * gunSize_, &gunTemplate[0], 0, NULL, NULL);

   clEnqueueWriteBuffer(commandQueue_, clWeightsInputHidden_, CL_TRUE, 0, sizeof(float) * weightsInputHiddenSize_, &matrix_ih[0], 0, NULL, NULL);
   clEnqueueWriteBuffer(commandQueue_, clWeightsHiddenOutput_, CL_TRUE, 0, sizeof(float) * weightsHiddenOutputSize_, &matrix_ho[0], 0, NULL, NULL);

   return true;
}
