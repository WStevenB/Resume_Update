#ifndef CNF_H
#define CNF_H

#include <deque>
#include <set>

class CNF {
public:

   CNF();


   // appends new set of propositions
   void addProps(std::deque<int> props);

   // returns previously undisclosed singular propositions - truths
   std::deque<int> getSingles();

   // delete all instances of this proposition
   void eliminate(int single);

   // performs all needed actions for an instance of sudoku specialized cnf reduction
   void reduce();

   // displays propositions in terminal window - for debugging
   void print();



   // stores all cnf propositions
   std::deque< std::deque<int> > props_;

   // false if the same positive and negative singular proposition exist
   bool isValid_;


private:

   // singular propositions already disclosed
   std::set<int> oldPropositions_;
};


#endif //CNF_H
