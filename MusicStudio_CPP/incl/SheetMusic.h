#ifndef SHEET_MUSIC_H
#define SHEET_MUSIC_H

#include <string>
#include <vector>

#include "Instrument.h"
#include "Riff.h"

#include "Stk.h"


class SheetMusic
{
public:

   SheetMusic(std::string inputFilePath,
              double sampleRate,
              const std::vector<stk::StkFrames>& samples);

   ~SheetMusic();

   void insertData(stk::StkFrames& frame);


   std::string fileContents_;
   double sampleRate_;
   double beatsPerMinute_;
   double songLengthSeconds_;

   const std::vector<stk::StkFrames>& samples_;
   std::vector<Riff> riffs_;
};






















#endif //SHEET_MUSIC_H
