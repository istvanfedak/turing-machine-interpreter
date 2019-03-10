#ifndef TAPE_HPP
#define TAPE_HPP
#include <list>
#include "StateTable.hpp"

// simply a list of characters
typedef std::list<char> String;

class Tape {
 public:
  Tape();
  Tape(const std::string & str);

  String right; // everything right of the tape
  String left;  // everythign left of the tape
  
  // clear tape
  void clear();

  // set tape from string
  void set(const std::string & str);

  // write a char to the tape
  void write(const char & chr);

  // get a char seen on tape
  char get();

  // moves tape right
  void moveRight();

  // moves tape left
  void moveLeft();
};

#endif /* TAPE_HPP */
