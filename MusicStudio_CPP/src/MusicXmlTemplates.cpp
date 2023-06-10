#include "MusicXmlTemplates.h"

#include <fstream>
#include <regex>

#include "Utilities.h"


MusicXmlTemplates::MusicXmlTemplates()
{
   songStart_ = readTemplateFile("songStart.xml");
   songEnd_ = readTemplateFile("songEnd.xml");
   measureStart_ = readTemplateFile("measureStart.xml");
   measureEnd_ = readTemplateFile("measureEnd.xml");
   kickDrum_ = readTemplateFile("kickDrum.xml");
   kickRest_ = readTemplateFile("kickRest.xml");
   snare_ = readTemplateFile("snare.xml");
   chordSnare_ = readTemplateFile("chordSnare.xml");
   hat_ = readTemplateFile("hat.xml");
   crash_ = readTemplateFile("crash.xml");
   backup_ = readTemplateFile("backup.xml");

   bassRest_ = readTemplateFile("bassRest.xml");
   bass_ = readTemplateFile("bass.xml");
}

MusicXmlTemplates::~MusicXmlTemplates()
{

}


std::string MusicXmlTemplates::readTemplateFile(std::string filename)
{
   std::string output = "";

   std::string path = "templates/" + filename;
   std::ifstream ifs(path);
   if(ifs.is_open())
   {
      char c;
      while (ifs.get(c)) output.push_back(c);
   }
   output += "\n";

   return output;
}


std::string MusicXmlTemplates::getSongStart()
{
   return songStart_;
}


std::string MusicXmlTemplates::getSongEnd()
{
   return songEnd_;
}


std::string MusicXmlTemplates::getMeasureStart(std::string number, bool isBassClef)
{
   std::string output = "";
   output = std::regex_replace(measureStart_, std::regex("___MEASURE_NUMBER___"), number);
   if(isBassClef)
   {
      output = std::regex_replace(output, std::regex("___SIGN___"), "F");
   }
   else
   {
      output = std::regex_replace(output, std::regex("___SIGN___"), "G");
   }
   return output;
}


std::string MusicXmlTemplates::getMeasureEnd()
{
   return measureEnd_;
}


std::string MusicXmlTemplates::getKickDrum(std::string duration, std::string type)
{
   std::string output = "";
   output = std::regex_replace(kickDrum_, std::regex("___DURATION___"), duration);
   output = std::regex_replace(output, std::regex("___TYPE___"), type);
   return output;
}


std::string MusicXmlTemplates::getKickRest(std::string duration, std::string type)
{
   std::string output = "";
   output = std::regex_replace(kickRest_, std::regex("___DURATION___"), duration);
   output = std::regex_replace(output, std::regex("___TYPE___"), type);
   return output;
}


std::string MusicXmlTemplates::getSnare(std::string duration, std::string type)
{
   std::string output = "";
   output = std::regex_replace(snare_, std::regex("___DURATION___"), duration);
   output = std::regex_replace(output, std::regex("___TYPE___"), type);
   return output;
}


std::string MusicXmlTemplates::getChordSnare(std::string duration, std::string type)
{
   std::string output = "";
   output = std::regex_replace(chordSnare_, std::regex("___DURATION___"), duration);
   output = std::regex_replace(output, std::regex("___TYPE___"), type);
   return output;
}


std::string MusicXmlTemplates::getHat(std::string duration, std::string type)
{
   std::string output = "";
   output = std::regex_replace(hat_, std::regex("___DURATION___"), duration);
   output = std::regex_replace(output, std::regex("___TYPE___"), type);
   return output;
}


std::string MusicXmlTemplates::getCrash(std::string duration, std::string type)
{
   std::string output = "";
   output = std::regex_replace(crash_, std::regex("___DURATION___"), duration);
   output = std::regex_replace(output, std::regex("___TYPE___"), type);
   return output;
}


std::string MusicXmlTemplates::getBackup(std::string duration)
{
   std::string output = "";
   output = std::regex_replace(backup_, std::regex("___DURATION___"), duration);
   return output;
}


std::string MusicXmlTemplates::getBassRest(std::string duration, std::string type)
{
   std::string output = "";
   output = std::regex_replace(bassRest_, std::regex("___DURATION___"), duration);
   output = std::regex_replace(output, std::regex("___TYPE___"), type);
   return output;
}


std::string MusicXmlTemplates::getBass(std::string note,
                                       std::string octave,
                                       std::string duration,
                                       std::string type)
{
   std::string output = "";
   output = std::regex_replace(bass_, std::regex("___NOTE___"), note);
   output = std::regex_replace(output, std::regex("___OCTAVE___"), octave);
   output = std::regex_replace(output, std::regex("___DURATION___"), duration);
   output = std::regex_replace(output, std::regex("___TYPE___"), type);
   if(octave == "2" || (octave == "3" && note == "C"))
   {
      output = std::regex_replace(output, std::regex("___STEM___"), "up");
   }
   else output = std::regex_replace(output, std::regex("___STEM___"), "down");
   return output;
}


