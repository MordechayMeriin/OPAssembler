
#include "secondRun.h"

void second(char *fileName, List *codeList, List *dataList, Symbols *SymbolList)
{
    extern int IC, DC, ICF, DCF;
    FILE *file = openFile(fileName);
    int L, lineNumber = 1;
    char **firstWord = psalloc(), **tmpWord=psalloc();
    char *line, *Fline = (char *)calloc(sizeof(char), MAXLINE);
    Symbols *tmp;
    Rule *rule;
    char **operands;
    OpWord *operation;
    Int12 *codedOp1 = NULL, *codedOp2 = NULL;

    printf("\n\ninsideSecond\n\n");

    if (Fline == NULL || firstWord == NULL)
    {
        mallocError("string");
    }

    while(fgets(Fline, MAXLINE, file) != NULL)
    {
        /*printf("\nLine %d: '%s'\n", lineNumber, Fline);*/
        line=Fline;
        deleteBlanks(lineNumber, line);
        printf("Line %d: |%s|\n", lineNumber, Fline);
        if(!isEmpty(line))
        {
            line = getWord(line, firstWord);
            if(isItLable(lineNumber, *firstWord))
            {
                line = getWord(line, firstWord);
            }
            if(isItDir(*firstWord))
            {
                line=getWord(line,tmpWord);
                if (strcmp(*firstWord, ".entry")==0)
                {
                    for(tmp=SymbolList ; tmp->next!=NULL && strcmp(tmp->name, *tmpWord)!=0 ; tmp=tmp->next)
                    ;
                    if(strcmp(*tmpWord, tmp->name)==0)
                        strcat(tmp->attributes, ", entry");
                    else
                        errorLog(lineNumber, strcat(*tmpWord, " is not a known label"));
                }
            }
            else
            {
                /**complete command coding*/ 
                operation = (OpWord *)calloc(sizeof(OpWord), 1);
                if (operation == NULL)
                {
                    mallocError("OpWord");
                }
                L = 1;
                rule = getRule(*firstWord);
                operands = getOperands(line, lineNumber);
                
                operation->opcode = rule->opcode;
                operation->funct = rule->funct;
                if (operands[0] != NULL)
                {
                    L++; 
                    codedOp1 = i12alloc();                       
                    if (operands[1] != NULL)
                    {
                        L++;
                        codedOp2 = i12alloc();
                        addOperand2(operation, SymbolList, rule, operands[0], codedOp1, SOURCE_OPERAND, lineNumber);
                        addOperand2(operation, SymbolList, rule, operands[1], codedOp2, TARGET_OPERAND, lineNumber);
                        printf("two operands\n");
                    }
                    else
                    {
                        printf("just one\n");
                        addOperand2(operation, SymbolList, rule, operands[0], codedOp1, TARGET_OPERAND, lineNumber);
                    }
                }
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
    free(file);
}

void addOperand2(OpWord *operation, Symbols *SymbolList, Rule *rule, char *operand, Int12 *codedOperand, int operandType, int lineNumber)
{
    int rel=0;
    if (*operand != '#' && !isRegister(operand))
    {
            printf("wow2 --%s--\n", operand);
        if (*operand == '%')
        {
            operand++;
            rel=1;
            /*printf("wow0\n");*/
        }
        if(validLabel(operand))
        {
            /*printf("--%s--\n", operand);*/
            for(; strcmp(SymbolList->name, operand)!=0 && SymbolList->next!=NULL ; SymbolList=SymbolList->next)
                /*printf("|%s|=?=|%s|\n",SymbolList->name, operand)*/;
            /*printf("|%s|==|%s|\n",SymbolList->name, operand);*/
            if(strcmp(operand, SymbolList->name)==0)
            {
                if(rel) /*Relative Addressing*/
                {
                    codedOperand->value = (SymbolList->value.value)-(codedOperand->value);
                }
                else /*Direct addressing*/
                {
                    codedOperand->value = SymbolList->value.value;
                }
            }
            else
            {
                printf("wow1\n:");
                errorLog(lineNumber, strcat(operand, " is not a known label"));
            }
        }
        else
        {
            errorLog(lineNumber, strcat(operand, " is not a valid label"));
        }
    }
}