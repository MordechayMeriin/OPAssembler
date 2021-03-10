#include <stdio.h>
#include <string.h>
#include "firstRun.h"

void first(FILE *file)
{
    extern int IC, DC, ICF, DCF;
    short int labelFlag=0;
    int L, lineNumber = 1;
    char label[MAXWORD], EXlabel[MAXWORD];
    char *firstWord;
    char *line = (char *)calloc(sizeof(char), MAXLINE);
    List *codeList = listalloc();
    List *dataList = listalloc();
    Symbols *SymbolList = Slistalloc();
    Rule *rule;
    char **operands;

    if (line == NULL)
    {
        mallocError("string");
    }
    /*line=readLine(file);
    deleteBlanks(line);*/

    createRulesTable();

    while(fgets(line, MAXLINE, file) != NULL)
    {
        deleteBlanks(lineNumber, line);
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
                        errorLog(lineNumber, "Invalid data");
                }
                else if(strcmp(firstWord, ".extern")==0 ||  strcmp(firstWord, ".entry")==0)
                {
                    if(strcmp(firstWord, ".extern")==0)
                    {
                        getWord(line, EXlabel);
                        if (validLabel(EXlabel))
                        {
                            if (*line=='\0')
                            {
                                addToTable(SymbolList, EXlabel, "external", 0, lineNumber);
                            }
                            else
                            {
                                errorLog(lineNumber, "extern direction contains more than one operand")
                            }
                        }
                    }
                }
                else
                {
                    errorLog(lineNumber, strcat("Invalid direction: ", firstWord));
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
                    rule = getRule(firstWord);
                    operands = getOperands(line, lineNumber);
                    L = 1;
                    if (operands[0] != NULL)
                    {
                        L++;

                        if (operands[1] != NULL)
                        {
                            L++;
                        }
                        
                    }
                    
                }
                else
                {
                    errorLog(lineNumber, strcat("Unknown command: ", firstWord));
                }
                
                
            }
            /*line=readLine(file);
            deleteBlanks(line);*/
        }
        lineNumber++;
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

int isItLable(int lineNumber, char *word)
{
    if(word[strlen(word)-1]==':')
    {
        word[strlen(word)-1]='\0';
        if(strlen(word)>=MAXWORD)
            errorLog(lineNumber, "invalid label name, too long");
        else if(validLabel(word))
        {
            return 1;
        }
        else
        {
            errorLog(lineNumber,strcat(word, " is an invalid label name");
            return 1; /*maybe 0?*/
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
        for(i=1; line[i]!='\0' && line[i]!='\"' ; i++)
        ;
        if(line[0]=='\"' && line[i]=='\"' && line[i+1]=='\0')
            return (i-2);/*starts with appostrophes, ends with appostrophes, total 2 spare cahracters*/
    }
    if(strcmp(type, ".data")==0)
    {
        for(i=1; line[i]!='\0' ; i++)
        {
            if(line[i]>='0' || line[i]<='9' || line[i]==' ' || line[i]==',' || line[i]=='-' || line[i]== '+')
            {
                if((line[i]=='+' || line[i]=='-') && (line[i+1]>'9' || line[i+1]<'0'))
                ;
                else if(line[i]==',' && (/*line[i-1]>'9' || line[i-1]<'0' ||*/ line[i+1]=='\0'))
                ;
                else if(line[i]==',' && j==0)
                ;
                else if(line[i]==',' || j==0)
                    j++;
            }
        }
    }
    return j;
}

char **getOperands(char *line, int lineNumber)/*Return an array of strings, representing the operands. Comma checks included*/
{
    char **operands = (char **)calloc(sizeof(char), MAXWORD * 2);
    char *thirdOperand;
    line = getWord(line, operands[0]);
    char *tmp;
    
    if (operands[0] != NULL)
    {
        if (operands[0] == ',')
        {
            errorLog(lineNumber, "unnecessary ',' character.")
        }
        
        if (!trimComma(operands[0])) /*if first operand doesn't end with a comma*/
        {
            line = getWord(line, tmp);
            if (tmp != NULL)
            {
                if (*tmp == ',') 
                {
                    line = getWord(line, operands[1]);  
                }
                else
                {
                    errorLog(lineNumber, "2 operands without ',' seperate.");
                    operands[1] = tmp;                  
                }  
            }                       
        }
        else /*if first operand ends with a comma*/
        {
            line = getWord(line, operands[1]); 
        }
        if (operands[1] != NULL)
        {
            if (operands[1] == ',')
            {
                errorLog(lineNumber, "unnecessary ',' character.")
            }
            
            line = getWord(line, thirdOperand); 
            if (thirdOperand != NULL)
            {
                errorLog(lineNumber, "you can't have more then 2 operands.");
            }
        }        
    }
    
    return operands;
}

int trimComma(char *word)/*delete a comma at the end of an operand, and return an indication if there was a comma.*/
{
    int isComma;
    while (*word != '\0')
    {
        word++;
    }
    isComma =  (--word == ',');

    *word = '\0';

    return isComma;
}
