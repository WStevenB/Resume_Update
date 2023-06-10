#include "Instrument.h"

#include "Utilities.h"



Instrument::Instrument() {}

Instrument::~Instrument() {}

void Instrument::loadInstruments(std::vector<stk::StkFrames>& samples)
{
   const double FRAMES_PER_SAMPLE = 15000;
   const unsigned int MAX_INSTRUMENTS = 300;

   stk::StkFrames hiHat = Utilities::getData("hihat_alt2.wav", FRAMES_PER_SAMPLE, false);
   stk::StkFrames tunedHiHat = Utilities::changeFrequency(hiHat, 1946.48, 2093.00);

   stk::StkFrames bassDrum = Utilities::getData("kick_thunder.wav", FRAMES_PER_SAMPLE, false);
   stk::StkFrames tunedBassDrum = Utilities::changeFrequency(bassDrum, 45.0575, 49);

   stk::StkFrames snareDrum = Utilities::getData("totori_snare.wav", FRAMES_PER_SAMPLE, false);
   stk::StkFrames tunedSnare = Utilities::changeFrequency(snareDrum, 1191.25, 1174.66);

   stk::StkFrames untunedTom4 = Utilities::getData("tom4.wav", FRAMES_PER_SAMPLE, false);
   stk::StkFrames tom4 = Utilities::changeFrequency(untunedTom4, 145.134, 146.83);
   stk::StkFrames untunedTom3 = Utilities::getData("tom3.wav", FRAMES_PER_SAMPLE, false);
   stk::StkFrames tom3 = Utilities::changeFrequency(untunedTom3, 120.988, 123.47);
   stk::StkFrames untunedTom2 = Utilities::getData("tom2.wav", FRAMES_PER_SAMPLE, false);
   stk::StkFrames tom2 = Utilities::changeFrequency(untunedTom2, 126.643, 130.81);
   stk::StkFrames tom1 = Utilities::getData("tom1_newlow.wav", FRAMES_PER_SAMPLE, false);

   stk::StkFrames clap = Utilities::getData("clap.wav", FRAMES_PER_SAMPLE, false);

   stk::StkFrames openHiHat = Utilities::getData("open_hi_hat.wav", FRAMES_PER_SAMPLE*20, false);
   stk::StkFrames tunedOpenHiHat = Utilities::changeFrequency(openHiHat, 2136.98, 2093.00);

   stk::StkFrames crashCymbol = Utilities::getData("crash_alt.wav", FRAMES_PER_SAMPLE*20, false);
   stk::StkFrames tunedCrash = Utilities::changeFrequency(crashCymbol, 929.956, 1046.50);

   stk::StkFrames bassGuitarE2 = Utilities::getData("bass_pick_E.wav", FRAMES_PER_SAMPLE*20, false);
   stk::StkFrames bassGuitarF2 = Utilities::changeFrequency(bassGuitarE2,  41.2, 43.65);
   stk::StkFrames bassGuitarFS2 = Utilities::changeFrequency(bassGuitarE2, 41.2, 46.25);
   stk::StkFrames bassGuitarG2 = Utilities::changeFrequency(bassGuitarE2,  41.2, 49);
   stk::StkFrames bassGuitarGS2 = Utilities::changeFrequency(bassGuitarE2, 41.2, 51.91);
   stk::StkFrames bassGuitarA2 = Utilities::changeFrequency(bassGuitarE2,  41.2, 55);
   stk::StkFrames bassGuitarAS2 = Utilities::changeFrequency(bassGuitarE2, 41.2, 58.27);
   stk::StkFrames bassGuitarB2 = Utilities::changeFrequency(bassGuitarE2,  41.2, 61.74);
   stk::StkFrames bassGuitarC3 = Utilities::changeFrequency(bassGuitarE2,  41.2, 65.41);
   stk::StkFrames bassGuitarCS3 = Utilities::changeFrequency(bassGuitarE2, 41.2, 69.3);
   stk::StkFrames bassGuitarD3 = Utilities::changeFrequency(bassGuitarE2,  41.2, 73.42);
   stk::StkFrames bassGuitarDS3 = Utilities::changeFrequency(bassGuitarE2, 41.2, 77.78);
   stk::StkFrames bassGuitarE3 = Utilities::changeFrequency(bassGuitarE2,  41.2, 82.41);
   stk::StkFrames bassGuitarF3 = Utilities::changeFrequency(bassGuitarE2,  41.2, 87.31);
   stk::StkFrames bassGuitarFS3 = Utilities::changeFrequency(bassGuitarE2, 41.2, 92.5);
   stk::StkFrames bassGuitarG3 = Utilities::changeFrequency(bassGuitarE2,  41.2, 98);

   stk::StkFrames bassGuitarE2Finger = Utilities::getData("bass_finger_E.wav", FRAMES_PER_SAMPLE*20, false);
   stk::StkFrames bassGuitarF2Finger = Utilities::changeFrequency(bassGuitarE2Finger,  41.2, 43.65);
   stk::StkFrames bassGuitarFS2Finger = Utilities::changeFrequency(bassGuitarE2Finger, 41.2, 46.25);
   stk::StkFrames bassGuitarG2Finger = Utilities::changeFrequency(bassGuitarE2Finger,  41.2, 49);
   stk::StkFrames bassGuitarGS2Finger = Utilities::changeFrequency(bassGuitarE2Finger, 41.2, 51.91);
   stk::StkFrames bassGuitarA2Finger = Utilities::changeFrequency(bassGuitarE2Finger,  41.2, 55);
   stk::StkFrames bassGuitarAS2Finger = Utilities::changeFrequency(bassGuitarE2Finger, 41.2, 58.27);
   stk::StkFrames bassGuitarB2Finger = Utilities::changeFrequency(bassGuitarE2Finger,  41.2, 61.74);
   stk::StkFrames bassGuitarC3Finger = Utilities::changeFrequency(bassGuitarE2Finger,  41.2, 65.41);
   stk::StkFrames bassGuitarCS3Finger = Utilities::changeFrequency(bassGuitarE2Finger, 41.2, 69.3);
   stk::StkFrames bassGuitarD3Finger = Utilities::changeFrequency(bassGuitarE2Finger,  41.2, 73.42);
   stk::StkFrames bassGuitarDS3Finger = Utilities::changeFrequency(bassGuitarE2Finger, 41.2, 77.78);
   stk::StkFrames bassGuitarE3Finger = Utilities::changeFrequency(bassGuitarE2Finger,  41.2, 82.41);
   stk::StkFrames bassGuitarF3Finger = Utilities::changeFrequency(bassGuitarE2Finger,  41.2, 87.31);
   stk::StkFrames bassGuitarFS3Finger = Utilities::changeFrequency(bassGuitarE2Finger, 41.2, 92.5);
   stk::StkFrames bassGuitarG3Finger = Utilities::changeFrequency(bassGuitarE2Finger,  41.2, 98);

   stk::StkFrames untunedPiano_C3 = Utilities::getData("piano_C3.wav", FRAMES_PER_SAMPLE*20, false);
   stk::StkFrames piano_C3 = Utilities::changeFrequency(untunedPiano_C3, 130.81, 130.81);
   stk::StkFrames piano_CS3 = Utilities::changeFrequency(untunedPiano_C3, 130.81, 138.59);
   stk::StkFrames piano_D3 = Utilities::changeFrequency(untunedPiano_C3, 130.81, 146.83);
   stk::StkFrames piano_DS3 = Utilities::changeFrequency(untunedPiano_C3, 130.81, 155.56);
   stk::StkFrames piano_E3 = Utilities::changeFrequency(untunedPiano_C3, 130.81, 164.81);
   stk::StkFrames piano_F3 = Utilities::changeFrequency(untunedPiano_C3, 130.81, 174.61);
   stk::StkFrames piano_FS3 = Utilities::changeFrequency(untunedPiano_C3, 130.81, 185.00);
   stk::StkFrames piano_G3 = Utilities::changeFrequency(untunedPiano_C3, 130.81, 196.00);
   stk::StkFrames piano_GS3 = Utilities::changeFrequency(untunedPiano_C3, 130.81, 207.65);
   stk::StkFrames piano_A3 = Utilities::changeFrequency(untunedPiano_C3, 130.81, 220.00);
   stk::StkFrames piano_AS3 = Utilities::changeFrequency(untunedPiano_C3, 130.81, 233.08);
   stk::StkFrames piano_B3 = Utilities::changeFrequency(untunedPiano_C3, 130.81, 246.94);
   stk::StkFrames piano_C4 = Utilities::changeFrequency(untunedPiano_C3, 130.81, 261.63);
   stk::StkFrames piano_CS4 = Utilities::changeFrequency(untunedPiano_C3, 130.81, 277.18);
   stk::StkFrames piano_D4 = Utilities::changeFrequency(untunedPiano_C3, 130.81, 293.66);
   stk::StkFrames piano_DS4 = Utilities::changeFrequency(untunedPiano_C3, 130.81, 311.13);
   stk::StkFrames piano_E4 = Utilities::changeFrequency(untunedPiano_C3, 130.81, 329.63);
   stk::StkFrames piano_F4 = Utilities::changeFrequency(untunedPiano_C3, 130.81, 349.23);
   stk::StkFrames piano_FS4 = Utilities::changeFrequency(untunedPiano_C3, 130.81, 369.99);
   stk::StkFrames piano_G4 = Utilities::changeFrequency(untunedPiano_C3, 130.81, 392.00);
   stk::StkFrames piano_GS4 = Utilities::changeFrequency(untunedPiano_C3, 130.81, 415.30);
   stk::StkFrames piano_A4 = Utilities::changeFrequency(untunedPiano_C3, 130.81, 440.00);
   stk::StkFrames piano_AS4 = Utilities::changeFrequency(untunedPiano_C3, 130.81, 466.16);
   stk::StkFrames piano_B4 = Utilities::changeFrequency(untunedPiano_C3, 130.81, 493.88);
   stk::StkFrames piano_C5 = Utilities::changeFrequency(untunedPiano_C3, 130.81, 523.25);
   stk::StkFrames piano_CS5 = Utilities::changeFrequency(untunedPiano_C3, 130.81, 554.37);
   stk::StkFrames piano_D5 = Utilities::changeFrequency(untunedPiano_C3, 130.81, 587.33);
   stk::StkFrames piano_DS5 = Utilities::changeFrequency(untunedPiano_C3, 130.81, 622.25);
   stk::StkFrames piano_E5 = Utilities::changeFrequency(untunedPiano_C3, 130.81, 659.25);



   for(unsigned int i = 0; i<MAX_INSTRUMENTS; i++)
   {
      stk::StkFrames f;
      samples.push_back(f);
   }
   samples[HI_HAT] = tunedHiHat;
   samples[BASS_DRUM] = tunedBassDrum;
   samples[SNARE_DRUM] = tunedSnare;
   samples[TOM4] = tom4;
   samples[TOM3] = tom3;
   samples[TOM2] = tom2;
   samples[TOM1] = tom1;
   samples[CRASH_CYMBOL] = tunedCrash;
   samples[OPEN_HI_HAT] = tunedHiHat;
   samples[CLAP] = clap;

   samples[BASS_E2] = bassGuitarE2;
   samples[BASS_F2] = bassGuitarF2;
   samples[BASS_FSHARP2] = bassGuitarFS2;
   samples[BASS_G2] = bassGuitarG2;
   samples[BASS_GSHARP2] = bassGuitarGS2;
   samples[BASS_A2] = bassGuitarA2;
   samples[BASS_ASHARP2] = bassGuitarAS2;
   samples[BASS_B2] = bassGuitarB2;
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
   samples[BASS_FINGER_A2] = bassGuitarA2Finger;
   samples[BASS_FINGER_ASHARP2] = bassGuitarAS2Finger;
   samples[BASS_FINGER_B2] = bassGuitarB2Finger;
   samples[BASS_FINGER_C3] = bassGuitarC3Finger;
   samples[BASS_FINGER_CSHARP3] = bassGuitarCS3Finger;
   samples[BASS_FINGER_D3] = bassGuitarD3Finger;
   samples[BASS_FINGER_DSHARP3] = bassGuitarDS3Finger;
   samples[BASS_FINGER_E3] = bassGuitarE3Finger;
   samples[BASS_FINGER_F3] = bassGuitarF3Finger;
   samples[BASS_FINGER_FSHARP3] = bassGuitarFS3Finger;
   samples[BASS_FINGER_G3] = bassGuitarG3Finger;

   samples[PIANO_C3] = piano_C3;
   samples[PIANO_CS3] = piano_CS3;
   samples[PIANO_D3] = piano_D3;
   samples[PIANO_DS3] = piano_DS3;
   samples[PIANO_E3] = piano_E3;
   samples[PIANO_F3] = piano_F3;
   samples[PIANO_FS3] = piano_FS3;
   samples[PIANO_G3] = piano_G3;
   samples[PIANO_GS3] = piano_GS3;
   samples[PIANO_A3] = piano_A3;
   samples[PIANO_AS3] = piano_AS3;
   samples[PIANO_B3] = piano_B3;
   samples[PIANO_C4] = piano_C4;
   samples[PIANO_CS4] = piano_CS4;
   samples[PIANO_D4] = piano_D4;
   samples[PIANO_DS4] = piano_DS4;
   samples[PIANO_E4] = piano_E4;
   samples[PIANO_F4] = piano_F4;
   samples[PIANO_FS4] = piano_FS4;
   samples[PIANO_G4] = piano_G4;
   samples[PIANO_GS4] = piano_GS4;
   samples[PIANO_A4] = piano_A4;
   samples[PIANO_AS4] = piano_AS4;
   samples[PIANO_B4] = piano_B4;
   samples[PIANO_C5] = piano_C5;
   samples[PIANO_CS5] = piano_CS5;
   samples[PIANO_D5] = piano_D5;
   samples[PIANO_DS5] = piano_DS5;
   samples[PIANO_E5] = piano_E5;


}
