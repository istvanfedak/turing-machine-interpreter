#include "read.hpp"

// test and convert character literals of tokens
char testCharLiteral(const int & lineNumber, std::string tokens[], const int index)
{ const int litSize = 4;
  std::string strLiterals[litSize] = { "\\n", "\\r", "\\t", "\\0" };
  char literals[] = { '\n', '\r', '\t', '\0' };

  // test the vector of literals to see if they match
  bool isLit = false;
  int i;
  for (i = 0; i < litSize; i += 1)
  { if(tokens[index] == strLiterals[i])
    { isLit = true;
      break; } }

  if ( isLit )
    return literals[i];

  // make sure that you are reading characters
  if(index == 1) assertCurChar(lineNumber, tokens);
  if(index == 3) assertNewChar(lineNumber, tokens);
  return tokens[index][0]; }

// split a line read into sub strings and construct a state
bool splitLine(State & state, const std::string & line, const int & lineNumber)
{ std::stringstream sline(line);
  const int size = 6;
  std::string tokens[size];

  char curChar, newChar;
  int tokenIndex = 0;
  while ( tokenIndex < size && sline >> tokens[tokenIndex] )
  {
    // this allows comments in between lines
    if(tokens[0] == "//") return false;

    if (tokenIndex < size - 2 ) // the last entry in the state has no comma or separation
    {
      // make sure everything is separated by commas
      int end = tokens[tokenIndex].size();
      char ending = (end > 0)? tokens[tokenIndex][end-1] : '\0';
      assertSeparation(lineNumber, tokenIndex, ending);
      // delete the last char in the string
      tokens[tokenIndex].erase(end-1, 1); }

    // test to see if curChar and newChar are character literals
    if ( tokenIndex == 1 )
      curChar = testCharLiteral(lineNumber, tokens, 1);
    if ( tokenIndex == 3 )
      newChar = testCharLiteral(lineNumber, tokens, 3);

    tokenIndex += 1; }

  // makes sure the states and direction are correct
  assertState(lineNumber, tokenIndex, tokens, size);
  state.set(tokens[0], curChar, tokens[2], newChar, tokens[4][0]);
  return true; }

// make line all lowercase
void makeLowerCase(std::string & line)
{ for ( unsigned int i = 0; i < line.size(); i += 1 )
    if(line[i] <= 'Z' && line[i] >= 'A')
      line[i] -= ('Z' - 'z'); }

// read a touring table from a file and return it
StateTable readTable(const std::string & fileName)
{ std::ifstream fin(fileName.c_str());

  // check if file is open
  assertFileOpen(fin, fileName);

  StateTable stateTable;
  State state;
  std::string line;

  // used to store the line number of each entry in the table
  std::vector<int> lineNum;

  // read each line of the file
  for (unsigned int i = 0; getline(fin, line); i++ )
  {
    // make sure that there are no new lines
    if ( line.size() > 1 )
    {
      // makes characters case insensitive
      makeLowerCase(line);

      // split the lines into multiple components
      // and only add to touring table if state is valid
      if ( splitLine(state, line, i) )
      {
        // attempt to add the state to the table
        int result = stateTable.addState(state);

        // make sure the state is valid
        assertStateAddition(stateTable, state, result, i, lineNum);

        // push the line number into the vector fo debug
        lineNum.push_back(i); } } }

  // sort state table
  sortTable(stateTable);

  // return the state table
  return stateTable; }

// read a tape file and return it as a string
Tape readTape(const std::string & fileName)
{ // open file
  std::ifstream fin(fileName.c_str());

  // check if file is open
  assertFileOpen(fin, fileName);

  // create return tape
  Tape tape;

  // read file
  char c;
  while ( fin.get(c) )
    tape.right.push_back(c);

  return tape; }


// split a line read into sub strings and construct a state
void readUserInput(std::vector<std::string> & tokens)
{ // clear tokens 
  tokens.clear();

  std::string line;

  // get the line from the user
  getline(std::cin, line);

  // make line all lowercase
  makeLowerCase(line);

  // have a temp string for input
  std::string temp;
  // prepare string stream to make tokens
  std::stringstream sline(line);

  // extract all the tokens from string
  while ( sline >> temp )
    tokens.push_back(temp); }

