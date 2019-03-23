#ifndef READ_HPP
#define READ_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "StateTable.hpp"
#include "sortTable.hpp"
#include "Tape.hpp"
#include "print.hpp"
#include "assert.hpp"

// test and convert character literals of tokens
char testCharLiteral(std::string tokens[], const int index);

// split the line into multiple entries used to generate a State
bool splitLine(State & state, const std::string & line, const int & lineNumber);

// make line all lowercase
void makeLowerCase(std::string & line);

// read a touring table from a file
// returns a sorted table
StateTable readTable(const std::string & fileName);

// read a tape file and return it as a string
Tape readTape(const std::string & fileName);

// split a line read into sub strings and construct a state
void readUserInput(std::vector<std::string> & tokens);

#endif /* READ_HPP */
