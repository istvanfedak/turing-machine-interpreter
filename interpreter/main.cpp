#include <stdio.h>
#include <string>
#include "assert.hpp"
#include "State.hpp"
#include "StateTable.hpp"
#include "read.hpp"
#include "print.hpp"
#include "Tape.hpp"
#include "shell.hpp"


int main(int argc, char * argv[])
{ // make sure that arguments are correct
  assertArguments(argc, argv);

  // create table
  StateTable stateTable = readTable(argv[1]);
  
  // create tape
  Tape tape;
  if ( argc == 3 ) tape.set(argv[2]);
  else tape = readTape(argv[3]);

  shell(stateTable, tape);

  return 0; }
