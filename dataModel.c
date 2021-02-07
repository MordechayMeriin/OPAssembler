#include <stdlib.h>
#include <stdio.h>
#include "dataModel.h"

Word *walloc()
{
    Word *p;
    p = (Word *)calloc(sizeof(Word), 1);
    if (p == NULL)
    {
        printf("%s\n", "Failed to allocate memory for a new word.");
        exit(2);
    }  
    return p;
}
