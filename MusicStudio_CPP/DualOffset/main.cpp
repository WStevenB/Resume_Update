#include "FileWvOut.h"
#include "RtWvOut.h"
#include "RtWvIn.h"
#include "Utilities.h"
#include "SheetMusic.h"
#include "Instrument.h"
#include <cstdlib>



int main( int argc, char *argv[] )
{
   if (argc != 4)
   {
      std::cout << std::endl << "Error - incorrect arguments" << std::endl;
      std::cout << "   Input File Path = path to the input .wav file" << std::endl;
      std::cout << "   Output File = name of the output .wav file to create" << std::endl;
      std::cout << "   Track Length = length of input track in seconds" << std::endl;

      exit(0);
   }

   const double SAMPLES_PER_SECOND = 44100;
   const double MICROSECOND_OFFSET = 2.4;
   const double MICROSECONDS_IN_SECOND = 1000000;

   stk::Stk::showWarnings(true);
   stk::Stk::setSampleRate(SAMPLES_PER_SECOND);

   std::string inputFilePath = argv[1];
   std::string trackLengthStr = argv[3];
   float trackLength = std::stof(trackLengthStr);
   float totalInputSamples = trackLength * SAMPLES_PER_SECOND;
   stk::StkFrames inputFrames = Utilities::getData(inputFilePath, totalInputSamples, false, true);

   unsigned int frameOffset = static_cast<unsigned int> (SAMPLES_PER_SECOND *
                                                         SAMPLES_PER_SECOND / MICROSECONDS_IN_SECOND);
   unsigned int totalOffsetFrames = totalInputSamples + frameOffset;

   stk::StkFrames offsetFrames(totalOffsetFrames, 1);

   for(unsigned int i = 0; i<frameOffset; i++) offsetFrames[i] = 0;
   for(unsigned int i = 0; i<totalInputSamples; i++) offsetFrames[i+frameOffset] = inputFrames[i];

   stk::FileWvOut* output = 0;
   std::string outputFileName = argv[2];
   std::string outputFilePath = "output/" + outputFileName;
   try
   {
      output = new stk::FileWvOut(outputFilePath, 1, stk::FileWrite::FILE_WAV);
   }
   catch (stk::StkError&)
   {
      exit(0);
   }

   for(unsigned int i = 0; i<totalOffsetFrames; i++) output->tick(offsetFrames[i]);

   delete output;
}
