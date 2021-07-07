#ifndef SOLVER_H
#define SOLVER_H

#include <deque>

#include "Board.h"

class Solver {
public:

   // set particular board as determined by user input
   Solver(unsigned int puzzleId);


   // delete the current invalid board and switch to different branch of guess tree
   bool switchBoards();

   // primary sudoku solving algorithm
   void solvePuzzle();



   // set of sudoku boards branched at different guesses
   std::deque<Board> boards_;

   // index of currently processed board in boards_
   unsigned int current_;
};




#endif //SOLVER_H
