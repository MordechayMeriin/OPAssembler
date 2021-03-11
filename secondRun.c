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
            /*if(dir==entry)*/ /*for each labelName in etries array*/
            {
                /*labelName = NULL; /*the lable's name...*/
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