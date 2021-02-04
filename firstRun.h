#include "hashtable.c"
#include "getInput.c"

void first(FILE *, struct hnode *, int *IC, int *DC);
int isEmpty(char * line); /*is it an empty line or a comment line*/
int isItDir(char *line); /*is it a directive statment - data, string, labels etc*/
int isThereLable(char *line);
