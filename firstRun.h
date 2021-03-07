#include "rulesHash.h"
#include "linkedList.h"
#include "getInput.h"
#include "tables.c"
#include "errors.h"


void first(FILE *file);
int isEmpty(char * line); /*is it an empty line or a comment line*/
int isItDir(char *line); /*is it a directive statment - data, string, labels etc*/
int isItLable(char *word, Symbols *list);
int datalen(char *line, char *type);
int validLabel(char *word);