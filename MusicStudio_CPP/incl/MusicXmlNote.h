#ifndef MUSICXMLNOTE_H
#define MUSICXMLNOTE_H

#include <string>

#include "Instrument.h"
#include "Note.h"
#include "Stk.h"

class MusicXmlNote
{
public:

   MusicXmlNote(Note note);
   ~MusicXmlNote();

   INSTRUMENT instrument_;
   unsigned int startingDivision_;
   unsigned int duration_;
};




















#endif // MUSICXMLNOTE_H
