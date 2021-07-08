#include "Board.h"

#include <iostream>

#include "Constants.h"


Board::Board(const unsigned int* board) {

   numberRounds_ = 0;
   recursionLevel_ = 0;

   // populate local field according to user input for which sudoku to solve
   unsigned int count = 0;
   for(unsigned int i = 0; i<SUDOKU_WIDTH; i++) {
      std::vector<unsigned int> row;
      for(unsigned int ii = 0; ii<SUDOKU_WIDTH; ii++) {
         row.push_back(board[count]);
         count++;
      }
      board_.push_back(row);
   }

   // make propositions that each value 1-9 is present in each row and each column
   for(unsigned int v = VALUE_START; v<VALUE_LIMIT; v++) {

      for(unsigned int i = 0; i<SUDOKU_WIDTH; i++) {
         std::deque<int> rowPropositions;
         std::deque<int> columnPropositions;

         for(unsigned int ii = 0; ii<SUDOKU_WIDTH; ii++) {
            Square sRow(i, ii, v, POSITIVE_PROPOSITION);
            rowPropositions.push_back(sRow.proposition_);

            Square sCol(ii, i, v, POSITIVE_PROPOSITION);
            columnPropositions.push_back(sCol.proposition_);
         }

         cnf_.addProps(rowPropositions);
         cnf_.addProps(columnPropositions);
      }
   }

   // make propositions that each value 1-9 is present in each box
   for(unsigned int v = VALUE_START; v<VALUE_LIMIT; v++) {
      for(unsigned int i = 0; i<SUDOKU_WIDTH; i+=BOX_WIDTH) {
         for(unsigned int ii = 0; ii<SUDOKU_WIDTH; ii+=BOX_WIDTH) {
            std::deque<int> boxPropositions;
            for(unsigned int iii = i; iii<i+BOX_WIDTH; iii++) {
               for(unsigned int iiii = ii; iiii<ii+BOX_WIDTH; iiii++) {
                  Square sBox(iii, iiii, v, POSITIVE_PROPOSITION);
                  boxPropositions.push_back(sBox.proposition_);
               }
            }
            cnf_.addProps(boxPropositions);
         }
      }
   }

   // make propositions for each given value in the starting puzzle
   for(unsigned int i = 0; i<SUDOKU_WIDTH; i++) {
      for(unsigned int ii = 0; ii<SUDOKU_WIDTH; ii++) {
         if(board_[i][ii] != BLANK_VALUE) {
            Square newSquare(i, ii, board_[i][ii], POSITIVE_PROPOSITION);
            std::deque<int> newProposition;
            newProposition.push_back(newSquare.proposition_);
            cnf_.addProps(newProposition);
            newPropositions(newSquare.proposition_);
         }
      }
   }
}


// called when a value is assigned to a square
void Board::newPropositions(int newSquare) {

   Square square(newSquare);

   // make propositions that all other values at this square are false
   for(unsigned int v = VALUE_START; v<VALUE_LIMIT; v++) {
      if(v == square.value_) continue;
      Square valueNegative(square.row_, square.column_, v, NEGATIVE_PROPOSITION);
      std::deque<int> valueProp;
      valueProp.push_back(valueNegative.proposition_);
      cnf_.addProps(valueProp);
   }

   // make propositions that this value is false at every other square in this row
   for(unsigned int i = 0; i<SUDOKU_WIDTH; i++) {
      if(i == square.column_) continue;
      Square rowNegative(square.row_, i, square.value_, NEGATIVE_PROPOSITION);
      std::deque<int> rowPropositions;
      rowPropositions.push_back(rowNegative.proposition_);
      cnf_.addProps(rowPropositions);
   }

   // make propositions that this value is false at every other square in this column
   for(unsigned int i = 0; i<SUDOKU_WIDTH; i++) {
      if(i == square.row_) continue;
      Square columnNegative(i, square.column_, square.value_, NEGATIVE_PROPOSITION);
      std::deque<int> columnPropositions;
      columnPropositions.push_back(columnNegative.proposition_);
      cnf_.addProps(columnPropositions);
   }

   // make propositions that this value is false at every other square in this box
   unsigned int startingRow = BOX_1_START;
   if(square.row_ >= BOX_2_START && square.row_ < BOX_3_START) startingRow = BOX_2_START;
   else if(square.row_ >= BOX_3_START && square.row_ < SUDOKU_WIDTH) startingRow = BOX_3_START;

   unsigned int startingColumn = BOX_1_START;
   if(square.column_ >= BOX_2_START && square.column_ < BOX_3_START) startingColumn = BOX_2_START;
   else if(square.column_ >= BOX_3_START && square.column_ < SUDOKU_WIDTH) startingColumn = BOX_3_START;

   for(unsigned int i = startingRow; i<startingRow+BOX_WIDTH; i++) {
      for(unsigned int ii = startingColumn; ii<startingColumn+BOX_WIDTH; ii++) {
         if(i == square.row_ && ii == square.column_) continue;
         Square boxNegative(i, ii, square.value_, NEGATIVE_PROPOSITION);
         std::deque<int> boxPropositions;
         boxPropositions.push_back(boxNegative.proposition_);
         cnf_.addProps(boxPropositions);
      }
   }
}


