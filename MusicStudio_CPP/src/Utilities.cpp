#include "Utilities.h"

#include <regex>


const double Utilities::SAMPLES_PER_SECOND = 44100;
const unsigned int Utilities::DIVISIONS_PER_QUARTER_NOTE = 24;
const unsigned int Utilities::DIVISIONS_PER_MEASURE = 96;


stk::StkFrames Utilities::getData(std::string filename,
                                  unsigned int numberSamples,
                                  bool isRawFile,
                                  bool isFullPath)
{
   stk::FileWvIn inputFile;

   std::string fullPath = "samples/" + filename;
   if(isFullPath) fullPath = filename;

   try
   {
      inputFile.openFile(fullPath, isRawFile);
   }
   catch(stk::StkError&)
   {
      exit(1);
   }

   double rate = 1.0;
   rate = inputFile.getFileRate() / stk::Stk::sampleRate();
   inputFile.setRate( rate );
   inputFile.ignoreSampleRateChange();

   stk::StkFrames frame (numberSamples, 1);
   for(unsigned int i = 0; i<numberSamples; i++) frame[i] = 0;

   for(unsigned int i = 0; i<numberSamples; i++) frame[i] = inputFile.tick(0);

   for(unsigned int i = 1; i<1000; i++) frame[numberSamples - i] = 0;

   normalize(frame);

   return frame;

}


void Utilities::replaceInstrumentNames(std::string& text)
{
   text = std::regex_replace(text, std::regex("KICK"), "0");
   text = std::regex_replace(text, std::regex("SNARE"), "1");
   text = std::regex_replace(text, std::regex("HAT"), "2");
   text = std::regex_replace(text, std::regex("CYMBOL"), "3");
   text = std::regex_replace(text, std::regex("CRASH"), "4");
   text = std::regex_replace(text, std::regex("CLAP"), "5");
   text = std::regex_replace(text, std::regex("OHAT"), "6");
   text = std::regex_replace(text, std::regex("TOM4"), "7");
   text = std::regex_replace(text, std::regex("TOM3"), "8");
   text = std::regex_replace(text, std::regex("TOM2"), "9");
   text = std::regex_replace(text, std::regex("TOM1"), "10");

   text = std::regex_replace(text, std::regex("RBASS_E2"), "100");
   text = std::regex_replace(text, std::regex("RBASS_F2"), "101");
   text = std::regex_replace(text, std::regex("RBASS_FS2"), "102");
   text = std::regex_replace(text, std::regex("RBASS_G2"), "103");
   text = std::regex_replace(text, std::regex("RBASS_GS2"), "104");
   text = std::regex_replace(text, std::regex("RBASS_A2"), "105");
   text = std::regex_replace(text, std::regex("RBASS_AS2"), "106");
   text = std::regex_replace(text, std::regex("RBASS_B2"), "107");
   text = std::regex_replace(text, std::regex("RBASS_C3"), "108");
   text = std::regex_replace(text, std::regex("RBASS_CS3"), "109");
   text = std::regex_replace(text, std::regex("RBASS_D3"), "110");
   text = std::regex_replace(text, std::regex("RBASS_DS3"), "111");
   text = std::regex_replace(text, std::regex("RBASS_E3"), "112");
   text = std::regex_replace(text, std::regex("RBASS_F3"), "113");
   text = std::regex_replace(text, std::regex("RBASS_FS3"), "114");
   text = std::regex_replace(text, std::regex("RBASS_G3"), "115");

   text = std::regex_replace(text, std::regex("FBASS_E2"), "116");
   text = std::regex_replace(text, std::regex("FBASS_F2"), "117");
   text = std::regex_replace(text, std::regex("FBASS_FS2"), "118");
   text = std::regex_replace(text, std::regex("FBASS_G2"), "119");
   text = std::regex_replace(text, std::regex("FBASS_GS2"), "120");
   text = std::regex_replace(text, std::regex("FBASS_A2"), "121");
   text = std::regex_replace(text, std::regex("FBASS_AS2"), "122");
   text = std::regex_replace(text, std::regex("FBASS_B2"), "123");
   text = std::regex_replace(text, std::regex("FBASS_C3"), "124");
   text = std::regex_replace(text, std::regex("FBASS_CS3"), "125");
   text = std::regex_replace(text, std::regex("FBASS_D3"), "126");
   text = std::regex_replace(text, std::regex("FBASS_DS3"), "127");
   text = std::regex_replace(text, std::regex("FBASS_E3"), "128");
   text = std::regex_replace(text, std::regex("FBASS_F3"), "129");
   text = std::regex_replace(text, std::regex("FBASS_FS3"), "130");
   text = std::regex_replace(text, std::regex("FBASS_G3"), "131");

   text = std::regex_replace(text, std::regex("PIANO_C3"), "200");
   text = std::regex_replace(text, std::regex("PIANO_CS3"), "201");
   text = std::regex_replace(text, std::regex("PIANO_D3"), "202");
   text = std::regex_replace(text, std::regex("PIANO_DS3"), "203");
   text = std::regex_replace(text, std::regex("PIANO_E3"), "204");
   text = std::regex_replace(text, std::regex("PIANO_F3"), "205");
   text = std::regex_replace(text, std::regex("PIANO_FS3"), "206");
   text = std::regex_replace(text, std::regex("PIANO_G3"), "207");
   text = std::regex_replace(text, std::regex("PIANO_GS3"), "208");
   text = std::regex_replace(text, std::regex("PIANO_A3"), "209");
   text = std::regex_replace(text, std::regex("PIANO_AS3"), "210");
   text = std::regex_replace(text, std::regex("PIANO_B3"), "211");
   text = std::regex_replace(text, std::regex("PIANO_C4"), "212");
   text = std::regex_replace(text, std::regex("PIANO_CS4"), "213");
   text = std::regex_replace(text, std::regex("PIANO_D4"), "214");
   text = std::regex_replace(text, std::regex("PIANO_DS4"), "215");
   text = std::regex_replace(text, std::regex("PIANO_E4"), "216");
   text = std::regex_replace(text, std::regex("PIANO_F4"), "217");
   text = std::regex_replace(text, std::regex("PIANO_FS4"), "218");
   text = std::regex_replace(text, std::regex("PIANO_G4"), "219");
   text = std::regex_replace(text, std::regex("PIANO_GS4"), "220");
   text = std::regex_replace(text, std::regex("PIANO_A4"), "221");
   text = std::regex_replace(text, std::regex("PIANO_AS4"), "222");
   text = std::regex_replace(text, std::regex("PIANO_B4"), "223");
   text = std::regex_replace(text, std::regex("PIANO_C5"), "224");
   text = std::regex_replace(text, std::regex("PIANO_CS5"), "225");
   text = std::regex_replace(text, std::regex("PIANO_D5"), "226");
   text = std::regex_replace(text, std::regex("PIANO_DS5"), "227");
   text = std::regex_replace(text, std::regex("PIANO_E5"), "228");

}


