#include <stdio.h>
#include <string.h>
#include "firstRun.h"

void first(FILE *file)
{
    extern int IC=100, DC=0, ICF, DCF, L;
    int labelFlag=0;
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
        deleteBlanks(line);
        if(!isEmpty(line))
        {
            line = getWord(line, firstWord);
            if(isItLable(firstWord))
            {
                labelFlag=1;
                strcpy(label, firstWord);
                line = getWord(line, firstWord);
            }
            /*else*/ if(isItDir(firstWord))
            {
                if (strcmp(firstWord, ".data")==0 ||  strcmp(firstWord, ".string")==0)
                {
                    if(labelFlag)
                    {
                        addToTable(SymbolList, label, "data", DC);
                    }
                    if(datalen(line, firstWord))
                        DC+=datalen(line, firstWord);
                    else
                        errorLog("invalid data");
                }
                else if(strcmp(firstWord, ".extern")==0 ||  strcmp(firstWord, ".entry")==0)
                {
                    if(strcmp(firstWord, ".extern")==0)
                    {
                        addToTable(SymbolList, label, "extern", 0);
                    }
                }
                else
                {
                    errorLog("invalid direction");
                }
            }
            else /*it is a command line*/
            {
                if(labelFlag)
                {
                    addToTable(SymbolList, label, "code", IC);
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
    if(errorsLog!=NULL)
    {
        printErrors();
    }
    else
    {
        ICF=IC;
        DCF=DC;
        setVal(SymbolList, ICF);
        second(codeList, dataList, SymbolList);
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

int isItLable(char *word)
{
    if(word[strlen(word)-1]==':')
    {
        word[strlen(word)-1]='\0';
        if(strlen(word)>=MAXWORD)
            errorLog("invalid label name, too long");
        else if(validLabel(word))
        {
            return 1;
        }
        else
        {
            errorLog("invalid label name");
        }
    }
    return 0;
}

int validLabel(char *word)
{
    int i=0;
    if(isValidCommand(word))
        return 0;
    if(strlen(word)==2 && word[0]=='r' && word[1]>='0' && word[1]<='7')
        return 0;
    if((word[i]<'a' || word[i]>'z') && (word[i]<<'A' || word[i]>'Z'))
        return 0;
    for( ; word[i]!='/0' ; i++)
    {
        if((word[i]<'a' || word[i]>'z') && (word[i]<<'A' || word[i]>'Z') && (word[i]<'0' || word[i]>'9'))
            return 0;
    }
    return 1;
}

int datalen(char *line, char *type)
{
    int i, j=0;
    if(strcmp(type, ".string")==0)
    {
        if(strlen(line)<=2)
            return 0;
        for(i=2; line[i]!='\0' && line[i]!='\"' ; i++)
        ;
        if(line[0]==' ' && line[1]=='\"' && line[i]=='\"' && line[i+1]=='\0')
            return (i-3);/*starts with a space and appostrophes, and ends with appostrophes, total 3 spare cahracters*/
        else
        {
            return 0;
        }
    }
    if(strcmp(type, ".data")==0)
    {
        if(strlen(line)<=1)
            return 0;
        for(i=1, j=1; line[i]!='\0' ; i++)
        {
            if(line[i]>='0' || line[i]<='9' || line[i]==' ' || line[i]==',' || line[i]=='-' || line[i]== '+')
            {
                if((line[i]=='+' || line[i]=='-')&& (line[i+1]>'9' || line[i+1]<'0'))
                {
                    return 0;
                }
                else if(line[i]==',' && (line[i-1]>'9' || line[i-1]<'0' || line[i+1]=='\0'))
                {
                    return 0;
                }
                else if(line[i]==',')
                    j++;
            }
            else
            {
                return 0;
            }
        }
        return j;

    }
    return 0;
}
