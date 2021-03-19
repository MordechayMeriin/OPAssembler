#include <stdio.h>
#include <string.h>
#include "firstRun.h"
#include "getInput.h"

void second(char *fileName, List *codeList, List *dataList, Symbols *SymbolList);

void addOperand2(OpWord *operation, Symbols *SymbolList, Rule *rule, char *operand, Int12 *codedOperand, int operandType, int lineNumber);    