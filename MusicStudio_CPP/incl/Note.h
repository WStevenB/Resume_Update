#ifndef NOTE_H
#define NOTE_H

#include <string>

#include "Instrument.h"

#include "Stk.h"

class Note
{
public:

   Note(std::string text, double samplesPerBeat);
   ~Note();

   void insertData(stk::StkFrames& frame, const stk::StkFrames& sample, double measureOffset);

   INSTRUMENT instrument_;
   double startingSample_;
   double lengthSamples_;
   double gain_;
   unsigned int beat_;
   unsigned int length_;
};




















#endif // NOTE_H
