#include "Solver.h"

#include <iostream>

#include "Constants.h"


// set particular board as determined by user input
Solver::Solver(unsigned int puzzleId) {

   current_ = 0;

   const unsigned int* idPtr = SUDOKU_1;
   if(puzzleId == 2) idPtr = SUDOKU_2;
   else if(puzzleId == 3) idPtr = SUDOKU_3;

   Board b(idPtr);
   boards_.push_back(b);
   boards_[current_].cnf_.reduce();
}


// delete the current invalid board and switch to different branch of guess tree
bool Solver::switchBoards() {

   boards_.erase(boards_.begin() + current_);

   // should abort all sudoku processing if no more boards remain
   if(boards_.size() == 0) return false;

   // find new board
   // assumption that board with most cnf reductions and guesses is closet to being solved
   // not true if an early bad guess was made - could explore other heuristics
   current_ = 0;
   unsigned int highestRounds = 0;
   for(unsigned int i = 0; i<boards_.size(); i++) {
      if(boards_[i].numberRounds_ > highestRounds) {
         highestRounds = boards_[i].numberRounds_;
         current_ = i;
      }
   }

   // successfully switched boards
   return true;
}


// primary sudoku solving algorithm
void Solver::solvePuzzle() {

   unsigned int count = 0;
   while(boards_[current_].isSolved() == false) {

      // increment total rounds and rounds for this particular board
      boards_[current_].numberRounds_++;
      boards_[current_].print();
      std::cout << "Round: " << count++ << std::endl;


      // attempt to switch boards if current one is invalid
      if(boards_[current_].cnf_.isValid_ == false || boards_[current_].applyEmpties() == false) {
         if(switchBoards() == false) break;
      }


      else {

         // find any truths revealed by previous cnf reduction
         std::deque<int> newSquares = boards_[current_].cnf_.getSingles();


         if(newSquares.size() > 0) {

            // attempt to assign these truths to the actual sudoku board, make new propositions based on them, and then reduce cnf
            // abort if unable to do so - bad guess was made at some previous point in time
            for(unsigned int i = 0; i<newSquares.size(); i++) {
               Square s(newSquares[i]);
               if(s.sign_ == POSITIVE_PROPOSITION) {
                  if(boards_[current_].board_[s.row_][s.column_] != BLANK_VALUE && boards_[current_].board_[s.row_][s.column_] != s.value_) {
                     boards_[current_].cnf_.isValid_ = false;
                     std::cout << "Not valid : " << (unsigned int) s.row_ << " " << (unsigned int) s.column_ << " " << s.value_ << " " << s.sign_ << std::endl;
                     continue;
                  }
                  else {
                     boards_[current_].board_[s.row_][s.column_] = s.value_;
                     boards_[current_].newPropositions(newSquares[i]);
                  }
               }
            }
            boards_[current_].cnf_.reduce();
         }


         // abort all processing due to excessive recursion probably caused by malformed puzzle
         // nothing is possible to gain by exceeding 9 (1-9 values) times 81 sudoku squares
         else if(boards_[current_].recursionLevel_ > RECURSION_MAX) {
            break;
         }


         // no truths were revealed by lastest cnf reduction - guesses must be made
         // smallest set guesses with a unique value is found
         // each is applied to a new board and recursion levels incremented - current board is deleted
         else {
            bool guessMade = false;
            while(guessMade == false) {

               // continue to get new guesses if none in first round pan out
               // bad sign if more than one round is needed - board likely invalid
               // it's possible that the board is definitely invalid and should be immediately switched out and deleted
               std::deque<int> guesses = boards_[current_].getBestGuesses();
               if(guesses.size() > 0) {
                  for(unsigned int i = 0; i<guesses.size(); i++) {
                     Board guessBoard = boards_[current_];
                     Square guessSquare(guesses[i]);

                     if(guessSquare.sign_ == POSITIVE_PROPOSITION && guessBoard.board_[guessSquare.row_][guessSquare.column_] == BLANK_VALUE) {

                        guessMade = true;
                        guessBoard.board_[guessSquare.row_][guessSquare.column_] = guessSquare.value_;

                        if(guessBoard.isValid()) {

                           // guess appears valid so save this board for further processing
                           guessBoard.recursionLevel_++;
                           std::deque<int> props;
                           props.push_back(guesses[i]);
                           guessBoard.cnf_.addProps(props);
                           guessBoard.newPropositions(guesses[i]);
                           guessBoard.cnf_.reduce();
                           boards_.push_back(guessBoard);
                        }
                     }
                  }
               }
               else {
                  // abort loop if no guesses can be found
                  break;
               }
            }

            // after guesses made, now find board estimated to be closest to solving
            if(switchBoards() == false) break;
         }
      }
   }

   // sudoku processing completed - find out if it was successful or not
   if(boards_.size() > 0) boards_[current_].print();
   else std::cout << "No solution found to Sudoku puzzle..." << std::endl;
}
