#include "firstRun.h"

void first(FILE *f1, struct hnode *ht1, int *IC, int *DC)
{
    char line[MAXLINE];
    while(line=getline(f1) != EOF)
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