// called when reducing propositions fails to reveal truths
// smallest set of positive, previously unguessed propositions is desired
// because the true proposition is likely to be found quicker in a smaller set
std::deque<int> Board::getBestGuesses() {

   std::deque<int> output;

   unsigned int smallestSize = 2;
   bool keepGoing = true;
   while(keepGoing && smallestSize < VALUE_LIMIT) {
      for(unsigned int i = 0; i<cnf_.props_.size(); i++) {
         Square s(cnf_.props_[i][0]);
         if(s.sign_ == POSITIVE_PROPOSITION && cnf_.props_[i].size() == smallestSize) {
            unsigned int previousSize = pastGuesses_.size();
            for(unsigned int ii = 0; ii<cnf_.props_[i].size(); ii++) pastGuesses_.insert(cnf_.props_[i][ii]);
            if(previousSize != pastGuesses_.size()) {
               output = cnf_.props_[i];
               keepGoing = false;
               break;
            }
         }
      }
      smallestSize++;
   }

   return output;
}


// true if board contains no blank values and is valid
bool Board::isSolved() {

   for(unsigned int i = 0; i<SUDOKU_WIDTH; i++) {
      for(unsigned int ii = 0; ii<SUDOKU_WIDTH; ii++) {
         if(board_[i][ii] == BLANK_VALUE) return false;
      }
   }
   return isValid();
}


// false if board contains duplicate values in a row, column, or box
// may happen when bad guesses are made and indicates board should be discarded
bool Board::isValid() {

   for(unsigned int i = 0; i<SUDOKU_WIDTH; i++) {

      std::deque<int> allRowValues;
      std::set<int> uniqueRowValues;

      std::deque<int> allColValues;
      std::set<int> uniqueColValues;

      for(unsigned int ii = 0; ii<SUDOKU_WIDTH; ii++) {

         if(board_[i][ii] > BLANK_VALUE) {
            allRowValues.push_back(board_[i][ii]);
            uniqueRowValues.insert(board_[i][ii]);


         }

         if(board_[ii][i] > BLANK_VALUE) {
            allColValues.push_back(board_[ii][i]);
            uniqueColValues.insert(board_[ii][i]);
         }
      }

      if(allRowValues.size() != uniqueRowValues.size()) return false;
      if(allColValues.size() != uniqueColValues.size()) return false;
   }

   for(unsigned int i = 0; i<SUDOKU_WIDTH; i+=BOX_WIDTH) {
      for(unsigned int ii = 0; ii<SUDOKU_WIDTH; ii+=BOX_WIDTH) {

         std::deque<int> allBoxValues;
         std::set<int> uniqueBoxValues;

         for(unsigned int iii = i; iii<i+BOX_WIDTH; iii++) {
            for(unsigned int iiii = ii; iiii<ii+BOX_WIDTH; iiii++) {

               if(board_[iii][iiii] > BLANK_VALUE) {
                  allBoxValues.push_back(board_[iii][iiii]);
                  uniqueBoxValues.insert(board_[iii][iiii]);
               }
            }
         }

         if(allBoxValues.size() != uniqueBoxValues.size()) return false;
      }
   }

   return true;

}


