#include "State.hpp"

State::State()
{ this->clear(); }

State::State(const std::string & curState, const char & curChar,
             const std::string & newState, const char & newChar,
             const char & direction)
{ this->set(curState, curChar, newState, newChar, direction); }

void State::clear()
{ curState.clear();
  curChar = '\0';
  newState.clear();
  newChar = '\0';
  direction = '\0'; }

void State::set(const std::string & curState, const char & curChar,
                const std::string & newState, const char & newChar,
                const char & direction)
{ this->curState  = curState;
  this->curChar   = curChar;
  this->newState  = newState;
  this->newChar   = newChar;
  this->direction = direction; }

