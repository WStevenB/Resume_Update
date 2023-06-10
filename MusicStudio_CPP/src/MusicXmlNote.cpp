#include "MusicXmlNote.h"

#include "Utilities.h"


MusicXmlNote::MusicXmlNote(Note note)
{
   instrument_ = note.instrument_;
   startingDivision_ = note.beat_;
   duration_ = note.length_;
}


MusicXmlNote::~MusicXmlNote()
{

}
