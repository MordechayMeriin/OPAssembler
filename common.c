#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXWORD 20

void mallocError(char *dataType)
{
    printf("Error: could not allocate memory for a %s.", dataType);
    exit(2);
}

int openWord(char *line, char *word, int wordLength)
{
    char tmp[MAXWORD];
    int i;

    /*tmp = calloc(sizeof(char), wordLength + 1);*/

    for(i=0 ; i<wordLength ; i++)
        tmp[i]=line[i];
    tmp[i]='\0';
    if(strcmp(tmp,word)==0)
        return 1;
    return 0;
}