#include "Square.h"

#include "Constants.h"


// convert from row/column form to composite form
Square::Square(unsigned char row, unsigned char column, unsigned short value, int sign) {

   row_ = row;
   column_ = column;
   value_ = value;
   sign_ = sign;

   unsigned int composite = 0;
   unsigned short* shortPtr = reinterpret_cast<unsigned short*>(&composite);
   unsigned char* charPtr = reinterpret_cast<unsigned char*>(&composite);
   shortPtr[0] = value;
   charPtr[2] = row;
   charPtr[3] = column;

   proposition_ = static_cast<int>(composite) * sign;
}


// convert from composite form to row/column form
Square::Square(int proposition) {

   proposition_ = proposition;

   sign_ = POSITIVE_PROPOSITION;
   if(proposition < 0) {
      proposition *= -1;
      sign_ = NEGATIVE_PROPOSITION;
   }
   unsigned int composite = static_cast<unsigned int>(proposition);
   unsigned short* shortPtr = reinterpret_cast<unsigned short*>(&composite);
   unsigned char* charPtr = reinterpret_cast<unsigned char*>(&composite);
   value_ = shortPtr[0];
   row_ = charPtr[2];
   column_ = charPtr[3];
}
