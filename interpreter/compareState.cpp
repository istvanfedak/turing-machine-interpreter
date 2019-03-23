#include "compareState.hpp"

// compare chars
int compareChars(const char & a, const char & b)
{ // make sure question marks are the largest value
  if ( a == '?' && b != '?') return 1;
  if ( a != '?' && b == '?') return -1;
  // compare the other chars normally
  if ( a < b ) return -1;
  if ( a > b ) return 1;
  return 0; }

// compare current state
int compareCurState(const std::string & a, const std::string & b)
{ if( a == "start" && b != "start" ) return -1;
  if( a != "start" && b == "start" ) return 1;
  if( a == "end" && b != "end" ) return 1;
  if( a != "end" && b == "end" ) return -1;
  return a.compare(b); }

// compares if a state is equal to a string for current state and char seen on tape
bool stateIsEqual(const State & state,
                  const std::string & curState, const char & curChar)
{ if ( compareCurState(state.curState, curState) == 0 ) return true;
  return compareChars(state.curChar, curChar); }

// simple compare function
int compareState(const State & a, const State & b)
{ int comp = compareCurState(a.curState, b.curState);
  if ( comp != 0 ) return comp;
  return compareChars(a.curChar, b.curChar); }

// bolean comparing if a < b
bool boolCompareState(const State & a, const State & b)
{ if(compareState(a, b) < 0) return true;
  return false; }

// the pointer version
int compareState(const State * a, const State * b)
{ int comp = compareCurState(a->curState, b->curState);
  if ( comp != 0 ) return comp;
  return compareChars(a->curChar, b->curChar); }

// void * version
int compareState(const void * a, const void * b)
{ return compareState((State *)a, (State *)b); }
