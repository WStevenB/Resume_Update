#include "FileWvOut.h"
#include "RtWvOut.h"
#include "RtWvIn.h"
#include "Utilities.h"
#include <cstdlib>



int main( int argc, char *argv[] )
{
   if (argc != 3)
   {
      std::cout << std::endl << "Error - incorrect arguments" << std::endl;
      std::cout << "   Input File = path of the input .wav file" << std::endl;
      std::cout << "   Output File = name of the .wav file to create" << std::endl;
      exit(0);
   }

   stk::Stk::showWarnings(true);
   stk::Stk::setSampleRate(Utilities::SAMPLES_PER_SECOND);

   std::string inputPath = argv[1];
   unsigned int numberSamples = Utilities::SAMPLES_PER_SECOND * 120;
   stk::StkFrames inputSong = Utilities::getData(inputPath, numberSamples, false, true);
   stk::StkFrames channelTwo = inputSong;
   for(unsigned int i = 0; i<channelTwo.frames(); i++) channelTwo[i] = 0;
  
   stk::FileWvOut* output = 0;
   std::string outputFileName = argv[2];
   std::string outputFilePath = "output/" + outputFileName;
   try
   {
      output = new stk::FileWvOut(outputFilePath, 2, stk::FileWrite::FILE_WAV);
   }
   catch (stk::StkError&)
   {
      exit(0);
   }

   stk::RtWvIn* rtInput = 0;
   try
   {
      rtInput = new stk::RtWvIn(1);
   }
   catch (stk::StkError&)
   {
      exit(1);
   }

   stk::RtWvOut* rtOutput = 0;
   try
   {
      rtOutput = new stk::RtWvOut(1, 44100);
   }
   catch (stk::StkError&)
   {
      exit(0);
   }

   for(unsigned int i = 0; i<numberSamples; i++)
   {
      channelTwo[i] = rtInput->tick();
      rtOutput->tick(inputSong[i]);
   }

   Utilities::normalize(channelTwo);

   for(unsigned int i = 0; i<numberSamples; i++) output->stereoTick(inputSong[i], channelTwo[i]);

   delete output;
   delete rtOutput;
   delete rtInput;
}
