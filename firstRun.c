#include <stdio.h>
#include <string.h>
#include "firstRun.h"

void first(FILE *file)
{
    extern int flags[];
    char *line = (char *)calloc(sizeof(char), MAXLINE);
    List *codeList = listalloc();
    List *dataList = listalloc();

    if (line == NULL)
    {
        mallocError("string");
    }
    /*line=readLine(file);
    deleteBlanks(line);*/

    createRulesTable();

    while(fgets(line, MAXLINE, file) != NULL)
    {
        if(!isEmpty(line))
        {
            char *label;
            char *firstWord;
            line = getWord(line, firstWord);
            if(isThereLable(firstWord))
            {
                flags[0]=1;
                label = firstWord;
                line = getWord(line, firstWord);
            }
            else if(isItDir(firstWord))
            {
                if (strcmp(firstWord, ".data")==0 ||  strcmp(firstWord, ".string")==0 /*openWord(line, ".data ", 6) || openWord(line, ".string ", 8)*/)
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
            else /*it is a command line*/
            {
                if(flags[0])
                {
                    /*
                    enter to symbols tabel as code
                    symbol value is IC
                */
                }
                if (isValidCommand(firstWord))
                {
                    /* code */
                }
                else
                {
                    /* error */
                }
                
                
            }
            /*line=readLine(file);
            deleteBlanks(line);*/
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