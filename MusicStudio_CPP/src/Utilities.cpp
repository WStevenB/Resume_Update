#include "Utilities.h"


stk::StkFrames Utilities::getData(std::string filename,
                                  unsigned int numberSamples,
                                  bool isRawFile)
{
   stk::StkFrames frame (numberSamples, 1);
   stk::FileWvIn inputFile;

   std::string fullPath = "samples/" + filename;
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

   for(unsigned int i = 0; i<numberSamples; i++) frame[i] = inputFile.tick(0);

   return frame;

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
   stk::StkFrames output = input;

   double factor = newFrequency / oldFrequency;
   unsigned int newLength = (((double) input.frames()) * factor) + 1;

   for(unsigned int i = 1; i<newLength; i++)
   {
      double oldIndexDouble = ((double) i) * factor;
      unsigned int oldIndex = oldIndexDouble;
      double remainder = oldIndexDouble - ((double) oldIndex);

      unsigned int upperIndex = oldIndex + 1;
      double lowerRemainder = 1 - remainder;
      double newValue = input[upperIndex] * remainder + input[oldIndex] * lowerRemainder;
      output[i] = newValue;
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






