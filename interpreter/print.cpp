#include "print.hpp"

// print chars and literals
void fprintChar(FILE * ptr, const char & chr)
{ const int litSize = 4;
  std::string strLiterals[litSize] = { "\\n", "\\r", "\\t", "\\0" };
  char literals[] = { '\n', '\r', '\t', '\0' };

  for (int i = 0; i < litSize; i += 1)
  { if(chr == literals[i])
    { fprintf(ptr, "%3s", strLiterals[i].c_str());
      return; } }

  fprintf(ptr, "%3c", chr); }

// print a state
void printState(const State & state)
{ printf("%15s ", state.curState.c_str());
  fprintChar(stdout, state.curChar);
  printf("     ---> ");
  printf("%15s ", state.newState.c_str());
  fprintChar(stdout, state.newChar);
  printf(" %3c\n", state.direction); }

// print a state table
void printTable(const StateTable & stateTable)
{ printf(MAG "\n Table" RST ":\n");
  for ( unsigned int i = 0; i < stateTable.size(); i += 1 )
  { printf("%4u: ", i);
    printState(stateTable[i]); } }

// prints chars properly
void printChar(const char & chr)
{ const int litSize = 4;
  std::string strLiterals[litSize] = { "\\n", "\\r", "\\t", "\\0" };
  char literals[] = { '\n', '\r', '\t', '\0' };

  for (int i = 0; i < litSize; i += 1)
  { if(chr == literals[i])
    { printf("%s", strLiterals[i].c_str());
      return; } }

  printf("%c", chr); }


// prints the tape
// careful table is not constant!
void printTape(Tape & tape)
{ String::iterator i = tape.left.begin();
  while ( !tape.left.empty() && i != tape.left.end() )
  { printChar(*i);
    ++i; }
  i = tape.right.begin();
  while ( !tape.right.empty() && i != tape.right.end() )
  { printChar(*i);
    ++i; }
  printf("\n"); }

// print the final remating contents of the tape
// on the right and left
void printFinalTape(Tape & tape)
{ String::iterator i = tape.left.begin();
  printf(GRN " Tape remaining to the left" RST ":\n\n   "); 
  while ( !tape.left.empty() && i != tape.left.end() )
  { printChar(*i);
    ++i; }
  printf(GRN "\n\n Official result" RST ":\n\n   ");
  i = tape.right.begin();
  while ( !tape.right.empty() && i != tape.right.end() )
  { printChar(*i);
    ++i; }
  printf("\n\n"); }

// compare literals
bool isLiteral(const char & c)
{ const int litSize = 4;
  char literals[] = { '\n', '\r', '\t', '\0' };

  for ( int i = 0; i < litSize; i += 1 )
    if ( c == literals[i] )
      return true;
  return false; }


// print the curser for the tape
void printCurser(Tape & tape)
{ // count the number of literals in the left side of string
  int litCount = 0;
  String::iterator i = tape.left.begin();
  while ( !tape.left.empty() && i != tape.left.end() )
  { if ( isLiteral(*i) )
      litCount += 1;
    ++i; }

  // check current char on tape
  if ( isLiteral(*tape.right.begin()) )
    litCount += 1;
  
  // print the curser
  int leftLength = tape.left.size();
  if ( leftLength > 1 || litCount > 1 )
    printf(RED "%*c *^*\n" RST, leftLength + litCount - 1, ' ');
  else if (leftLength == 1)
  { if ( litCount == 1 )
      printf(RED "  *^*\n" RST);
    else
      printf(RED " *^*\n" RST); }
  else
  { if ( litCount == 1)
      printf(RED " *^*\n" RST);
    else
      printf(RED "*^*\n" RST); } }


// prints the steps that the shell makes to reach the answer
void printStep(const StateTable & stateTable,
               Tape & tape, const int & curState)
{ // print current state
  printf("\n----------------------------------------------------------\n");
  printf(MAG " Table entry" RST ":\n");
  printf("%4d: ", curState);
  printState(stateTable[curState]);
  // printing the tape
  printf(MAG "\n Tape" RST ":\n   ");
  printTape(tape);
  printf("  ");
  printCurser(tape); }

// after being done, print results
void printFinalInfo(const StateTable & stateTable, Tape & tape,
                    const int & curState, const int & stepCount)
{ printf("\n\n Stopped at state ");
  printf(GRN "%s" RST, stateTable[curState].newState.c_str());
  printf(" with char " GRN "'");
  printChar(tape.get());
  printf("'" RST " seen on the tape, after ");
  printf(GRN "%d" RST " steps.\n\n", stepCount);
  printFinalTape(tape); }


// prints errors when user doesn't provide the correct input
void printInputError()
{ fprintf(stderr, RED "\n Error" RST " please provide one of the following commands: \n");
  fprintf(stderr, CYN "   h" RST "               - halt program\n");
  fprintf(stderr, CYN "   r" RST "               - run\n");
  fprintf(stderr, CYN "   q" RST "               - run quietly\n");
  fprintf(stderr, CYN "   ru <state name>" RST );
  fprintf(stderr, " - run until state name is reached\n");
  fprintf(stderr, CYN "   qu <state name>" RST);
  fprintf(stderr, " - run quietly until state name is reached\n");
  fprintf(stderr, CYN "   t" RST );
  fprintf(stderr, "               - print the current state of the tape\n"); }
