#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXLINE 82
#define MAXWORD 32

/*char *getLine(FILE *);
char skipBlanks(FILE *, int *);*/
FILE *openFile(char *);
char *readLine(FILE *);
void deleteBlanks(char *);
char *getWord(char *line, char *word);
int isSpace(char);