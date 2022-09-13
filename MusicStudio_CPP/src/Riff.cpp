#include "Riff.h"

#include "Utilities.h"


Riff::Riff(std::string text,
           double samplesPerBeat,
           const std::vector<stk::StkFrames>& samples) : samples_(samples)
{
   fileText_ = text;
   samplesPerBeat_ = samplesPerBeat;

   std::string temp = text;
   measures_ = Utilities::parseTagContentsVector(temp, "Measures", true);
   for(unsigned int i = 0; i<measures_.size(); i++)
   {
      measures_[i] = measures_[i] - 1;
   }

   while(temp.find("Note") != std::string::npos)
   {
      std::string noteText = Utilities::getTagContents(temp, "Note", true);
      Note note(noteText, samplesPerBeat_);
      notes_.push_back(note);
   }
}

Riff::~Riff()
{

}


void Riff::insertData(stk::StkFrames& frame)
{
   for(unsigned int i = 0; i<measures_.size(); i++)
   {
      double measureOffset = measures_[i] * samplesPerBeat_ * 4; // 4x4 time signature assumed
      for(unsigned int ii = 0; ii<notes_.size(); ii++)
      {
         notes_[ii].insertData(frame, samples_[notes_[ii].instrument_], measureOffset);
      }
   }
}