// make propositions for a singular blank value in a row, column, or box
// it must be the missing value 1-9
std::deque<int> Board::getSingleEmpties() {

   std::deque<int> output;

   for(unsigned int i = 0; i<SUDOKU_WIDTH; i++) {

      unsigned int rowCount [VALUE_LIMIT];
      unsigned int colCount [VALUE_LIMIT];
      for(unsigned int v = BLANK_VALUE; v<VALUE_LIMIT; v++) {
         rowCount[v] = 0;
         colCount[v] = 0;
      }

      unsigned int rowZero = 0;
      unsigned int colZero = 0;
      unsigned int rowValue = 0;
      unsigned int colValue = 0;

      // loop through each row/column
      // count each time a value is present
      // also store the index of a zero value
      for(unsigned int ii = 0; ii<SUDOKU_WIDTH; ii++) {
         rowCount[ board_[i][ii] ] ++;
         colCount[ board_[ii][i] ] ++;

         if(board_[i][ii] == BLANK_VALUE) rowZero = ii;
         if(board_[ii][i] == BLANK_VALUE) colZero = i;
      }

      // if there is only one zero in this row
      // find the missing value and make proposition
      if(rowCount[0] == 1) {
         for(unsigned int v = VALUE_START; v<VALUE_LIMIT; v++) {
            if(rowCount[v] == 0) rowValue = v;
         }
         Square rSquare(i, rowZero, rowValue, POSITIVE_PROPOSITION);
         output.push_back(rSquare.proposition_);
      }

      // if there is only one zero in this column
      // find the missing value and make proposition
      if(colCount[0] == 1) {
         for(unsigned int v = VALUE_START; v<VALUE_LIMIT; v++) {
            if(colCount[v] == 0) colValue = v;
         }
         Square cSquare(colZero, i, colValue, POSITIVE_PROPOSITION);
         output.push_back(cSquare.proposition_);
      }
   }

   // loop through each box
   // count each time a value is present
   // also store the row/column of a zero value
   for(unsigned int i = 0; i<SUDOKU_WIDTH; i+=BOX_WIDTH) {
      for(unsigned int ii = 0; ii<SUDOKU_WIDTH; ii+=BOX_WIDTH) {

         unsigned int boxCount [VALUE_LIMIT];
         for(unsigned int v = BLANK_VALUE; v<VALUE_LIMIT; v++) boxCount[v] = 0;

         unsigned int rowZero = 0;
         unsigned int colZero = 0;
         unsigned int boxValue = 0;

         for(unsigned int iii = i; iii<i+BOX_WIDTH; iii++) {
            for(unsigned int iiii = ii; iiii<ii+BOX_WIDTH; iiii++) {
               boxCount[ board_[iii][iiii] ]++;
               if(board_[iii][iiii] == BLANK_VALUE) {
                  rowZero = iii;
                  colZero = iiii;
               }
            }
         }

         // if there is only one zero in this box
         // find the missing value and make proposition
         if(boxCount[0] == 1) {
            for(unsigned int v = VALUE_START; v<VALUE_LIMIT; v++) {
               if(boxCount[v] == 0) boxValue = v;
            }
            Square bSquare(rowZero, colZero, boxValue, POSITIVE_PROPOSITION);
            output.push_back(bSquare.proposition_);
         }
      }
   }

   return output;
}


// applies propositions found in getSingleEmpties()
bool Board::applySingleEmpties() {

   std::deque<int> empties = getSingleEmpties();

   for(unsigned int i = 0; i<empties.size(); i++) {

      Square s(empties[i]);

      if(board_[s.row_][s.column_] == 0) {

         board_[s.row_][s.column_] = s.value_;
         std::deque<int> prop;
         prop.push_back(empties[i]);
         cnf_.addProps(prop);
         newPropositions(empties[i]);
      }
   }

   return isValid();
}


// displays representation of sudoku board in terminal window
void Board::print() {

   if(isSolved()) std::cout << "Sudoku puzzle was solved!!!" << std::endl << std::endl;
   else std::cout << "Sudoku puzzle is not solved yet..." << std::endl << std::endl;

   for(int i = SUDOKU_WIDTH-1; i>=0; i--) {
      for(unsigned int ii = 0; ii<SUDOKU_WIDTH; ii++) {
         std::cout << board_[i][ii] << ", ";
      }
      std::cout << std::endl;
   }
}
