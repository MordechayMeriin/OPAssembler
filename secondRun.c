
#include "secondRun.h"

void second(char *fileName, List *codeList, List *dataList, Symbols *SymbolList, int ICF, int DCF)
{
    FILE *file = openFile(fileName);
    int lineNumber = 1;
    char **firstWord = psalloc(), **tmpWord=psalloc();
    char *line, *Fline = (char *)calloc(sizeof(char), MAXLINE);
    Symbols *tmp, *externals = Slistalloc();
    char **operands;
    List *codeListP = codeList;

    if (Fline == NULL || firstWord == NULL)
    {
        mallocError("string");
    }

    while(fgets(Fline, MAXLINE, file) != NULL)
    {
        line=Fline;
        deleteBlanks(lineNumber, line);
        printf("\nline %d: |%s|\n", lineNumber, line);

        if(!isEmpty(line))
        {
            printf("checkpoint %s\n", line);
            line = getWord(line, firstWord, lineNumber);
            if(isItLable(lineNumber, *firstWord))
            {
                printf("|%s| is a label\n", *firstWord);
                line = getWord(line, firstWord, lineNumber);
            }
            if(isItDir(*firstWord))
            {
                line=getWord(line,tmpWord, lineNumber);
                if (strcmp(*firstWord, ".entry")==0)
                {
                    for(tmp=SymbolList ; tmp->next!=NULL && strcmp(tmp->name, *tmpWord)!=0 ; tmp=tmp->next)
                    ;
                    if(strcmp(*tmpWord, tmp->name)==0)
                    {
                        tmp->attributes = strcat(tmp->attributes, ", entry");
                        tmp->attributeList.entry = 1;
                    }                        
                    else
                        errorLog(lineNumber, strcat(*tmpWord, " is not a known label"));
                }
            }
            else
            {              
                /**complete command coding*/ 
                int operationAddress = codeListP->value.address;
                operands = getOperands(line, lineNumber);

                if (*operands[0] != '\0')
                {
                    codeListP = codeListP->next; 
                    addOperand2(SymbolList, externals, operands[0], &codeListP, operationAddress, lineNumber);   

                    if (*operands[1] != '\0')
                    {                              
                        codeListP = codeListP->next;              
                        addOperand2(SymbolList, externals, operands[1], &codeListP, operationAddress, lineNumber);
                    }
                }
                codeListP = codeListP->next; 
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
        createFiles(codeList, SymbolList, externals, ICF, DCF, fileName);
    }
    fclose(file);
}

void addOperand2(Symbols *SymbolList, Symbols *externalsList, char *operand, List **codeList, int operationAddress, int lineNumber)
{
    int rel=0;
    if (*operand != '#' && !isRegister(operand))
    {
        if (*operand == '%')
        {
            operand++;
            rel=1;
        }
        if(validLabel(operand))
        {
            for(; strcmp(SymbolList->name, operand)!=0 && SymbolList->next!=NULL ; SymbolList=SymbolList->next)
                ;
            if(strcmp(operand, SymbolList->name)==0)
            {
                if(rel) /*Relative Addressing*/
                {
                    (*codeList)->value.value = SymbolList->value.value - operationAddress;
                    (*codeList)->value.ARE = 'A';
                }
                else /*Direct addressing*/
                {
                    (*codeList)->value.value = SymbolList->value.value;
                    if (SymbolList->attributeList.external)
                    {
                        (*codeList)->value.ARE = 'E';
                        addToTable(externalsList, operand, "", code, (*codeList)->value.address, lineNumber, true);
                    }
                    else
                    {
                        (*codeList)->value.ARE = 'R';
                    }
                }
            }
            else
            {
                errorLog(lineNumber, strcat(operand, " is not a known label"));
            }
        }
        else
        {
            errorLog(lineNumber, strcat(operand, " is not a valid label"));
        }
    }
}