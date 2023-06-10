#include "Note.h"

#include "Utilities.h"


Note::Note(std::string text, double samplesPerBeat)
{
   double instrument = Utilities::parseTagContents(text, "Instrument");
   instrument_ = static_cast<INSTRUMENT>(instrument);

   // beat is given in 96th notes, so quarter note is 24
   double beat = Utilities::parseTagContents(text, "Beat");
   beat_ = static_cast<unsigned int>(beat);
   double samplesPer96th = samplesPerBeat / 24;
   startingSample_ = beat * samplesPer96th;

   // length is given in 96th notes also, will decay in last 15% linearly
   double length = Utilities::parseTagContents(text, "Length");
   length_ = static_cast<unsigned int>(length);
   lengthSamples_ = length * samplesPer96th;

   gain_ = Utilities::parseTagContents(text, "Gain");
   if(gain_ == 0) gain_ = 1;
}


Note::~Note()
{

}

void Note::insertData(stk::StkFrames& frame, const stk::StkFrames& sample, double measureOffset)
{
   double noteOffset = measureOffset + startingSample_;
   if(lengthSamples_ == 0) // not used, copy whole sample
   {
      for(unsigned int i = 0; i<sample.frames(); i++)
      {
         frame[noteOffset + i] += sample[i] * gain_;
      }
   }
   else
   {
      unsigned int startDecay = lengthSamples_ * 0.85;  // 0-84 normal   85-99 decay   15
      unsigned int decayLength = lengthSamples_ - startDecay;
      for(unsigned int i = 0; i<sample.frames() && i < startDecay; i++)
      {
         frame[noteOffset + i] += sample[i] * gain_;
      }
      for(unsigned int i = 0; i<decayLength && i+startDecay<sample.frames(); i++)
      {
         unsigned int decayIndex = startDecay + i;
         double decayFactor = ((double) 1) - ( ((double)(i+1)) / ((double) decayLength));
         frame[noteOffset + decayIndex] += sample[decayIndex] * decayFactor * gain_;
      }

   }
}
