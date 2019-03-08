#ifndef STATE_HPP
#define STATE_HPP
#include <string>

class State {
 public:
  std::string curState;		// current state
         char curChar;		// current character seen on state
  std::string newState;		// new state
	 char newChar;		// new character to be replaced
         char direction;	// direction on tape
  State();
  State(const std::string & curState, const char & curChar,
        const std::string & newState, const char & newChar,
        const char & direction);
  void clear();
  void set(const std::string & curState, const char & curChar,
           const std::string & newState, const char & newChar,
           const char & direction);
};

#endif /* STATE_HPP */
