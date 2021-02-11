#include <stdio.h>
#include "firstRun.h"


void first(FILE *file, int *IC, int *DC, int *DFC, int *flags)
{
    char *line;
    line = (char *)calloc(sizeof(char), MAXLINE + 1);

    if (line == NULL)
    {
        mallocError("string");
    }
    
    while(*(line=getLine(file)) != EOF)
    {
        if(isThereLable(line))
        {
           flags[0]=1;
        }
        if(isEmpty(line))
        {
            ;
        }
       else if(isItDir(line))
       {
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
       else /*it is a command line*/
       {
          if(flags[0])
            {
                /*
                enter to symbols tabel as code
                symbol value is IC
               */
            }
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

int isThereLable(char *line)
{

    return 0;
}