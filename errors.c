#include <stdlib.h>
#include <stdio.h>
#include "errors.h"
#include "common.h"

static char *errorsLog;

void errorLog(int line, char *error)
{
    char *c, *errorMessage = "";

    sprintf(errorMessage, "Error at line %d: %s.", line, error);

    if (errorsLog == NULL)
    {
        errorsLog = (char *)malloc(sizeof(*errorMessage) + sizeof(char));       
    }
    else
    {
        errorsLog = (char *)realloc(errorsLog, (sizeof(*errorMessage) + sizeof(*errorsLog) + sizeof(char)));     
    }
    if (errorsLog == NULL)
    {
        mallocError("error output");
    }
    
    for (c = errorsLog; *c != '\0'; c++)
        ;
    
    for (; *errorMessage != '\0'; errorMessage++, c++)
    {
        *c = *errorMessage;
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

int areErrorsExist()
{
    return (errorsLog == NULL);
}