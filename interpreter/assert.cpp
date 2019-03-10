#include "assert.hpp"


// assert arguments
void assertArguments(const int & argc, char * argv[])
{ if( argc < 3 || argc > 4 || ( argc == 4 && strncmp("-f", argv[2], 2) != 0) )
  { fprintf(stderr, MAG "Usage" RST ": %s ", argv[0]);
    fprintf(stderr, CYN "<TM-file-name> <input-string>\n" RST);
    fprintf(stderr, MAG "   or" RST ": %s ", argv[0]);
    fprintf(stderr, CYN "<TM-file-name>" RST " -f ");
    fprintf(stderr, CYN "<input-file-name>\n" RST);
    exit(1); } }

// check if file opened
void assertFileOpen(const std::ifstream & fin, const std::string fileName)
{ if ( fin.fail() )
  { fprintf(stderr, RED "Failed" RST " to open file: ");
    fprintf(stderr, RED "'%s'" RST ".\n\n", fileName.c_str());
    exit(1); } }

// check the state is of proper size
void assertStateSize(const int & lineNumber, const int & tokenCount,
                     const std::string tokens[], const int & size)
{ if ( tokenCount < size -1 )
  { fprintf(stderr, RED "Error" RST " on " MAG "line %d" RST, lineNumber);
    fprintf(stderr, ": table entry has " MAG "not enough" RST " arguments.\n");
    fprintf(stderr, " Please provide: stateName, charOnTape, ");
    fprintf(stderr, "newStateName, newCharOnTape, direction\n\n");
    exit(1); }
                     // this allows comments at the end of a line
  if ( tokenCount == size && tokens[5] != "//" )
  { fprintf(stderr, RED "Error" RST " on " MAG "line %d" RST, lineNumber);
    fprintf(stderr, ": table entry has " MAG "too many" RST " arguments.\n");
    fprintf(stderr, " Please provide: stateName, charOnTape, ");
    fprintf(stderr, "newStateName, newCharOnTape, direction\n\n");
    exit(1); } }

// check that the currect character to be read from tape is a character
void assertCurChar(const int & lineNumber, std::string tokens[])
{ if ( tokens[1].size() > 1 )
  { fprintf(stderr, RED "Error" RST " on " MAG "line %d" RST, lineNumber);
    fprintf(stderr, "," MAG " entry %d" RST ": Character", 2);
    fprintf(stderr, RED " '%s'" RST, tokens[1].c_str());
    fprintf(stderr, " to be read from tape\n is");
    fprintf(stderr, MAG " not a character" RST ".\n\n");
    exit(1); } }

// check that the new character to be written on tape is a character
void assertNewChar(const int & lineNumber, std::string tokens[])
{ if ( tokens[3].size() > 1 )
  { fprintf(stderr, RED "Error" RST " on " MAG "line %d" RST, lineNumber);
    fprintf(stderr, "," MAG " entry %d" RST ": Character", 4);
    fprintf(stderr, RED " '%s'" RST, tokens[3].c_str());
    fprintf(stderr, " to be written on tape\n is");
    fprintf(stderr, MAG " not a character" RST ".\n\n");
    exit(1); } }

// check that direction is one of the predefined characters
void assertDirection(const int & lineNumber, std::string tokens[])
{ if ( tokens[4].size() > 1 )
  { fprintf(stderr, RED "Error" RST " on " MAG "line %d" RST, lineNumber);
    fprintf(stderr, "," MAG " entry %d" RST ":", 5);
    fprintf(stderr, RED " '%s'" RST, tokens[4].c_str());
    fprintf(stderr, " is not a character.\n");
    fprintf(stderr, "  Please use " GRN "R" RST ", " GRN "r" RST );
    fprintf(stderr, ", " GRN "L" RST ", " GRN "l" RST ", or " GRN "-" RST);
    fprintf(stderr, " to specify direction.\n\n");
    exit(1); }

  if ( tokens[4][0] != 'r' && tokens[4][0] != 'l' && tokens[4][0] != '-')
  { fprintf(stderr, RED "Error" RST " on " MAG "line %d" RST, lineNumber);
    fprintf(stderr, "," MAG " entry %d" RST ":", 5);
    fprintf(stderr, RED " '%c'" RST " invalid ", tokens[4][0]);
    fprintf(stderr, "character for direction.\n");
    fprintf(stderr, "  Please use " GRN "R" RST ", " GRN "r" RST );
    fprintf(stderr, ", " GRN "L" RST ", " GRN "l" RST ", or " GRN "-" RST);
    fprintf(stderr, " to specify direction.\n\n");
    exit(1); } }

