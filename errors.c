#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "errors.h"
#include "common.h"

#define ERROR_PREFIX_LENGTH 30

static char *errorsLog; /*global string, contains literal description of errors for each line*/

void errorLog(int line, char *error)

{  
    int errorLength;
    char *c, *errorMessage = (char *)calloc(sizeof(char), strlen(error) + ERROR_PREFIX_LENGTH);
    
    if (errorMessage == NULL)
    {
        mallocError("string");
    }

    sprintf(errorMessage, "Error at line %d: %s", line, error);
    errorLength = strlen(errorMessage);
    if (errorsLog == NULL || *errorsLog == '\0')
    {
        errorsLog = (char *)calloc(sizeof(char) , errorLength + 2);       
    }
    else
    {
        errorsLog = (char *)realloc(errorsLog, sizeof(char) * (errorLength + strlen(errorsLog) + 3));  
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

void errorLogCat(int line, char *errorCat1, char *errorCat2)
{
    char *error = calloc(sizeof(char), strlen(errorCat1) + strlen(errorCat2) + 50);
    if (error == NULL)
    {
        mallocError("string");
    }
    strcpy(error, errorCat1);
    strcat(error, errorCat2);

    errorLog(line, error);
    free(error);
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
    if (errorsLog != NULL)
    {
        return (strcmp(errorsLog, ""));
    }
    return 0;
}