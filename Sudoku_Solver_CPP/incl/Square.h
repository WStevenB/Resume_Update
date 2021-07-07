#ifndef SQUARE_H
#define SQUARE_H


class Square {
public:

   // convert from row/column form to composite form
   Square(unsigned char row, unsigned char column, unsigned short value, int sign);

   // convert from composite form to row/column form
   Square(int proposition);



   // composite form
   // abstract value representing row/column/value/sign all in one
   // form actually used by cnf - each row/column/value/sign will have a unique value
   int proposition_;



   // row/column form
   // fields for the assignment of a value 1-9 to a sudoku square given by row and colum
   // a positive sign indicates this value does exist at that square
   // a negative sign indicates that value does NOT exist at that square
   // this form is used in general sudoku processing - non cnf
   unsigned char row_;
   unsigned char column_;
   unsigned short value_;
   int sign_;

};


#endif //SQUARE_H
