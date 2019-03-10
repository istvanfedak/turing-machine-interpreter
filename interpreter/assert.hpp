#ifndef ASSERT_HPP
#define ASSERT_HPP

#include <string>
#include <fstream> // to make sure file is open
#include <stdio.h>
#include <string.h>
#include "StateTable.hpp"
#include "print.hpp"

// assert arguments
void assertArguments(const int & argc, char * argv[]);

// assert that file is open and displayes error
void assertFileOpen(const std::ifstream & fin, const std::string fileName);

// assert that the number of entries in the state are correct
void assertStateSize(const int & lineNumber,
                     const int & tokenCount, const int & size);

// assert that the character to be seen on the tape is a character
void assertCurChar(const int & lineNumber, std::string tokens[]);

// assert that the character to be written to the tape is a character
void assertNewChar(const int & lineNumber, std::string tokens[]);

// asserts that direction is one of r, R, l, L, - and is a character
void assertDirection(const int & lineNumber, std::string tokens[]);

// asserts that the state is valid using some of the functions above
void assertState(const int & lineNumber, const int & tokenCount,
                 std::string tokens[], const int & size);

// asserts that state entries are separated by commas
void assertSeparation(const int & lineNumber,
                     const int & tokenIndex, const char & ending);

// asserts that the State was correctly added to the StateTable
void assertStateAddition(const StateTable & stateTable,
                         const State & state, const int & result,
                         const int & lineNumber, const std::vector<int> & lineNum);

#endif /* ASSERT_HPP */