std::string Utilities::getTagContents(std::string& text, const std::string& tag, bool sideAffect)
{
   std::string output = "";

   std::string openingTag = "<" + tag + ">";
   std::string closingTag = "</" + tag + ">";

   int start = text.find(openingTag) + openingTag.length();
   int end = text.find(closingTag);
   int endClosingTag = end + closingTag.length();
   int length = end - start;

   if(start > 0 && end > start && length > 0)
   {
      output = text.substr(start, length);
   }

   if(sideAffect && endClosingTag <= text.length())
   {
      text = text.substr(endClosingTag);
   }

   return output;
}


double Utilities::parseTagContents(std::string& text, const std::string& tag, bool sideAffect)
{
   double output = 0;
   std::string contents = getTagContents(text, tag, sideAffect);
   if(contents != "")
   {
      std::stringstream sstm(contents);
      sstm >> output;
   }

   return output;
}


std::vector<double> Utilities::parseTagContentsVector(std::string& text,
                                                      const std::string& tag,
                                                      bool sideAffect)
{
   std::vector<double> output;
   std::string contents = getTagContents(text, tag, sideAffect);
   std::string measureString = "";
   double measure = 0;
   for(unsigned int i = 0; i<contents.length(); i++)
   {
      if(contents[i] == ',' || i == contents.length() - 1)
      {
         if(contents.length() - 1) measureString += contents[i];

         std::stringstream sstm(measureString);
         sstm >> measure;
         output.push_back(measure);
         measure = 0;
         measureString = "";
      }
      else
      {
         measureString += contents[i];
      }
   }

   return output;
}


