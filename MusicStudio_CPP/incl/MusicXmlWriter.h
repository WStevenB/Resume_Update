#ifndef MUSICXMLWRITER_H
#define MUSICXMLWRITER_H

#include <string>
#include <vector>

#include "MusicXmlNote.h"
#include "Instrument.h"
#include "SheetMusic.h"

#include "Stk.h"


class MusicXmlWriter
{
public:

   MusicXmlWriter(unsigned int songLengthInDivisions);

   ~MusicXmlWriter();

   void loadSheetMusic(SheetMusic music);

   void writeDrumsToFile(std::string filename);
   void writeBassToFile(std::string filename);
   void writeVocalsToFile(std::string filename);

   unsigned int totalDivisions_;

   std::vector< std::vector<MusicXmlNote> > drumDivisions_;
   std::vector< std::vector<MusicXmlNote> > bassDivisions_;
   std::vector< std::vector<MusicXmlNote> > vocalDivisions_;
};
















#endif // MUSICXMLWRITER_H
