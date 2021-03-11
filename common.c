#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXWORD 20

void mallocError(char *dataType)
{
    printf("Error: could not allocate memory for a %s.", dataType);
    exit(2);
}

int isStringNumber(char *str)
{
    if (*str == '-' || *str == '+')
    {
        str++;
    }
    if (*str == '\0')
    {
        return 0;
    }
    
    while (*str != '\0')
    {
        if (!isdigit(*str))
        {
            return 0;
        }
        str++;
    }
    return 1;
}

/*int openWord(char *line, char *word, int wordLength)
{
    char tmp[MAXWORD];
    int i;

     for(i=0 ; i<wordLength ; i++)
        tmp[i]=line[i];
    tmp[i]='\0';
    if(strcmp(tmp,word)==0)
        return 1;
    return 0;
}*/