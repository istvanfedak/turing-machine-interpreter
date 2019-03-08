#include "StateTable.hpp"

// function to maintain an ordered list
int StateTable::addState(const State & state)
{ if ( empty() )
  { push_back(state);
    return VALID; }
  unsigned int i = 0;
  while ( i < size() )
  { int comp = compareState(this->at(i), state);
    if ( comp == 0)
      // if dublicate states return the index of the duplicate state
      return i;
    i += 1; }
  // if no duplicate state puch back
  push_back(state);
 return VALID; }
