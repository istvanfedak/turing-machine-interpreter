#ifndef COMPARESTATE_HPP
#define COMPARESTATE_HPP
#include <string>
#include "State.hpp"

// compare chars
int compareChars(const char & a, const char & b);

// compare current state
int compareCurState(const std::string & a, const std::string & b);

// compares if a state is equal to a string for current state and char seen on tape
bool stateIsEqual(const State & state,
                  const std::string & curState, const char & curChar);

// simple compare function
int compareState(const State & a, const State & b);

// bolean comparing if a < b
bool boolCompareState(const State & a, const State & b);

// the pointer version
int compareState(const State * a, const State * b);

// the pointer version
int compareState(const void * a, const void * b);

#endif /* COMPARESTATE_HPP */
