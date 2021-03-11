#include <stdio.h>
#include <string.h>
#include "firstRun.h"

void second(List *codeList, List *dataList, Symbols *SymbolList /*, char **labelName*/)
{
    Symbols *tmp;
    char *labelName;
    /*while(read line)*/
    {
        /*if(isItDir)*/
        {
            /*if(dir==entry)*/ /*for each labelName*/
            {
                /*labelName = NULL; the lable's name...*/
                for(tmp=SymbolList ; strcmp(tmp->name, labelName/*[i]*/)!=0 && tmp!=NULL ; tmp=tmp->next)
                ;
                if(strcmp(labelName/*[i]*/, tmp->name)==0)
                    strcat(tmp->attributes, ", entry");
                else
                    exit(3);
            }
        }
            /*step 6, comlete binary coding*/
    }
    if(areErrorsExist())
    {
        printErrors();
    }
    /*build output files*/
}

/*void second(FILE *file, List *codeList, List *dataList, Symbols *SymbolList)
{
    extern int IC, DC, ICF, DCF, L;
    int lineNumber = 1;
    char label[MAXWORD];
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
                    if(strcmp(labelName, tmp->name)==0)
                        strcat(tmp->attributes, ", entry");
                    else
                        errorLog(lineNumber, strcat(line, " is not exists"));
                }
            }
            else
            {
                **complete command coding
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
        files creating
    }
}*/