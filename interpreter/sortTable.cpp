#include "sortTable.hpp"

void sortTable(StateTable & stateTable)
{ sort(stateTable.begin(), stateTable.end(), boolCompareState); }
