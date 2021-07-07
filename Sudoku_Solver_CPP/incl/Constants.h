#ifndef CONSTANTS_H
#define CONSTANTS_H

static const unsigned int SUDOKU_WIDTH = 9;
static const unsigned int BOX_WIDTH = 3;
static const unsigned int BOX_1_START = 0;
static const unsigned int BOX_2_START = 3;
static const unsigned int BOX_3_START = 6;

static const unsigned int BLANK_VALUE = 0;
static const unsigned int VALUE_START = 1;
static const unsigned int VALUE_LIMIT = 10;

static const int POSITIVE_PROPOSITION = 1;
static const int NEGATIVE_PROPOSITION = -1;

// max possible guesses is 9 (1-9 values) times 81 sudoku squares
static const unsigned int RECURSION_MAX = 729;

// easy
static const unsigned int SUDOKU_1 [81] = {0, 5, 7, 0, 0, 6, 0, 1, 0,
                                           0, 0, 0, 0, 2, 0, 8, 0, 0,
                                           2, 0, 9, 0, 4, 1, 0, 0, 0,
                                           0, 0, 0, 9, 7, 0, 4, 0, 0,
                                           6, 0, 2, 5, 3, 0, 7, 8, 1,
                                           4, 7, 3, 6, 1, 0, 0, 9, 2,
                                           5, 0, 0, 0, 0, 7, 0, 0, 0,
                                           0, 0, 0, 0, 6, 0, 0, 2, 5,
                                           0, 2, 4, 0, 0, 0, 6, 0, 8};

// hard
static const unsigned int SUDOKU_2 [81] = {0, 7, 0, 0, 0, 8, 0, 0, 0,
                                           3, 0, 0, 5, 0, 0, 0, 0, 0,
                                           0 ,0, 6, 7, 0, 0, 9, 1, 0,
                                           0, 0, 0, 0, 1, 3, 0, 0, 0,
                                           0, 9, 1, 0, 0, 0, 0, 3, 0,
                                           7, 0, 3, 0, 0, 0, 0, 0, 2,
                                           0 ,0, 0, 6, 0, 0, 0, 9, 0,
                                           8, 0, 0, 0, 3, 0, 0, 0, 6,
                                           0, 0, 2, 0, 0, 7, 3, 0, 5};

// expert
static const unsigned int SUDOKU_3 [81] = {0, 8, 0, 0, 0, 0, 0, 0, 0,
                                           0, 0, 7, 0, 0, 0, 8, 0, 3,
                                           0, 3, 0, 6, 0, 0, 0, 0, 9,
                                           0, 0, 0, 9, 8, 3, 0, 0, 0,
                                           7, 4, 0, 0, 0, 6, 0, 0, 0,
                                           2, 0, 0, 0, 0, 7, 0, 0, 0,
                                           0, 0, 0, 0, 9, 0, 0, 6, 0,
                                           0, 0, 0, 1, 0, 0, 7, 0, 0,
                                           5, 0, 1, 0, 0, 0, 0, 4, 0};


#endif //CONSTANT_S
