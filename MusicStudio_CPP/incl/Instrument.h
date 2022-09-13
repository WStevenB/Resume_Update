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

#define BASS_E2       100
#define BASS_F2       101
#define BASS_FSHARP2  102
#define BASS_G2       103
#define BASS_GSHARP2  104
#define BASS_A3       105
#define BASS_ASHARP3  106
#define BASS_B3       107
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
#define BASS_FINGER_A3       121
#define BASS_FINGER_ASHARP3  122
#define BASS_FINGER_B3       123
#define BASS_FINGER_C3       124
#define BASS_FINGER_CSHARP3  125
#define BASS_FINGER_D3       126
#define BASS_FINGER_DSHARP3  127
#define BASS_FINGER_E3       128
#define BASS_FINGER_F3       129
#define BASS_FINGER_FSHARP3  130
#define BASS_FINGER_G3       131


class Instrument
{
public:

   Instrument();
   ~Instrument();

   static void loadInstruments(std::vector<stk::StkFrames>& samples);
};














#endif  // INSTRUMENT_H
