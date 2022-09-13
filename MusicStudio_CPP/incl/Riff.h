#ifndef RIFF_H
#define RIFF_H

#include <string>
#include <vector>

#include "Note.h"
#include "Instrument.h"

#include "Stk.h"


class Riff
{
public:

   Riff(std::string text,
        double samplesPerBeat,
        const std::vector<stk::StkFrames>& samples);

   ~Riff();

   void insertData(stk::StkFrames& frame);

   std::string fileText_;
   double samplesPerBeat_;
   const std::vector<stk::StkFrames>& samples_;
   std::vector<double> measures_;
   std::vector<Note> notes_;
};
















#endif // RIFF_H
