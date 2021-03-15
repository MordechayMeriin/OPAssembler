#include <stdlib.h>
#include <stdio.h>
#include "dataModel.h"

Int12 *i12alloc()
{
    Int12 *p;
    p = (Int12 *)calloc(sizeof(Int12), 1);
    if (p == NULL)
    {
        printf("%s\n", "Failed to allocate memory for a new word.");
        exit(2);
    }  
    return p;
}

Row *ralloc()
{
    Row *p;
    p = (Row *)calloc(sizeof(Row), 1);
    if (p == NULL)
    {
        printf("%s\n", "Failed to allocate memory for a new code row.");
        exit(2);
    }  
    return p;
}

char **psalloc()
{
    char **p;
    p = (char **)calloc(sizeof(char *), 1);
    if (p == NULL)
    {
        printf("%s\n", "Failed to allocate memory for a pointer to string.");
        exit(2);
    }  
    return p;
}
