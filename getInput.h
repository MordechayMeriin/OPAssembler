#ifndef GET_INPUT_INCLUDED
#define GET_INPUT_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXLINE 82
#define MAXWORD 32

FILE *openFile(char *);
void deleteBlanks(int lineNumber, char *); /*deletes unnecessary spaces and tabs, and make the line more readable*/
char *getWord(char *line, char **word); /*move the first word to **word and returns pointer to the next word*/
int isSpace(char);

#endif