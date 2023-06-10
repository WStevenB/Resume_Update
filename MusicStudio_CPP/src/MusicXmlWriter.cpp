#include "MusicXmlWriter.h"

#include <fstream>

#include "MusicXmlNote.h"
#include "MusicXmlTemplates.h"
#include "Utilities.h"


MusicXmlWriter::MusicXmlWriter(unsigned int songLengthInDivisions)
{
   totalDivisions_ = songLengthInDivisions;

   for(unsigned int i = 0; i<songLengthInDivisions; i++)
   {
      std::vector<MusicXmlNote> noteVector;

      drumDivisions_.push_back(noteVector);
      bassDivisions_.push_back(noteVector);
      vocalDivisions_.push_back(noteVector);
   }
}

MusicXmlWriter::~MusicXmlWriter()
{

}


void MusicXmlWriter::loadSheetMusic(SheetMusic music)
{
   for(unsigned int i = 0; i<music.riffs_.size(); i++)
   {
      for(unsigned int ii = 0; ii<music.riffs_[i].measures_.size(); ii++)
      {
         unsigned int measureStartDivision = music.riffs_[i].measures_[ii] * Utilities::DIVISIONS_PER_MEASURE;

         for(unsigned int iii = 0; iii<music.riffs_[i].notes_.size(); iii++)
         {
            MusicXmlNote note(music.riffs_[i].notes_[iii]);
            unsigned int noteDivision = measureStartDivision + note.startingDivision_;

            if(note.instrument_ < 100) drumDivisions_[noteDivision].push_back(note);
            else if(note.instrument_ < 200) bassDivisions_[noteDivision].push_back(note);
            else vocalDivisions_[noteDivision].push_back(note);
         }
      }
   }
}

void MusicXmlWriter::writeDrumsToFile(std::string filename)
{
   const unsigned int UNASSIGNED = 999999;

   MusicXmlTemplates templates;
   unsigned int numberOfMeasures = totalDivisions_ / Utilities::DIVISIONS_PER_MEASURE;

   std::string drumXml = templates.getSongStart();

   for(unsigned int i = 0; i<numberOfMeasures; i++)
   {
      drumXml += templates.getMeasureStart(std::to_string(i+1));

      unsigned int divisionStart = i * Utilities::DIVISIONS_PER_MEASURE;
      unsigned int divisionEnd = divisionStart + Utilities::DIVISIONS_PER_MEASURE;

      bool hasKickDrum = false;
      for(unsigned int ii = divisionStart; ii<divisionEnd && ii<drumDivisions_.size(); ii++)
      {
         unsigned int crashIndex = UNASSIGNED;
         unsigned int snareIndex = UNASSIGNED;
         unsigned int hatIndex = UNASSIGNED;
         for(unsigned int iii = 0; iii<drumDivisions_[ii].size(); iii++)
         {
            if(drumDivisions_[ii][iii].instrument_ == SNARE_DRUM) snareIndex = iii;
            else if(drumDivisions_[ii][iii].instrument_ == HI_HAT) hatIndex = iii;
            else if(drumDivisions_[ii][iii].instrument_ == CRASH_CYMBOL) crashIndex = iii;
            else if(drumDivisions_[ii][iii].instrument_ == BASS_DRUM) hasKickDrum = true;
         }
         if(crashIndex != UNASSIGNED)
         {
            drumXml += templates.getCrash("24", "quarter");
            if(snareIndex != UNASSIGNED) drumXml += templates.getChordSnare("24", "quarter");
         }
         else if(hatIndex != UNASSIGNED)
         {
            drumXml += templates.getHat("24", "quarter");
            if(snareIndex != UNASSIGNED) drumXml += templates.getChordSnare("24", "quarter");
         }
         else if(snareIndex != UNASSIGNED)
         {
            drumXml += templates.getSnare("24", "quarter");
         }
      }

      if(hasKickDrum)
      {
         drumXml += templates.getBackup("96");

         unsigned int restCount = 0;
         for(unsigned int ii = divisionStart; ii<divisionEnd && ii<drumDivisions_.size(); ii++)
         {
            unsigned int kickIndex = UNASSIGNED;
            for(unsigned int iii = 0; iii<drumDivisions_[ii].size(); iii++)
            {
               if(drumDivisions_[ii][iii].instrument_ == BASS_DRUM)
               {
                  kickIndex = iii;
               }
            }

            if(kickIndex != UNASSIGNED)
            {
               if(restCount > 0)
               {
                  std::string restType = templates.getType(restCount);
                  drumXml += templates.getKickRest( std::to_string(restCount), restType);
                  restCount = 0;
               }

               drumXml += templates.getKickDrum("24", "quarter");
               ii += Utilities::DIVISIONS_PER_QUARTER_NOTE - 1;
            }
            else restCount++;
         }
         if(restCount > 0)
         {
            std::string restType = templates.getType(restCount);
            drumXml += templates.getKickRest( std::to_string(restCount), restType);
         }
      }

      drumXml += templates.getMeasureEnd();
   }

   drumXml += templates.getSongEnd();

   std::string path = "output/Drums_" + filename;
   std::ofstream writer(path);
   writer << drumXml;
}


