#ifndef OUTPUT_INCLUDED
#define OUTPUT_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"
#include "binary.h"
#include "common.h"

void printCodeListDebug(List *list);
void createFiles(List *codeList, Symbols *symbolsList, Symbols *externalsList, int ICF, int DCF, char *fileName);
FILE *CreateFile(char *fileName, char *extention);

#endif