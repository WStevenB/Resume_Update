#include "FileWvOut.h"
#include "Utilities.h"
#include "SheetMusic.h"
#include "MusicXmlWriter.h"
#include "Instrument.h"
#include <cstdlib>



int main( int argc, char *argv[] )
{
   if (argc != 3)
   {
      std::cout << std::endl << "Error - incorrect arguments" << std::endl;
      std::cout << "   Input File = name of the formatted sheet music file" << std::endl;
      std::cout << "   Output File = name of the .xml file to create" << std::endl;
      exit(0);
   }

   stk::Stk::showWarnings(true);
   stk::Stk::setSampleRate(Utilities::SAMPLES_PER_SECOND);

   std::vector<stk::StkFrames> samples;
   Instrument::loadInstruments(samples);

   std::string inputFileName = argv[1];
   std::string inputFilePath = "input/" + inputFileName;
   std::string outputFileName = argv[2];
   SheetMusic sheetMusic(inputFilePath, Utilities::SAMPLES_PER_SECOND, samples);

   unsigned int totalDivisions = (sheetMusic.songLengthSeconds_/60) * sheetMusic.beatsPerMinute_ * Utilities::DIVISIONS_PER_QUARTER_NOTE;
   MusicXmlWriter xmlWriter(totalDivisions);
   xmlWriter.loadSheetMusic(sheetMusic);
   xmlWriter.writeDrumsToFile(outputFileName);
   xmlWriter.writeBassToFile(outputFileName);
   xmlWriter.writeVocalsToFile(outputFileName);
}
