#include <stdio.h>
#include <string.h>
#include "firstRun.h"

void second(FILE *file, List *codeList, List *dataList, Symbols *SymbolList);

void addOperand2(OpWord *operation, Symbols *SymbolList, Rule *rule, char *operand, Int12 *codedOperand, int operandType, int lineNumber);    