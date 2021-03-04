#include "rulesHash.h"
#include "linkedList.h"
#include "getInput.h"
#include "tables.c"


void first(FILE *file);
int isEmpty(char * line); /*is it an empty line or a comment line*/
int isItDir(char *line); /*is it a directive statment - data, string, labels etc*/
int isThereLable(char *line);
