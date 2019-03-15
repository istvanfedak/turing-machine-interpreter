#ifndef PRINT_HPP
#define PRINT_HPP

// Colors!!!
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RST   "\x1B[0m"  // reset

#include <stdio.h>
#include "State.hpp"
#include "StateTable.hpp"
#include "Tape.hpp"

// print character and literals
void fprintChar(FILE * ptr, const char & chr);

// print a state
void printState(const State & state);

// print a state table
void printTable(const StateTable & stateTable);

// print hidden literals
void printChar(const char & chr);

// prints the tape
// I couldn't make a print method that involced const
void printTape(Tape & tape);

// print the final remating contents of the tape
// on the right and left
void printFinalTape(Tape & tape);

// prints curser for tape
void printCurser(Tape & tape);

// prints the steps that the shell makes to reach the answer
void printStep(const StateTable & stateTable,
               Tape & tape, const int & curState);

// after being done, print results
void printFinalInfo(const StateTable & stateTable, Tape & tape, 
                    const int & curState, const int & stepCount);

// prints errors when user doesn't provide the correct input
void printInputError();

#endif /* PRINT_HPP */