void Utilities::normalize(stk::StkFrames& frame)
{
   const unsigned int TOTAL_SAMPLES = frame.frames();

   stk::StkFloat extreme = 0;
   for(unsigned int i = 0; i<TOTAL_SAMPLES; i++)
   {
      if(frame[i] > 0)
      {
         if(frame[i] > extreme) extreme = frame[i];
      }
      else
      {
         if(-1* frame[i] > extreme) extreme = -1 * frame[i];
      }
   }
   for(unsigned int i = 0; i<TOTAL_SAMPLES; i++) frame[i] = frame[i] / extreme;
}


stk::StkFrames Utilities::noiseGate(const stk::StkFrames& input, double floor, bool removeInMiddle)
{
   std::deque< std::vector<double> > periods = getPeriods(input);

   const unsigned int NON_EXISTING_PERIOD = 999999999;
   unsigned int indexOfLastNonZeroPeriod = NON_EXISTING_PERIOD;

   for(unsigned int i = 0; i<periods.size(); i++)
   {
      bool periodIsEmpty = true;
      double average = 0;
      for(unsigned int ii = 0; ii<periods[i].size(); ii++)
      {
         if(periods[i][ii] > 0) average += periods[i][ii];
         else average += periods[i][ii] * -1;
      }

      average = average / periods[i].size();
      if(average > floor)
      {
         periodIsEmpty = false;
         break;
      }

      if(periodIsEmpty == false)
      {
         indexOfLastNonZeroPeriod = i;
      }
      else if(removeInMiddle)
      {
         for(unsigned int ii = 0; ii<periods[i].size(); ii++) periods[i][ii] = 0;
      }
   }

   if(indexOfLastNonZeroPeriod != NON_EXISTING_PERIOD && indexOfLastNonZeroPeriod < periods.size() - 1)
   {
      for(unsigned int i = periods.size() - 1; i>indexOfLastNonZeroPeriod; i--)
      {
         periods.pop_back();
      }
   }

   return joinPeriods(periods);
}


std::deque< std::vector<double> > Utilities::getPeriods(const stk::StkFrames& input)
{
   const double THRESHOLD = 0;

   std::deque< std::vector<double> > output;

   bool startingPositive = false;
   bool crossedZeroOnce = false;
   bool crossedZeroTwice = false;
   std::vector<double> period;
   for(unsigned int i = 0; i<input.frames(); i++)
   {
      if(startingPositive == false && input[i] > THRESHOLD) startingPositive = true;

      else if(startingPositive && crossedZeroOnce == false)
      {
         if(input[i] < THRESHOLD * -1) crossedZeroOnce = true;
      }

      else if(startingPositive && crossedZeroOnce && crossedZeroTwice == false)
      {
         if(input[i] > THRESHOLD) crossedZeroTwice = true;
      }

      if(startingPositive && crossedZeroOnce && crossedZeroTwice)
      {
         output.push_back(period);
         period.clear();
         startingPositive = true;
         crossedZeroOnce = false;
         crossedZeroTwice = false;
      }

      period.push_back(input[i]);
   }

   return output;
}


stk::StkFrames Utilities::joinPeriods(const std::deque< std::vector<double> >& input)
{
   unsigned int totalFrames = 0;
   for(unsigned int i = 0; i<input.size(); i++)
   {
      totalFrames += input[i].size();
   }
   stk::StkFrames output(totalFrames, 1);

   unsigned int count = 0;
   for(unsigned int i = 0; i<input.size(); i++)
   {
      for(unsigned int ii = 0; ii<input[i].size(); ii++)
      {
         output[count] = input[i][ii];
         count++;
      }
   }

   return output;
}


unsigned int Utilities::framesInPeriods(const std::deque< std::vector<double> >& input)
{
   unsigned int output = 0;


   for(unsigned int i = 0; i<input.size(); i++)
   {
      output += input[i].size();
   }

   return output;
}


std::deque<HybridPeriod> Utilities::getHybridPeriods(std::deque< std::vector<double> >& periods)
{
   std::deque<HybridPeriod> output;

   for(unsigned int i = 0; i<periods.size()-1; i++)
   {
      HybridPeriod hybrid(periods[i], periods[i+1], i);
      output.push_back(hybrid);
   }

   return output;
}


