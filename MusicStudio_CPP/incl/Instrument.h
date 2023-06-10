#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include "Stk.h"

#include <vector>


typedef unsigned int INSTRUMENT;

#define BASS_DRUM     0
#define SNARE_DRUM    1
#define HI_HAT        2
#define CYMBOL        3
#define CRASH_CYMBOL  4
#define CLAP          5
#define OPEN_HI_HAT   6
#define TOM4          7
#define TOM3          8
#define TOM2          9
#define TOM1          10

#define BASS_E2       100
#define BASS_F2       101
#define BASS_FSHARP2  102
#define BASS_G2       103
#define BASS_GSHARP2  104
#define BASS_A2       105
#define BASS_ASHARP2  106
#define BASS_B2       107
#define BASS_C3       108
#define BASS_CSHARP3  109
#define BASS_D3       110
#define BASS_DSHARP3  111
#define BASS_E3       112
#define BASS_F3       113
#define BASS_FSHARP3  114
#define BASS_G3       115

#define BASS_FINGER_E2       116
#define BASS_FINGER_F2       117
#define BASS_FINGER_FSHARP2  118
#define BASS_FINGER_G2       119
#define BASS_FINGER_GSHARP2  120
#define BASS_FINGER_A2       121
#define BASS_FINGER_ASHARP2  122
#define BASS_FINGER_B2       123
#define BASS_FINGER_C3       124
#define BASS_FINGER_CSHARP3  125
#define BASS_FINGER_D3       126
#define BASS_FINGER_DSHARP3  127
#define BASS_FINGER_E3       128
#define BASS_FINGER_F3       129
#define BASS_FINGER_FSHARP3  130
#define BASS_FINGER_G3       131

#define PIANO_C3  200
#define PIANO_CS3  201
#define PIANO_D3  202
#define PIANO_DS3  203
#define PIANO_E3  204
#define PIANO_F3  205
#define PIANO_FS3  206
#define PIANO_G3  207
#define PIANO_GS3  208
#define PIANO_A3  209
#define PIANO_AS3  210
#define PIANO_B3  211
#define PIANO_C4  212
#define PIANO_CS4  213
#define PIANO_D4  214
#define PIANO_DS4  215
#define PIANO_E4  216
#define PIANO_F4  217
#define PIANO_FS4  218
#define PIANO_G4  219
#define PIANO_GS4  220
#define PIANO_A4  221
#define PIANO_AS4  222
#define PIANO_B4  223
#define PIANO_C5  224
#define PIANO_CS5  225
#define PIANO_D5  226
#define PIANO_DS5  227
#define PIANO_E5  228


class Instrument
{
public:

   Instrument();
   ~Instrument();

   static void loadInstruments(std::vector<stk::StkFrames>& samples);
};














#endif  // INSTRUMENT_H
