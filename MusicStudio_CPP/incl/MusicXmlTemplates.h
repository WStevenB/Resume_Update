#ifndef MUSICXMLTEMPLATES_H
#define MUSICXMLTEMPLATES_H

#include <string>

#include "Instrument.h"


class MusicXmlTemplates
{
public:

   MusicXmlTemplates();
   ~MusicXmlTemplates();

   std::string readTemplateFile(std::string filename);
   std::string getSongStart();
   std::string getSongEnd();
   std::string getMeasureStart(std::string number, bool isBassClef = true);
   std::string getMeasureEnd();
   std::string getKickDrum(std::string duration, std::string type);
   std::string getKickRest(std::string duration, std::string type);
   std::string getSnare(std::string duration, std::string type);
   std::string getChordSnare(std::string duration, std::string type);
   std::string getHat(std::string duration, std::string type);
   std::string getCrash(std::string duration, std::string type);
   std::string getBackup(std::string duration);

   std::string getBassRest(std::string duration, std::string type);
   std::string getBass(std::string note,
                       std::string octave,
                       std::string duration,
                       std::string type);

   std::string getType(unsigned int duration);

   void getNoteAndOctave(INSTRUMENT instrument,
                         std::string& note,
                         std::string& octave);

   std::string songStart_;
   std::string songEnd_;
   std::string measureStart_;
   std::string measureEnd_;
   std::string kickDrum_;
   std::string kickRest_;
   std::string snare_;
   std::string chordSnare_;
   std::string hat_;
   std::string crash_;
   std::string backup_;

   std::string bassRest_;
   std::string bass_;
};















#endif  // MUSICXMLTEMPLATES_H
