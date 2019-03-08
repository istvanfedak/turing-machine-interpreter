#ifndef STATETABLE_HPP
#define STATETABLE_HPP
#define VALID -1       // code for valid insertion
#include "State.hpp"
#include "compareState.hpp"
#include <vector>

// ordered list of state
class StateTable : public std::vector<State> {
 public:
  // add state and check for dups
  // the StateTable can be sorted with sortTable.hpp
  int addState(const State & state);
};

#endif /* STATETABLE_HPP */
