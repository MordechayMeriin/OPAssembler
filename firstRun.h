#include "rulesHash.h"
#include "getInput.h"

void first(FILE *file, int *IC, int *DC, int *DFC, int *flags);
int isEmpty(char * line); /*is it an empty line or a comment line*/
int isItDir(char *line); /*is it a directive statment - data, string, labels etc*/
int isThereLable(char *line);
