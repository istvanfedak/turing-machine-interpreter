#ifndef GETNEWSTATE_HPP
#define GETNEWSTATE_HPP

#include "StateTable.hpp"
#include "compareState.hpp"

// invalid code for assert
#define INVALID -2

// gets the index of the next state given the current state index
// and the character seen on tape
int getNewState(const StateTable & stateTable,
                const int curState, const char & charSeen);

#endif /* GETNEWSTATE_HPP */
