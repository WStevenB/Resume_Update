#include "CNF.h"

#include <iterator>
#include <iostream>

#include "Square.h"


CNF::CNF() {

   isValid_ = true;
}


// appends new set of propositions
void CNF::addProps(std::deque<int> props) {

   props_.push_back(props);
}


// returns previously undisclosed singular propositions - truths
std::deque<int> CNF::getSingles() {

   std::deque<int> singles;

   for(unsigned int i = 0; i<props_.size(); i++) {
      if(props_[i].size() == 1) {
         unsigned int oldSize = oldPropositions_.size();
         oldPropositions_.insert(props_[i][0]);
         if(oldSize != oldPropositions_.size()) singles.push_back(props_[i][0]);
      }
   }

   return singles;
}


// delete all instances of this proposition
void CNF::eliminate(int single) {

   for(unsigned int i = 0; i<props_.size(); i++) {

      bool isSingle = false;
      if(props_[i].size() == 1) isSingle = true;

      for(int ii = props_[i].size()-1; ii>=0; ii--) {
         if(props_[i][ii] == single) {
            props_[i].erase(props_[i].begin() + (ii));
            if(isSingle) {
               // set cnf to invalid because opposing singular propositions were found
               isValid_ = false;
            }
         }
      }
   }
}


// performs all needed actions for an instance of sudoku specialized cnf reduction
// generic cnf procedures for removing empty propositions and opposites within the same set are not needed
void CNF::reduce() {

   std::deque<int> singles;
   for(unsigned int i = 0; i<props_.size(); i++) {
      if(props_[i].size() == 1)singles.push_back(props_[i][0]);
   }

   for(unsigned int i = 0; i<singles.size(); i++) eliminate(singles[i] * -1);
}


// displays propositions in terminal window - for debugging
void CNF::print() {

   for(unsigned int i = 0; i<props_.size(); i++) {
      for(unsigned int ii = 0; ii<props_[i].size(); ii++) {
         Square s (props_[i][ii]);
         std::cout << "(" << (unsigned int)s.row_ << " " << (unsigned int) s.column_ << " " << s.value_ << " " << s.sign_ << "), ";
      }
      std::cout << std::endl;
   }
}