std::string MusicXmlTemplates::getType(unsigned int duration)
{
   std::string output = "quarter";

   if(duration >= 5 && duration <= 7) output = "16th";
   else if(duration >= 11 && duration <= 13) output = "eighth";
   else if(duration >= 23 && duration <= 25) output = "quarter";
   else if(duration >= 47 && duration <= 49) output = "half";
   else if(duration >= 95) output = "whole";

   return output;
}


void MusicXmlTemplates::getNoteAndOctave(INSTRUMENT instrument,
                                         std::string& note,
                                         std::string& octave)
{
   switch(instrument)
   {
   case BASS_E2:
   case BASS_FINGER_E2:
      note = "E";
      octave = "2";
      break;

   case BASS_F2:
   case BASS_FINGER_F2:
      note = "F";
      octave = "2";
      break;

   case BASS_FSHARP2:
   case BASS_FINGER_FSHARP2:
      note = "F";
      octave = "2";
      break;

   case BASS_G2:
   case BASS_FINGER_G2:
      note = "G";
      octave = "2";
      break;

   case BASS_GSHARP2:
   case BASS_FINGER_GSHARP2:
      note = "G";
      octave = "2";
      break;

   case BASS_A2:
   case BASS_FINGER_A2:
      note = "A";
      octave = "2";
      break;

   case BASS_ASHARP2:
   case BASS_FINGER_ASHARP2:
      note = "A";
      octave = "2";
      break;

   case BASS_B2:
   case BASS_FINGER_B2:
      note = "B";
      octave = "2";
      break;

   case BASS_C3:
   case BASS_FINGER_C3:
      note = "C";
      octave = "3";
      break;

   case BASS_CSHARP3:
   case BASS_FINGER_CSHARP3:
      note = "C";
      octave = "3";
      break;

   case BASS_D3:
   case BASS_FINGER_D3:
      note = "D";
      octave = "3";
      break;

   case BASS_DSHARP3:
   case BASS_FINGER_DSHARP3:
      note = "D";
      octave = "3";
      break;

   case BASS_E3:
   case BASS_FINGER_E3:
      note = "E";
      octave = "3";
      break;

   case BASS_F3:
   case BASS_FINGER_F3:
      note = "F";
      octave = "3";
      break;

   case BASS_FSHARP3:
   case BASS_FINGER_FSHARP3:
      note = "F";
      octave = "3";
      break;

   case BASS_G3:
   case BASS_FINGER_G3:
      note = "G";
      octave = "3";
      break;




   case PIANO_C3:
      note = "C";
      octave = "3";
      break;

   case PIANO_CS3:
      note = "C";
      octave = "3";
      break;

   case PIANO_D3:
      note = "D";
      octave = "3";
      break;

   case PIANO_DS3:
      note = "D";
      octave = "3";
      break;

   case PIANO_E3:
      note = "E";
      octave = "3";
      break;

   case PIANO_F3:
      note = "F";
      octave = "3";
      break;

   case PIANO_FS3:
      note = "F";
      octave = "3";
      break;

   case PIANO_G3:
      note = "G";
      octave = "3";
      break;

   case PIANO_GS3:
      note = "G";
      octave = "3";
      break;

   case PIANO_A3:
      note = "A";
      octave = "3";
      break;

   case PIANO_AS3:
      note = "A";
      octave = "3";
      break;

   case PIANO_B3:
      note = "B";
      octave = "3";
      break;

   case PIANO_C4:
      note = "C";
      octave = "4";
      break;

   case PIANO_CS4:
      note = "C";
      octave = "4";
      break;

   case PIANO_D4:
      note = "D";
      octave = "4";
      break;

   case PIANO_DS4:
      note = "D";
      octave = "4";
      break;

   case PIANO_E4:
      note = "E";
      octave = "4";
      break;

   case PIANO_F4:
      note = "F";
      octave = "4";
      break;

   case PIANO_FS4:
      note = "F";
      octave = "4";
      break;

   case PIANO_G4:
      note = "G";
      octave = "4";
      break;

   case PIANO_GS4:
      note = "G";
      octave = "4";
      break;

   case PIANO_A4:
      note = "A";
      octave = "4";
      break;

   case PIANO_AS4:
      note = "A";
      octave = "4";
      break;

   case PIANO_B4:
      note = "B";
      octave = "4";
      break;

   case PIANO_C5:
      note = "C";
      octave = "5";
      break;

   case PIANO_CS5:
      note = "C";
      octave = "5";
      break;

   case PIANO_D5:
      note = "D";
      octave = "5";
      break;

   case PIANO_DS5:
      note = "D";
      octave = "5";
      break;

   case PIANO_E5:
      note = "E";
      octave = "5";
      break;

   default:
      break;
   }
}

