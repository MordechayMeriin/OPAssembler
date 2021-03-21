#include <stdio.h>
#include <string.h>
#include "firstRun.h"
#include "getInput.h"

void second(char *fileName, List *codeList, List *dataList, Symbols *SymbolList, int ICF, int DCF);

void addOperand2(Symbols *SymbolList, Symbols *externalsList, char *operand, List **codeList, int operationAddress, int lineNumber);