#include <stdio.h>
#include "firstRun.h"


void first(FILE *f1, int *IC, int *DC)
{
    char line[MAXLINE];
    while((*line=getLine(f1)) != EOF)
    {
        if(isEmpty(line))
        {
 
        }
       else if(isItDir(line))
       {
           if(isThereLable(line))
           {

           }
           
       }
       else 
       {
           
       }
    }
}