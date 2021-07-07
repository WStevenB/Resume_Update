#ifndef BOARD_H
#define BOARD_H

#include <vector>

#include "Square.h"
#include "CNF.h"


class Board {
public:

   Board(const unsigned int* board);


   // called when a value 1-9 is assigned to a square
   void newPropositions(int newSquare);

   // called when reducing propositions fails to reveal truths
   std::deque<int> getBestGuesses();

   // true if board contains no blank values and is valid
   bool isSolved();

   // false if a duplicate value is found in a row, column, or box
   bool isValid();

   // searches for a single blank value in any row, column, or box
   std::deque<int> getSingleEmpties();

   // applies propositions from getSingleEmpties()
   bool applyEmpties();

   // displays sudoku board in terminal window
   void print();



   // two dimensional representation of known sudoku values [row][column]
   std::vector< std::vector<unsigned int> > board_;

   // contains propositions for squares' values
   CNF cnf_;

   // times propositions have been reduced and guesses made
   unsigned int numberRounds_;

   // depth of recursion branch - used to kill processing for bad puzzles and "infinite" loop
   unsigned int recursionLevel_;

   // stores all past guesses made in order to find unique guesses
   std::set<int> pastGuesses_;
};


#endif //BOARD_H
