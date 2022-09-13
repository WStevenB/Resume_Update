#include "SheetMusic.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include "Utilities.h"


SheetMusic::SheetMusic(std::string inputFilePath,
                       double sampleRate,
                       const std::vector<stk::StkFrames>& samples) : samples_(samples)
{
   sampleRate_ = sampleRate;

   std::ifstream ifs(inputFilePath);
   if(ifs.is_open())
   {
      char c;
      while (ifs.get(c)) fileContents_.push_back(c);
   }

   songLengthSeconds_ = Utilities::parseTagContents(fileContents_, "LengthSeconds");
   if(songLengthSeconds_ < 1 || songLengthSeconds_ > 10000)
   {
      std::cout << "Failed to parse song length" << std::endl;
      exit(0);
   }

   beatsPerMinute_ = Utilities::parseTagContents(fileContents_, "BeatsPerMinute");
   beatsPerMinute_ = beatsPerMinute_ * 2;
   if(beatsPerMinute_ < 20 || beatsPerMinute_ > 300)
   {
      std::cout << "Failed to parse beats per minute" << std::endl;
      exit(0);
   }
   double beatsPerSecond = beatsPerMinute_ / 60;
   double samplesPerBeat = sampleRate / beatsPerSecond;

   std::string temp = fileContents_;
   while(temp.find("Riff") != std::string::npos)
   {
      std::string riffText = Utilities::getTagContents(temp, "Riff", true);
      Riff riff(riffText, samplesPerBeat, samples_);
      riffs_.push_back(riff);
   }
}

SheetMusic::~SheetMusic()
{

}


void SheetMusic::insertData(stk::StkFrames& frame)
{
   for(unsigned int i = 0; i<riffs_.size(); i++)
   {
      riffs_[i].insertData(frame);
   }
}
