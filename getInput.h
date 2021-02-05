#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXLINE 81

char *getLine(FILE *);
char skipBlanks(FILE *, int *);