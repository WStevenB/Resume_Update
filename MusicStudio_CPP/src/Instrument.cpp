#include "Instrument.h"

#include "Utilities.h"



Instrument::Instrument() {}

Instrument::~Instrument() {}

void Instrument::loadInstruments(std::vector<stk::StkFrames>& samples)
{
   const double FRAMES_PER_SAMPLE = 10000;

   stk::StkFrames hiHat = Utilities::getData("hihatcym.raw", FRAMES_PER_SAMPLE, true);
   stk::StkFrames bassDrum = Utilities::getData("bassdrum.raw", FRAMES_PER_SAMPLE, true);
   stk::StkFrames snareDrum = Utilities::getData("snardrum.raw", FRAMES_PER_SAMPLE, true);
   stk::StkFrames clap = Utilities::getData("clap.wav", FRAMES_PER_SAMPLE*20, false);
   stk::StkFrames openHiHat = Utilities::getData("open_hi_hat.wav", FRAMES_PER_SAMPLE*20, false);
   stk::StkFrames crashCymbol = Utilities::getData("crashcym.raw", FRAMES_PER_SAMPLE*20, true);

   stk::StkFrames bassGuitarE2 = Utilities::getData("bass_pick_E.wav", FRAMES_PER_SAMPLE*20, false);
   Utilities::normalize(bassGuitarE2);
   stk::StkFrames bassGuitarF2 = Utilities::changeFrequency(bassGuitarE2,  41.2, 43.65);
   stk::StkFrames bassGuitarFS2 = Utilities::changeFrequency(bassGuitarE2, 41.2, 46.25);
   stk::StkFrames bassGuitarG2 = Utilities::changeFrequency(bassGuitarE2,  41.2, 49);
   stk::StkFrames bassGuitarGS2 = Utilities::changeFrequency(bassGuitarE2, 41.2, 51.91);
   stk::StkFrames bassGuitarA3 = Utilities::changeFrequency(bassGuitarE2,  41.2, 55);
   stk::StkFrames bassGuitarAS3 = Utilities::changeFrequency(bassGuitarE2, 41.2, 58.27);
   stk::StkFrames bassGuitarB3 = Utilities::changeFrequency(bassGuitarE2,  41.2, 61.74);
   stk::StkFrames bassGuitarC3 = Utilities::changeFrequency(bassGuitarE2,  41.2, 65.41);
   stk::StkFrames bassGuitarCS3 = Utilities::changeFrequency(bassGuitarE2, 41.2, 69.3);
   stk::StkFrames bassGuitarD3 = Utilities::changeFrequency(bassGuitarE2,  41.2, 73.42);
   stk::StkFrames bassGuitarDS3 = Utilities::changeFrequency(bassGuitarE2, 41.2, 77.78);
   stk::StkFrames bassGuitarE3 = Utilities::changeFrequency(bassGuitarE2,  41.2, 82.41);
   stk::StkFrames bassGuitarF3 = Utilities::changeFrequency(bassGuitarE2,  41.2, 87.31);
   stk::StkFrames bassGuitarFS3 = Utilities::changeFrequency(bassGuitarE2, 41.2, 92.5);
   stk::StkFrames bassGuitarG3 = Utilities::changeFrequency(bassGuitarE2,  41.2, 98);

   stk::StkFrames bassGuitarE2Finger = Utilities::getData("bass_finger_E.wav", FRAMES_PER_SAMPLE*20, false);
   Utilities::normalize(bassGuitarE2Finger);
   stk::StkFrames bassGuitarF2Finger = Utilities::changeFrequency(bassGuitarE2Finger,  41.2, 43.65);
   stk::StkFrames bassGuitarFS2Finger = Utilities::changeFrequency(bassGuitarE2Finger, 41.2, 46.25);
   stk::StkFrames bassGuitarG2Finger = Utilities::changeFrequency(bassGuitarE2Finger,  41.2, 49);
   stk::StkFrames bassGuitarGS2Finger = Utilities::changeFrequency(bassGuitarE2Finger, 41.2, 51.91);
   stk::StkFrames bassGuitarA3Finger = Utilities::changeFrequency(bassGuitarE2Finger,  41.2, 55);
   stk::StkFrames bassGuitarAS3Finger = Utilities::changeFrequency(bassGuitarE2Finger, 41.2, 58.27);
   stk::StkFrames bassGuitarB3Finger = Utilities::changeFrequency(bassGuitarE2Finger,  41.2, 61.74);
   stk::StkFrames bassGuitarC3Finger = Utilities::changeFrequency(bassGuitarE2Finger,  41.2, 65.41);
   stk::StkFrames bassGuitarCS3Finger = Utilities::changeFrequency(bassGuitarE2Finger, 41.2, 69.3);
   stk::StkFrames bassGuitarD3Finger = Utilities::changeFrequency(bassGuitarE2Finger,  41.2, 73.42);
   stk::StkFrames bassGuitarDS3Finger = Utilities::changeFrequency(bassGuitarE2Finger, 41.2, 77.78);
   stk::StkFrames bassGuitarE3Finger = Utilities::changeFrequency(bassGuitarE2Finger,  41.2, 82.41);
   stk::StkFrames bassGuitarF3Finger = Utilities::changeFrequency(bassGuitarE2Finger,  41.2, 87.31);
   stk::StkFrames bassGuitarFS3Finger = Utilities::changeFrequency(bassGuitarE2Finger, 41.2, 92.5);
   stk::StkFrames bassGuitarG3Finger = Utilities::changeFrequency(bassGuitarE2Finger,  41.2, 98);

   for(unsigned int i = 0; i<200; i++)
   {
      stk::StkFrames f;
      samples.push_back(f);
   }
   samples[HI_HAT] = hiHat;
   samples[BASS_DRUM] = bassDrum;
   samples[SNARE_DRUM] = snareDrum;
   samples[CRASH_CYMBOL] = crashCymbol;
   samples[OPEN_HI_HAT] = openHiHat;
   samples[CLAP] = clap;

   samples[BASS_E2] = bassGuitarE2;
   samples[BASS_F2] = bassGuitarF2;
   samples[BASS_FSHARP2] = bassGuitarFS2;
   samples[BASS_G2] = bassGuitarG2;
   samples[BASS_GSHARP2] = bassGuitarGS2;
   samples[BASS_A3] = bassGuitarA3;
   samples[BASS_ASHARP3] = bassGuitarAS3;
   samples[BASS_B3] = bassGuitarB3;
   samples[BASS_C3] = bassGuitarC3;
   samples[BASS_CSHARP3] = bassGuitarCS3;
   samples[BASS_D3] = bassGuitarD3;
   samples[BASS_DSHARP3] = bassGuitarDS3;
   samples[BASS_E3] = bassGuitarE3;
   samples[BASS_F3] = bassGuitarF3;
   samples[BASS_FSHARP3] = bassGuitarFS3;
   samples[BASS_G3] = bassGuitarG3;

   samples[BASS_FINGER_E2] = bassGuitarE2Finger;
   samples[BASS_FINGER_F2] = bassGuitarF2Finger;
   samples[BASS_FINGER_FSHARP2] = bassGuitarFS2Finger;
   samples[BASS_FINGER_G2] = bassGuitarG2Finger;
   samples[BASS_FINGER_GSHARP2] = bassGuitarGS2Finger;
   samples[BASS_FINGER_A3] = bassGuitarA3Finger;
   samples[BASS_FINGER_ASHARP3] = bassGuitarAS3Finger;
   samples[BASS_FINGER_B3] = bassGuitarB3Finger;
   samples[BASS_FINGER_C3] = bassGuitarC3Finger;
   samples[BASS_FINGER_CSHARP3] = bassGuitarCS3Finger;
   samples[BASS_FINGER_D3] = bassGuitarD3Finger;
   samples[BASS_FINGER_DSHARP3] = bassGuitarDS3Finger;
   samples[BASS_FINGER_E3] = bassGuitarE3Finger;
   samples[BASS_FINGER_F3] = bassGuitarF3Finger;
   samples[BASS_FINGER_FSHARP3] = bassGuitarFS3Finger;
   samples[BASS_FINGER_G3] = bassGuitarG3Finger;
}
