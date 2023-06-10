#ifndef UTILITIES_H
#define UTILITIES_H

#include <vector>
#include <deque>

#include "Stk.h"
#include "FileWvIn.h"

#include "HybridPeriod.h"


class Utilities
{
public:

   static const double SAMPLES_PER_SECOND;
   static const unsigned int DIVISIONS_PER_QUARTER_NOTE;
   static const unsigned int DIVISIONS_PER_MEASURE;


   static stk::StkFrames getData(std::string filename,
                                 unsigned int numberSamples,
                                 bool isRawFile = false,
                                 bool isFullPath = false);

   static void replaceInstrumentNames(std::string& text);

   static std::string getTagContents(std::string& text, const std::string& tag, bool sideAffect = false);

   static double parseTagContents(std::string& text, const std::string& tag, bool sideAffect = false);

   static std::vector<double> parseTagContentsVector(std::string& text,
                                                     const std::string& tag,
                                                     bool sideAffect = false);

   static void normalize(stk::StkFrames& frame);

   static stk::StkFrames noiseGate(const stk::StkFrames& input, double floor, bool removeInMiddle);

   static std::deque< std::vector<double> > getPeriods(const stk::StkFrames& input);

   static stk::StkFrames joinPeriods(const std::deque< std::vector<double> >& input);

   static unsigned int framesInPeriods(const std::deque< std::vector<double> >& input);

   static std::deque<HybridPeriod> getHybridPeriods(std::deque< std::vector<double> >& periods);

   static const HybridPeriod& findClosestHybrid(std::deque<HybridPeriod>& hybrids);

   static stk::StkFrames completePitchCorrection(const stk::StkFrames& original,
                                                 const stk::StkFrames& corrected);

   static void setGain(stk::StkFrames& frame, double gain);

   static stk::StkFrames changeFrequency(const stk::StkFrames& input, double oldFrequency, double newFrequency);

   static stk::StkFrames halfFrequency(const stk::StkFrames& input, double oldFrequency);

   static stk::StkFrames mixSamples(const stk::StkFrames& inputOne, const stk::StkFrames& inputTwo);

};


























#endif // UTILITIES_H
