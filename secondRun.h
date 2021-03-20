#include <stdio.h>
#include <string.h>
#include "firstRun.h"
#include "getInput.h"

void second(char *fileName, List *codeList, List *dataList, Symbols *SymbolList);

void addOperand2(Symbols *SymbolList, char *operand, List **codeList, int operationAddress, int lineNumber);