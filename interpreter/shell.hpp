#ifndef SHELL_HPP
#define SHELL_HPP
#include <stdio.h>
#include <iostream>
#include "StateTable.hpp"
#include "getNewState.hpp"
#include "Tape.hpp"
#include "print.hpp"
#include "read.hpp" // for user input

// update the tape given the current state
void updateTape(const StateTable & stateTable,
                Tape & tape, const int & curState);

// interpret user input
void interpretInput(const std::vector<std::string> & tokens,
                    Tape & tape, bool & run, bool & quiet,
                    bool & until, bool & halt, bool & redo,
                    std::string &tillState);

// check to see if specified state was reached
void checkUntillState(const StateTable & stateTable, const int & curState,
                    bool & run, bool & quiet, bool & until,
                    std::string &tillState);

// shell that handels all the opperations
void shell(const StateTable & stateTable, Tape & tape);

#endif /* SHELL_HPP */
