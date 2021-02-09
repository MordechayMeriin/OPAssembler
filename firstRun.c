#include <stdio.h>
#include "firstRun.h"


void first(FILE *f1, int *IC, int *DC, int *flags)
{
    char line[MAXLINE];
    while((*line=getLine(f1)) != EOF)
    {
        if(isEmpty(line))
        {
            ;
        }
       else if(isItDir(line))
       {
           if(isThereLable(line))
           {
               flags[0]=1;
           }
           if (openWord(line, ".data ", 6) || openWord(line, ".string ", 8))
           {
               if(flags[0])
               {
                   /*
                   enter to symbols tabel as data
                   symbol value is DC
                   identify data type
                   DC+=(data length)
                   */
               }
               else if(openWord(line, ".extern ", 8) || openWord(line, ".entry ", 7))
               {
                   if(openWord(line, ".extern ", 8))
                   {
                       /*
                        enter to symbols tabel as external
                        value is 0 
                       */
                   }
               }
               else
               {
                   /*error*/
               }
           }
           
       }
       else 
       {
           
       }
    }
}

int isEmpty(char *line)
{
    if(line[0]==';' || line[0]=='\0')
        return 1;
    return 0;
}

int isItDir(char *line)
{
    if(line[0]=='.')
        return 1;
    return 0;
}