#ifndef UTILITIES_H
#define UTILITIES_H

#include <vector>

#include "Stk.h"
#include "FileWvIn.h"


class Utilities
{
public:

   static stk::StkFrames getData(std::string filename,
                                 unsigned int numberSamples,
                                 bool isRawFile = false);

   static std::string getTagContents(std::string& text, const std::string& tag, bool sideAffect = false);

   static double parseTagContents(std::string& text, const std::string& tag, bool sideAffect = false);

   static std::vector<double> parseTagContentsVector(std::string& text,
                                                     const std::string& tag,
                                                     bool sideAffect = false);

   static void normalize(stk::StkFrames& frame);

   static void setGain(stk::StkFrames& frame, double gain);

   static stk::StkFrames changeFrequency(const stk::StkFrames& input, double oldFrequency, double newFrequency);

   static stk::StkFrames mixSamples(const stk::StkFrames& inputOne, const stk::StkFrames& inputTwo);

};


























#endif // UTILITIES_H
