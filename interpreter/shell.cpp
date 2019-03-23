#include "shell.hpp"

// update the tape given the current state
void updateTape(const StateTable & stateTable,
                Tape & tape, const int & curState)
{ // write to tape the new char
  char newChar = stateTable[curState].newChar;
  // take care of the question mark
  if(newChar != '?') tape.write(newChar);

  // move tape in appropriate direction
  if ( stateTable[curState].direction == 'r' )
    tape.moveRight();
  if ( stateTable[curState].direction == 'l' )
    tape.moveLeft(); }

// interpret user input
void interpretInput(const std::vector<std::string> & tokens, 
                    Tape & tape, bool & run, bool & quiet,
                    bool & until, bool & halt, bool & redo,
                    std::string &tillState)
{ const int size = tokens.size();
  if ( size < 1 ) return;
  if ( size < 2 )
  { if ( tokens[0] == "h" )
    { printf(RED "\n Halted program.\n" RST);
      halt = true;
      return; }
    if ( tokens[0] == "t" )
    { printf("\n\n"); // ensure proper spacing
      printFinalTape(tape);
      redo = true; // redo current state
      return; }
    if ( tokens[0] == "r" )
    { run = true;
      return; }
    if ( tokens[0] == "q" )
    { run = true;
      quiet = true;
      return; } }
  if ( size < 3 )
  { if ( tokens[0] == "ru" )
    { run = true;
      until = true;
      tillState = tokens[1];
      return; }
    if ( tokens[0] == "qu" )
    { run = true;
      quiet = true;
      until = true;
      tillState = tokens[1];
      return; } }
  printInputError();
  redo = true; } // redo current state without continuing

// check to see if specified state was reached
void checkUntillState(const StateTable & stateTable, const int & curState,
                    bool & run, bool & quiet, bool & until, 
                    std::string &tillState)
{ if ( stateTable[curState].curState == tillState )
  { run = false;
    quiet = false;
    until = false; } }

void shell(const StateTable & stateTable, Tape & tape)
{
  //Print tabale
  printTable(stateTable);

  // keep track of the state
  int curState = 0;

  // store tokens read from user
  std::vector<std::string> tokens;

  // bools for user commans
  bool run = false, quiet = false, until = false;
  bool halt = false, redo = false;

  // string used to run until that state
  std::string tillState;

  // count of number of steps
  unsigned int count = 1;
  // main loop that traverses through the program
  for (count = 1; stateTable.size() > 0; count += 1)
  { // print current step
    if ( !quiet )
      printStep(stateTable, tape, curState);
 
    // print input line if run flag is false
    if ( !run )
      printf("> ");

    // read tokens from user if run flag is false
    if ( !run )
      readUserInput(tokens);

    // interpret user input if run flag is flase
    if ( !run )
      interpretInput(tokens, tape, run, quiet, until, halt, redo, tillState);

    // if halt break loop
    if ( halt ) break;

    // if redo continue and redo loop with out going to next state
    if ( redo )
    { redo = false;
      continue; }

    // update the tape given the current state
    updateTape(stateTable, tape, curState);

    // get the new state
    int newState = getNewState(stateTable, curState, tape.get());

    // check to see if newState is valid
    if( newState == INVALID) break;
    else curState = newState;

    // check to see if you reached the given state
    if ( until )
      checkUntillState(stateTable, curState, run, quiet, until, tillState); }
  
  // after being done, print results
  printFinalInfo(stateTable, tape, curState, count);
}
