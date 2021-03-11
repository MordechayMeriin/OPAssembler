#include <stdio.h>
#include <string.h>
#include "firstRun.h"

void second(List *codeList, List *dataList, Symbols *SymbolList)
{
    Symbols *tmp;
    char *labelName;
    /*while(read line)*/
    {
        /*if(isItDir)*/
        {
            /*if(dir==entry)*/
            {
                /*labelName = the lable's name...*/
                for(tmp=SymbolList ; strcmp(tmp->name, labelName)!=0 && tmp!=NULL ; tmp=tmp->next)
                ;
                if(strcmp(labelName, tmp->name)==0)
                    strcat(tmp->attributes, ", entry");
                else
                    exit(3);
            }
            /*step 6, comlete binary coding*/
        }
    }
    if(errorsLog!=NULL)
    {
        printErrors();
    }
    /*build output files*/
}