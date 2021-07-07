#include "Solver.h"


int main(int argc, char *argv[]) {

   unsigned int puzzleId = 1;
   if(argc > 1) {
      if(argv[1][0] == '2') puzzleId = 2;
      else if(argv[1][0] == '3') puzzleId = 3;
   }

   Solver sudoku(puzzleId);
   sudoku.solvePuzzle();

   return 1;
}
