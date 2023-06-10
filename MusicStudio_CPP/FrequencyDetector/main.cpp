#include "FileWvOut.h"
#include "RtWvOut.h"
#include "RtWvIn.h"
#include "Utilities.h"
#include "SheetMusic.h"
#include "Instrument.h"
#include "kiss_fft.h"
#include <cstdlib>
#include <cmath>



int main( int argc, char *argv[] )
{
   if (argc != 2)
   {
      std::cout << std::endl << "Error - incorrect arguments" << std::endl;
      std::cout << "   Input File = name of the file to detect frequency" << std::endl;
      exit(0);
   }

   stk::Stk::showWarnings(true);
   stk::Stk::setSampleRate(Utilities::SAMPLES_PER_SECOND);

   std::string inputFilePath = argv[1];
   stk::StkFrames frames = Utilities::getData(inputFilePath, 100000, false, true);
   Utilities::normalize(frames);

   const double SPIKE_THRESHOLD = 3500;
   const double UNSET_VALUE = -999999;
   const unsigned int START_BUFFER = 0.25 * Utilities::SAMPLES_PER_SECOND;
   const unsigned int DETECT_LENGTH = Utilities::SAMPLES_PER_SECOND;

   if(frames.frames() <= START_BUFFER + DETECT_LENGTH)
   {
      std::cout << "File is too small for detection" << std::endl;
      exit(0);
   }

   // Run Fast Fourier Transform
   kiss_fft_cfg cfg = kiss_fft_alloc(Utilities::SAMPLES_PER_SECOND, 0, 0, 0);

   kiss_fft_cpx cx_in[DETECT_LENGTH];
   kiss_fft_cpx cx_out[DETECT_LENGTH];
   for(unsigned int i = START_BUFFER; i<START_BUFFER+DETECT_LENGTH; i++)
   {
      cx_in[i-START_BUFFER].r = frames[i];
      cx_in[i-START_BUFFER].i = frames[i];

   }
   kiss_fft(cfg, cx_in, cx_out);

   // Find max magnitude and first spike in magnitude
   // Set to first spike if close to max spike because lowest tone is recognized as primary by ear
   double firstSpike = UNSET_VALUE;
   double firstIndex = 0;
   double maxMagnitude = UNSET_VALUE;
   double maxIndex = 0;
   for(unsigned int i = 1; i<DETECT_LENGTH; i++)
   {
      double frequencyMagnitude = std::sqrt (cx_out[i].r * cx_out[i].r + cx_out[i].i * cx_out[i].i);
      if(frequencyMagnitude > maxMagnitude)
      {
         maxMagnitude = frequencyMagnitude;
         maxIndex = i;
      }
      if(frequencyMagnitude > SPIKE_THRESHOLD && firstSpike == UNSET_VALUE)
      {
         firstSpike = frequencyMagnitude;
         firstIndex = i;
      }
   }

   if(firstIndex != 0 && firstSpike > maxMagnitude * 0.6)
   {
      maxMagnitude = firstSpike;
      maxIndex = firstIndex;
   }

   // Analyze right and left values of max magnitude to calculate shift to peak frequency
   double shift = 0;
   if(maxIndex > 10 && maxIndex < Utilities::SAMPLES_PER_SECOND - 10)
   {
      unsigned int r = maxIndex + 1;
      unsigned int l = maxIndex - 1;
      double frequencyMagnitudeRight = std::sqrt (cx_out[r].r * cx_out[r].r + cx_out[r].i * cx_out[r].i);
      double frequencyMagnitudeLeft = std::sqrt (cx_out[l].r * cx_out[l].r + cx_out[l].i * cx_out[l].i);

      if(frequencyMagnitudeRight > frequencyMagnitudeLeft)
      {
         double factor = (0.5) / (maxMagnitude - frequencyMagnitudeLeft);
         shift = (frequencyMagnitudeRight - frequencyMagnitudeLeft) * factor;
         if(shift < 0) shift = 0;
      }
      else
      {
         double factor = (-0.5) / (maxMagnitude - frequencyMagnitudeRight);
         shift = (frequencyMagnitudeLeft - frequencyMagnitudeRight) * factor;
         if(shift > 0) shift = 0;
      }
   }

   double rootFrequency = maxIndex * Utilities::SAMPLES_PER_SECOND / (Utilities::SAMPLES_PER_SECOND);
   rootFrequency += shift;

   std::cout << "Frequency for sound in file " << inputFilePath << std::endl;
   std::cout << rootFrequency << " Hertz" << std::endl;

   return 1;
}
