# Turing Machine Interpreter

I made this interpreter in order to help me master turing machines! I added
a couple of debugging tools that should help my quality of sleep... Feel
free to use it and let me know of any awesome algorithms you manage to 
recreate! Or you can always let me know of any bugs that you find lurking
around and I'll try to fix them.

## Compilation

Go into the interpreter folder and type the following command into the
terminal:

    $ make

To clean the interpreter folder type the following command into the
terminal:

    $ make clean

## Usage

Go into the interpreter folder and type one of the following two
commands:

    $ ./tm <turing-table-file-name> <input-string>

  or

    $ ./tm <turing-tabe-file-name> -f <input-file-name>

## Shell commands

When you start up the interpreter it will allow you to enter the following
commands:

    <enter>           - when pressing the enter key you go to the next state
    h                 - halt program
    r                 - run
    q                 - run quietly
    ru <state name>   - run until state name is reached
    qu <state name>   - run quietly until state name is reached
    t                 - print the current state of the tape

## Turing table format

The interpreter uses a strict turing table format. If the start state is 
not present in the table the starting state will be the smallest current 
state string.

**State names are case insensitive!**

Table row format:

    <current state>, <char seen on tape>, <next state name>, <char writen on tape>, <direction>

Sample table:

    // Yes the interpreter ignores comments!!!

    // This table will decrement a binary number surrounded by numerals
    // Sample input: #100110#

    D1,    #, D2,   #, L
    start, #, D1,   #, R  // the start state doesn't have to be at the top
    D1,    ?, D1,   ?, R
    D2,    #, stop, #, R
    D2,    1, D3,   0, R
    D2,    ?, D2,   ?, L
    D3,    #, stop, #, -  // the '-' stands for no movement of the tape
    D3,    0, D3,   1, R



## Interpreter error handling

The interpreter is very picky and it will be more than happy to point out
any mistakes you made! This is was done on purpose so that the tables 
remain consistent.
