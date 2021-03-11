#include <stdio.h>
#include <string.h>
#include "firstRun.h"

void second(FILE *file, List *codeList, List *dataList, Symbols *SymbolList)
{
    extern int IC, DC, ICF, DCF, L;
    int lineNumber = 1;
    char *firstWord = NULL;
    char *line = (char *)calloc(sizeof(char), MAXLINE);
    Symbols *tmp;

    if (line == NULL)
    {
        mallocError("string");
    }

    while(fgets(line, MAXLINE, file) != NULL)
    {
        deleteBlanks(lineNumber, line);
        if(!isEmpty(line))
        {
            line = getWord(line, firstWord);
            if(isItLable(lineNumber, firstWord))
            {
                line = getWord(line, firstWord);
            }
            if(isItDir(firstWord))
            {
                if (strcmp(firstWord, ".entry")==0)
                {
                    for(tmp=SymbolList ; strcmp(tmp->name, line)!=0 && tmp!=NULL ; tmp=tmp->next)
                    ;
                    if(strcmp(line, tmp->name)==0)
                        strcat(tmp->attributes, ", entry");
                    else
                        errorLog(lineNumber, strcat(line, " is not exists"));
                }
            }
            else
            {
                /**complete command coding*/ 
            }
        }
        lineNumber++;
    }
    if(areErrorsExist())
    {
        printErrors();
    }
    else
    {
        /*files creating*/
    }
}