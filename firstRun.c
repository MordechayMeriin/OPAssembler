#include <stdio.h>
#include <string.h>
#include "firstRun.h"
#include "tables.c"

void first(FILE *file)
{
    extern int flags[];
    char label[MAXWORD];
    char *firstWord;
    char *line = (char *)calloc(sizeof(char), MAXLINE);
    List *codeList = listalloc();
    List *dataList = listalloc();
    Symbols *SymbolList = Slistalloc();

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
            line = getWord(line, firstWord);
            if(isThereLable(firstWord))
            {
                flags[0]=1;
                strcpy(label, firstWord);
                line = getWord(line, firstWord);
            }
            /*else*/ if(isItDir(firstWord))
            {
                if (strcmp(firstWord, ".data")==0 ||  strcmp(firstWord, ".string")==0 /*openWord(line, ".data ", 6) || openWord(line, ".string ", 8)*/)
                {
                    if(flags[0])
                    {
                        addToTable(SymbolList, label, "data", DC);
                        /*
                        identify data type and length (how?)
                        DC+=(data length)
                        */
                    }
                }
                else if(firstWord, ".extern")==0 ||  strcmp(firstWord, ".entry")==0 /*openWord(line, ".extern ", 8) || openWord(line, ".entry ", 7)*/)
                {
                    if(firstWord, ".extern")==0)
                    {
                        addToTable(SymbolList, label, "extern", 0);
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
                    addToTable(SymbolList, label, "code", IC);
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