// check that the state has proper size and the direction is correct
void assertState(const int & lineNumber, const int & tokenCount,
                 std::string tokens[], const int & size)
{ assertStateSize(lineNumber, tokenCount, tokens, size);
  assertDirection(lineNumber, tokens); }

// check if states are separated by commas
void assertSeparation(const  int & lineNumber,
                      const  int & tokenIndex, const char & ending)
{ if ( ending == ',' )
    return;
  fprintf(stderr, RED "Error" RST " on " MAG "line %d" RST, lineNumber);
  fprintf(stderr, "," MAG " entry %d" RST ":", tokenIndex+1);
  fprintf(stderr, " Invalid ending" RED " '%c' " RST "for ", ending);
  switch (tokenIndex)
  { case 0:
      fprintf(stderr, "current state name."); break;
    case 1:
      fprintf(stderr, "character to be seen on tape."); break;
    case 2:
      fprintf(stderr, "next state name."); break;
    case 3:
      fprintf(stderr, "character to be written on tape."); break;
    case 4:
      fprintf(stderr, "tape dirrection."); break;
    default: break; }
  fprintf(stderr, "\n  Please use commas " GRN "','" RST "\n\n");
  exit(1); }

// used to print state errors
void _statePrint(const int & lineNumber,
                 const State & state, bool highlight = false)
{ // if line is result set color to magenta
  if ( highlight ) fprintf(stderr, MAG);
  // print the line number
  fprintf(stderr, "%4u", lineNumber + 1);
  // if line is result set reset color
  if ( highlight ) fprintf(stderr, RST);
  // print current state
  fprintf(stderr, ": %15s ", state.curState.c_str());
  // if line is result set color to magenta
  if ( highlight ) fprintf(stderr, MAG);
  // print current character using printTable lib
  fprintChar(stderr, state.curChar);
  // if line is result set reset color
  if ( highlight ) fprintf(stderr, RST);
  //  print arrow
  fprintf(stderr, "     ---> ");
  // print next state name
  fprintf(stderr, "%15s ", state.newState.c_str());
  // print next character using printTable lib
  fprintChar(stderr, state.newChar);
  // print direction
  fprintf(stderr, " %3c\n", state.direction); }

// prints a character correctly for error
void _charPrint(const char & chr)
{ const int litSize = 4;
  std::string strLiterals[litSize] = { "\\n", "\\r", "\\t", "\\0" };
  char literals[] = { '\n', '\r', '\t', '\0' };

  for (int i = 0; i < litSize; i += 1)
  { if(chr == literals[i])
    { fprintf(stderr, "%s", strLiterals[i].c_str());
      return; } }

  fprintf(stderr, "%c", chr); }


// check if the state table tried to add a repeated state
void assertStateAddition(const StateTable & stateTable,
                         const State & state, const int & result,
                         const int & lineNumber, const std::vector<int> & lineNum)
{ // if instertion is valid, return
  if(result == VALID) return;

  // print a portion of the table to inform user
  int i = ( result < 4 ) ? 0 : result - 4;
  while ( i < (signed int) stateTable.size() && i < result + 5)
  { // print current state
    _statePrint(lineNum[i], stateTable[i], ( i == result));
    i += 1; }

  // print ... for spacing
  fprintf(stderr, " %*c \n %*c \n %*c \n", 31, '.', 31, '.', 31, '.');
  _statePrint(lineNumber, state, true);
  fprintf(stderr, "\n");

  // print the error message
  fprintf(stderr, RED "Error" RST " on " MAG "line %d" RST ":", lineNumber + 1);
  fprintf(stderr, " current character to be seen on tape " RED "'");
  _charPrint(state.curChar);
  fprintf(stderr, "'" RST " duplicates ");
  fprintf(stderr, MAG "line %d" RST ".\n\n", lineNum[result] + 1);
  exit(1); }


