#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "errors.h"
#include "common.h"

#define ERROR_PREFIX_LENGTH 30

static char *errorsLog;

void errorLog(int line, char *error)

{  
    int errorLength;
    char *c, *errorMessage = (char *)calloc(sizeof(char), strlen(error) + ERROR_PREFIX_LENGTH);
    sprintf(errorMessage, "Error at line %d: %s.", line, error);
    errorLength = strlen(errorMessage);
    if (errorsLog == NULL || *errorsLog == '\0')
    {
        errorsLog = (char *)malloc(sizeof(char) * (strlen(errorMessage) + 2));       
    }
    else
    {
        errorsLog = (char *)realloc(errorsLog, sizeof(char) * (strlen(errorMessage) + strlen(errorsLog) + 3));
        /*errorsLog = (char *)realloc(errorsLog, (sizeof(*errorMessage) + sizeof(*errorsLog) + sizeof(char)));  */   
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
    if (*errorsLog != '\0')
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
    return (!*errorsLog == '\0');
}