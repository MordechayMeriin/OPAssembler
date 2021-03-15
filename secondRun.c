#include "secondRun.h"

void second(FILE *file, List *codeList, List *dataList, Symbols *SymbolList)
{
    extern int IC, DC, ICF, DCF;
    int L, lineNumber = 1;
    char *firstWord = NULL;
    char *line = (char *)calloc(sizeof(char), MAXLINE);
    Symbols *tmp;
    Rule *rule;
    char **operands;
    OpWord *operation;
    Int12 *codedOp1 = NULL, *codedOp2 = NULL;

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
                        errorLog(lineNumber, strcat(line, " is not a known label"));
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
                rule = getRule(firstWord);
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
                    }
                    else
                    {
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
}

void addOperand2(OpWord *operation, Symbols *SymbolList, Rule *rule, char *operand, Int12 *codedOperand, int operandType, int lineNumber)
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
            for(; strcmp(SymbolList->name, operand)!=0 && SymbolList!=NULL ; SymbolList=SymbolList->next)
                ;
            if(strcmp(operand, SymbolList->name)==0)
            {
                if(rel) /*Relative Addressing*/
                {
                    codedOperand->value = (SymbolList->value.value)-(0);
                }
                else /*Direct addressing*/
                {
                    codedOperand->value = SymbolList->value.value;
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