void MusicXmlWriter::writeBassToFile(std::string filename)
{
   MusicXmlTemplates templates;
   unsigned int numberOfMeasures = totalDivisions_ / Utilities::DIVISIONS_PER_MEASURE;

   std::string bassXml = templates.getSongStart();

   for(unsigned int i = 0; i<numberOfMeasures; i++)
   {
      bassXml += templates.getMeasureStart(std::to_string(i+1));

      unsigned int divisionStart = i * Utilities::DIVISIONS_PER_MEASURE;
      unsigned int divisionEnd = divisionStart + Utilities::DIVISIONS_PER_MEASURE;
      unsigned int restCount = 0;

      for(unsigned int ii = divisionStart; ii<divisionEnd && ii<bassDivisions_.size(); ii++)
      {
         if(bassDivisions_[ii].size() == 0)
         {
            restCount++;
         }
         else
         {
            if(restCount > 0)
            {
               std::string restType = templates.getType(restCount);
               bassXml += templates.getBassRest(std::to_string(restCount), restType);
               restCount = 0;
            }
            std::string note = "";
            std::string octave = "";
            unsigned int duration = bassDivisions_[ii][0].duration_;
            std::string type = templates.getType(duration);
            templates.getNoteAndOctave(bassDivisions_[ii][0].instrument_, note, octave);
            bassXml += templates.getBass(note,
                                         octave,
                                         std::to_string(duration),
                                         type);

            ii += bassDivisions_[ii][0].duration_ - 1;
         }
      }

      if(restCount > 0)
      {
         std::string restType = templates.getType(restCount);
         bassXml += templates.getBassRest(std::to_string(restCount), restType);
         restCount = 0;
      }

      bassXml += templates.getMeasureEnd();
   }

   bassXml += templates.getSongEnd();

   std::string path = "output/Bass_" + filename;
   std::ofstream writer(path);
   writer << bassXml;
}


void MusicXmlWriter::writeVocalsToFile(std::string filename)
{
   MusicXmlTemplates templates;
   unsigned int numberOfMeasures = totalDivisions_ / Utilities::DIVISIONS_PER_MEASURE;

   std::string vocalsXml = templates.getSongStart();

   for(unsigned int i = 0; i<numberOfMeasures; i++)
   {
      vocalsXml += templates.getMeasureStart(std::to_string(i+1), false);

      unsigned int divisionStart = i * Utilities::DIVISIONS_PER_MEASURE;
      unsigned int divisionEnd = divisionStart + Utilities::DIVISIONS_PER_MEASURE;
      unsigned int restCount = 0;

      for(unsigned int ii = divisionStart; ii<divisionEnd && ii<vocalDivisions_.size(); ii++)
      {
         if(vocalDivisions_[ii].size() == 0)
         {
            restCount++;
         }
         else
         {
            if(restCount > 0)
            {
               std::string restType = templates.getType(restCount);
               vocalsXml += templates.getBassRest(std::to_string(restCount), restType);
               restCount = 0;
            }
            std::string note = "";
            std::string octave = "";
            unsigned int duration = vocalDivisions_[ii][0].duration_;
            std::string type = templates.getType(duration);
            templates.getNoteAndOctave(vocalDivisions_[ii][0].instrument_, note, octave);
            vocalsXml += templates.getBass(note,
                                           octave,
                                           std::to_string(duration),
                                           type);

            ii += vocalDivisions_[ii][0].duration_ - 1;
         }
      }

      if(restCount > 0)
      {
         std::string restType = templates.getType(restCount);
         vocalsXml += templates.getBassRest(std::to_string(restCount), restType);
         restCount = 0;
      }

      vocalsXml += templates.getMeasureEnd();
   }

   vocalsXml += templates.getSongEnd();

   std::string path = "output/Vocals_" + filename;
   std::ofstream writer(path);
   writer << vocalsXml;
}






