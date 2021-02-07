#include <stdlib.h>
#include <stdio.h>
#include "errors.h"
#include "common.h"

static char *errorsLog;

void errorLog(char *error)
{
    char *c;

    if (errorsLog == NULL)
    {
        errorsLog = (char *)malloc(sizeof(*error) + sizeof(char));       
    }
    else
    {
        errorsLog = (char *)realloc(errorsLog, (sizeof(*error) + sizeof(*errorsLog) + sizeof(char)));     
    }
    if (errorsLog == NULL)
    {
        mallocError("error output");
    }
    
    for (c = errorsLog; *c != '\0'; c++)
        ;
    
    for (; *error != '\0'; error++, c++)
    {
        *c = *error;
    }
    *c = '\n';
    c++;
    *c = '\0';
}

void printErrors()
{
    if (errorsLog != NULL)
    {
        printf("Assembly errors:\n\n%s", errorsLog);
    }
}

void freeLogMemory()
{
    free(errorsLog);
}