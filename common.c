#include <stdio.h>
#include <stdlib.h>

int strCompare(char *s1, char *s2)
{
    for (; *s1 == *s2; s2++)
    {
        if (*s1 == '\0')
        {
            return 0;
        }       
    }
    return *s1 - *s2;
}

void mallocError(char *dataType)
{
    printf("Error: could not allocate memory for a %s.", dataType);
    exit(2);
}

int openWord(char *line, char *word, int wordLength)
{
    char *tmp;
    int i;
    for(i=0 ; i<wordLength ; i++)
        tmp[i]=line[i];
    if(strcmp(tmp,word)==0)
        return 1;
    return 0;
}