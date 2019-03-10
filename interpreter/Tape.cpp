#include "Tape.hpp"
#include <stdio.h>
Tape::Tape()
{ this->clear(); }

//construct from a string
Tape::Tape(const std::string & str)
{ this->set(str); }

// clear tape
void Tape::clear()
{ left.clear();
  right.clear(); }

// set tape from string 
void Tape::set(const std::string & str)
{ left.clear();
  right.clear();
  for(unsigned int i = 0; i < str.size(); i ++)
   right.push_back(str[i]); }

// write a char to the tape
void Tape::write(const char & chr)
{ if ( right.size() > 0 )
    right.front() = chr;
  else
    right.push_front(chr); }

// get a char seen on tape
char Tape::get()
{ if ( right.size() > 0 )
    return right.front();
  else
    return '\0'; }

// moves tape right
void Tape::moveRight()
{ if ( right.size() > 0)
  { left.push_back(right.front());
    right.pop_front(); }
  else
    left.push_back('\0'); }

// moves tape left
void Tape::moveLeft()
{ if ( left.size() > 0 )
  { right.push_front(left.back());
    left.pop_back(); }
  else
    right.push_front('\0'); }
