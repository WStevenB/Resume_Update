#ifndef NEURAL_NET_H
#define NEURAL_NET_H


#include "OpenClBuilder.h"


class NeuralNetwork : public OpenClBuilder {

public:

   NeuralNetwork();
   virtual ~NeuralNetwork();

   virtual void setSourceCode();

   virtual bool compile();

   // run forward algorithm of pre-trained neural network
   void forward(float* outputHost);

private:

   std::string loadInputSource_;
   std::string inputToHiddenSource_;
   std::string hiddenToOutputSource_;

   cl_kernel loadInputKernel_;
   cl_kernel inputToHiddenKernel_;
   cl_kernel hiddenToOutputKernel_;
};






#endif //NEURAL_NET_H
