#include "getNewState.hpp"

// gets the index of the next state given the current state index
// and the character seen on tape
int getNewState(const StateTable & stateTable,
                const int curState, const char & charSeen)
{ for ( int i = 0; i < (signed int) stateTable.size(); i += 1 )
  { // compare the next state name with the character seen on tape
    // to find te next state
    if ( stateTable[i].curState == stateTable[curState].newState )
    { // if the curChar is equal to char seen
      // or is equal to ? aka anything allow them to be equal.
      if ( stateTable[i].curChar == charSeen || stateTable[i].curChar == '?')
        return i; } }
  // if no state is found print invalid
  return INVALID; }
