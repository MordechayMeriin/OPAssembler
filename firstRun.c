#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "firstRun.h"


void first(FILE *file)
{
    FILE *Sfile = file;
    extern int IC, DC, ICF, DCF;
    extern void second(FILE *,List *, List *, Symbols *);
    short int labelFlag=0;
    int L, lineNumber = 1;
    char label[MAXWORD], EXlabel[MAXWORD];
    char *firstWord = NULL;
    char *line = (char *)calloc(sizeof(char), MAXLINE);
    List *codeList = listalloc();
    List *dataList = listalloc();
    Symbols *SymbolList = Slistalloc();
    Rule *rule;
    char **operands;
    OpWord *operation;
    Int12 *codedOp1 = NULL, *codedOp2 = NULL;

    if (line == NULL)
    {
        mallocError("string");
    }
    /*line=readLine(file);
    deleteBlanks(line);*/
    createRulesTable();
    while(fgets(line, MAXLINE, file) != NULL)
    {
        printf("line %d:\n", lineNumber);
        deleteBlanks(lineNumber, line);
        printf("1\n");
        if(!isEmpty(line))
        {
            line = getWord(line, firstWord);
            printf("2\n");
            printf("word: %s\n", firstWord);
            if(isItLable(lineNumber, firstWord))
            {
                labelFlag=1;
                printf("2.1\n");
                strcpy(label, firstWord);
                printf("2.2\n");
                line = getWord(line, firstWord);
                printf("3\n");
            }
            /*else*/ if(isItDir(firstWord))
            {
                printf("4\n");
                if (strcmp(firstWord, ".data")==0 ||  strcmp(firstWord, ".string")==0)
                {
                    if(labelFlag)
                    {
                        addToTable(SymbolList, label, "data", DC, lineNumber);
                    }
                    if(datalen(line, firstWord))
                    {
                        DC+=datalen(line, firstWord);
                        dataCoding(line, dataList);
                    }
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
                                errorLog(lineNumber, "extern direction contains more than one operand");
                            }
                        }
                    }
                    /*else- save line as labelName in an array of entries. idea continues in second*/
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
                    addToTable(SymbolList, label, "code", IC, lineNumber);
                }
                if (isValidCommand(firstWord))
                {
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
                            addOperand(operation, rule, operands[0], codedOp1, SOURCE_OPERAND, lineNumber);
                            addOperand(operation, rule, operands[1], codedOp2, TARGET_OPERAND, lineNumber);
                        }
                        else
                        {
                            addOperand(operation, rule, operands[0], codedOp1, TARGET_OPERAND, lineNumber);
                        }
                    }
                    
                    addRowToCodeList(codeList, IC++, *wordToInt12(operation), 'A');
                    if (operands[0] != NULL)
                    {
                        addRowToCodeList(codeList, IC++, *codedOp1, 'N');
                        if (operands[1] != NULL)
                        {
                            addRowToCodeList(codeList, IC++, *codedOp2, 'N');
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
    if(areErrorsExist())
    {
        printErrors();
    }
    else
    {
        ICF=IC;
        DCF=DC;
        setVal(SymbolList, ICF);
        second(Sfile, codeList, dataList, SymbolList);
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
    printf("inside isItLabel %s\n", word);
    if(word[strlen(word)-1]==':')
    {
        printf("inside isItLabel 1\n");
        word[strlen(word)-1]='\0';
        printf("inside isItLabel 2\n");
        if(strlen(word)>=MAXWORD)
            errorLog(lineNumber, "invalid label name, too long");
        else if(validLabel(word))
        {
            return 1;
        }
        else
        {
            errorLog(lineNumber,strcat(word, " is an invalid label name"));
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
    if(!isalpha(word[i])/*(word[i]<'a' || word[i]>'z') && (word[i]<'A' || word[i]>'Z')*/)
        return 0;
    for( ; word[i]!='\0' ; i++)
    {
        if(!isalpha(word[i]) && !isdigit(word[i])/*(word[i]<'a' || word[i]>'z') && (word[i]<'A' || word[i]>'Z') && (word[i]<'0' || word[i]>'9')*/)
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
            if(isdigit(line[i]) || line[i]==' ' || line[i]==',' || line[i]=='-' || line[i]== '+')
            {
                if((line[i]=='+' || line[i]=='-') && !isdigit(line[i+1]))
                ;
                else if(line[i]==',' && line[i+1]=='\0')
                ;
                else if(line[i]==',' && j==0)
                ;
                else if(line[i]==',' || j==0)
                    j++;
                if(j==0)
                    break;
            }
        }
    }
    return j;
}

void dataCoding(char *line, struct lnode *dataList)
{
    int tmp, sign;
    Row *TW = ralloc();
    if(*line=='\"')/*what does it mean?*/
    {
        line++;
        for(; *line!='\"' ; line++)
        {
            TW->value=(int)(*line);/*you need to use atoi() to convert string to number.*/
            addToList(dataList, TW);
        }
    }
    else
    {
        for(; *line!='\0'; line++)
        {
            for(tmp=0, sign=1 ; *line!=','; line++)
            {
                if(*line=='-')
                    sign=-1;
                else if(*line!='+')
                    tmp=tmp*10+(((int)(*line)-'0')*sign);/*atoi(). what did you do here?*/
            }
            TW->value=tmp;
            addToList(dataList, TW);
            if(*line==' ') /*why?*/
                line++;
        }
    }
}

char **getOperands(char *line, int lineNumber)/*Return an array of strings, representing the operands. Comma checks included*/
{
    char **operands = (char **)calloc(sizeof(char), MAXWORD * 2);
    char *thirdOperand = NULL;
    char *tmp = NULL;
    line = getWord(line, operands[0]);
    
    
    if (operands[0] != NULL)
    {
        if (*operands[0] == ',')
        {
            errorLog(lineNumber, "unnecessary ',' character.");
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
            if (*operands[1] == ',')
            {
                errorLog(lineNumber, "unnecessary ',' character.");
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
    isComma =  (*(--word) == ',');

    *word = '\0';

    return isComma;
}

int isRegister(char *operand)
{
    int registerNum;
    if (*operand == 'r')
    {
        operand++;
        if(isStringNumber(operand))
        {
            registerNum = atoi(operand);
            return (registerNum >= 0 && registerNum <= 7 && *(++operand) == '\0');            
        }
    }
    return 0;   
}

void addOperandTypeToWord(OpWord *word, int value, int operandType)
{
    if (operandType == SOURCE_OPERAND)
    {
        word->inVal = value;
    }
    else
    {
       word->outVal = value;
    }    
}

void addOperand(OpWord *operation, Rule *rule, char *operand, Int12 *codedOperand, int operandType, int lineNumber)
{
    struct addressingMethod *method = getAddressingMethod(rule, operandType);

    if (*operand == '#')/*Immediate Addressing*/
    {
        
        if (method->immediate)
        {
            addOperandTypeToWord(operation, IMMEDIATE_ADDRESSING, operandType);
            if (!isStringNumber(++operand))
            {
                errorLog(lineNumber, strcat(operand - 1, " - invalid operand. must be a number."));
            }
            else
            {
                codedOperand->value = atoi(operand);
            }           
        }
        else
        {
            errorLog(lineNumber, strcat("immeidate addressing operand is not supported for the command: ", rule->name));
        }       
    }
    else if (*operand == '%') /*Relative Addressing*/
    {
        if (method->relative)
        {
            addOperandTypeToWord(operation, RELATIVE_ADDRESSING, operandType);
        }
        else
        {
            errorLog(lineNumber, strcat("relative addressing operand is not supported for the command: ", rule->name));
        }
        
        
    }
    else if (isRegister(operand)) /*Register Addressing*/
    {
        if (method->registerDirect)
        {
            codedOperand = intToRegister(atoi(++operand));
            addOperandTypeToWord(operation, REGISTER_DIRECT_ADDRESSING, operandType);
        }
        else
        {
            errorLog(lineNumber, strcat("register addressing operand is not supported for the command: ", rule->name));
        }        
    }
    else /*Direct addressing*/
    {
        if (method->direct)
        {
            addOperandTypeToWord(operation, REGISTER_DIRECT_ADDRESSING, operandType);
        }
        else
        {
            errorLog(lineNumber, strcat("direct addressing operand is not supported for the command: ", rule->name));
        }       
    }
}

void addRowToCodeList(List *list, int address ,Int12 value, char ARE)
{
    Row *row = ralloc();

    row->address = address;
    row->value = value.value;
    row->ARE = ARE;

    addToList(list, row);
}
