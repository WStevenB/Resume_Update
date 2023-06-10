#include "FileWvOut.h"
#include "Utilities.h"
#include "SheetMusic.h"
#include "Instrument.h"
#include <cstdlib>



int main( int argc, char *argv[] )
{
   if (argc != 3)
   {
      std::cout << std::endl << "Error - incorrect arguments" << std::endl;
      std::cout << "   Input File = name of the formatted sheet music file" << std::endl;
      std::cout << "   Output File = name of the .wav file to create" << std::endl;
      exit(0);
   }

   stk::Stk::showWarnings(true);
   stk::Stk::setSampleRate(Utilities::SAMPLES_PER_SECOND);

   std::vector<stk::StkFrames> samples;
   Instrument::loadInstruments(samples);

   std::string inputFileName = argv[1];
   std::string inputFilePath = "input/" + inputFileName;
   SheetMusic sheetMusic(inputFilePath, Utilities::SAMPLES_PER_SECOND, samples);

   const double TEMPO_BEATS_PER_MINUTE = sheetMusic.beatsPerMinute_;
   const double SONG_LENGTH_SECONDS = sheetMusic.songLengthSeconds_;

   const double TEMPO_BEATS_PER_SECOND = TEMPO_BEATS_PER_MINUTE / 60;
   const double SAMPLES_PER_BEAT = Utilities::SAMPLES_PER_SECOND / TEMPO_BEATS_PER_SECOND;
   const double SAMPLES_PER_EIGHTH_NOTE = SAMPLES_PER_BEAT / 2;
   const double TOTAL_BEATS_IN_SONG = SONG_LENGTH_SECONDS * TEMPO_BEATS_PER_SECOND;
   const double TOTAL_SAMPLES = Utilities::SAMPLES_PER_SECOND * SONG_LENGTH_SECONDS;
  
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

   stk::StkFrames songFrame(Utilities::SAMPLES_PER_SECOND * SONG_LENGTH_SECONDS, 1);
   for(unsigned int i = 0; i<Utilities::SAMPLES_PER_SECOND * SONG_LENGTH_SECONDS; i++) songFrame[i] = 0;

   sheetMusic.insertData(songFrame);

   Utilities::normalize(songFrame);

   //stk::StkFrames channelTwo(songFrame);
   //Utilities::setGain(channelTwo, 1);

   //for(unsigned int i = 0; i<TOTAL_SAMPLES; i++) output->stereoTick(songFrame[i], channelTwo[i]);

   for(unsigned int i = 0; i<TOTAL_SAMPLES; i++) output->tick(songFrame[i]);


   delete output;
}