const HybridPeriod& Utilities::findClosestHybrid(std::deque<HybridPeriod>& hybrids)
{
   const double MAX_WEIGHT = 999999;

   unsigned int lowestIndex = 1;
   double lowestWeight = MAX_WEIGHT;

   for(unsigned int i = 1; i<hybrids.size()-1; i++)
   {
      if(hybrids[i].weight_ < lowestWeight)
      {
         lowestIndex = i;
         lowestWeight = hybrids[i].weight_;
      }
   }

   hybrids[lowestIndex].weight_ += MAX_WEIGHT;
   for(unsigned int i = 1; i<10; i++)
   {
      unsigned int factor = 10 - i;
      if(lowestIndex + i < hybrids.size()) hybrids[lowestIndex + i].weight_ += factor * 100;
      if(lowestIndex > i && lowestIndex - i > 1) hybrids[lowestIndex - i].weight_ += factor * 100;
   }

   return hybrids[lowestIndex];
}


stk::StkFrames Utilities::completePitchCorrection(const stk::StkFrames& original,
                                                  const stk::StkFrames& corrected)
{
   if(corrected.frames() > original.frames())
   {
      std::cout << "corrected.frames: " << corrected.frames() << "   original.frames: " << original.frames() << std::endl;
      std::cout << "completePitchCorrect to lower frequency not supported yet" << std::endl;
      exit(0);
   }

   std::deque< std::vector<double> > periods = Utilities::getPeriods(corrected);
   std::deque<HybridPeriod> hybrids = Utilities::getHybridPeriods(periods);

   while( framesInPeriods(periods) < original.frames() )
   {
      const HybridPeriod& closest = findClosestHybrid(hybrids);
      std::deque< std::vector<double> >::iterator it = periods.begin() + closest.position_;
      periods.insert(it, closest.frames_);
   }

   return joinPeriods(periods);
}


void Utilities::setGain(stk::StkFrames& frame, double gain)
{
   const unsigned int TOTAL_SAMPLES = frame.frames();

   if(gain < 0 || gain > 1) return;

   for(unsigned int i = 0; i<TOTAL_SAMPLES; i++)
   {
      frame[i] = frame[i] * gain;
   }
}


stk::StkFrames Utilities::changeFrequency(const stk::StkFrames& input, double oldFrequency, double newFrequency)
{
   if(newFrequency < oldFrequency)
   {
      stk::StkFrames halfInput = halfFrequency(input, oldFrequency);
      return changeFrequency(halfInput, oldFrequency/2, newFrequency);
   }

   stk::StkFrames output = input;
   for(unsigned int i = 0; i<output.frames(); i++) output[i] = 0;

   double factor = newFrequency / oldFrequency;
   double lengthFactor = oldFrequency / newFrequency;
   unsigned int newLength = (((double) input.frames()) * lengthFactor) + 1;

   for(unsigned int i = 1; i<newLength; i++)
   {
      double oldIndexDouble = ((double) i) * factor;
      unsigned int oldIndex = oldIndexDouble;

      if(oldIndex + 1 > input.frames()) break;

      double remainder = oldIndexDouble - ((double) oldIndex);
      unsigned int upperIndex = oldIndex + 1;
      double lowerRemainder = 1 - remainder;
      double newValue = input[upperIndex] * remainder + input[oldIndex] * lowerRemainder;
      output[i] = newValue;
   }

   return output;
}


stk::StkFrames Utilities::halfFrequency(const stk::StkFrames& input, double oldFrequency)
{
   stk::StkFrames output (input.frames() * 2, 1);
   for(unsigned int i = 0; i<output.frames(); i++) output[i] = 0;

   for(unsigned int i = 0; i<input.frames(); i+=2)
   {
      output[i*2] = input[i];
      if( (i*2+1 < output.frames()) && (i+1 < input.frames()) )
      {
         output[i*2+1] = (input[i] + input[i+1]) / 2;
      }
   }

   return output;
}


stk::StkFrames Utilities::mixSamples(const stk::StkFrames& inputOne, const stk::StkFrames& inputTwo)
{
   stk::StkFrames output = inputOne;

   for(unsigned int i = 0; i<output.frames(); i++)
   {
      output[i] = (output[i] + inputTwo[i]) / 2;
   }

   return output;
}






