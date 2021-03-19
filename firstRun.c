#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "firstRun.h"


void first(char *fileName)
{
    FILE *file = openFile(fileName);
    extern int IC, DC, ICF, DCF;
    extern void second(char *,List *, List *, Symbols *);
    short int labelFlag=0;
    int L, lineNumber = 1, tmp=0;
    char label[MAXWORD], EXlabel[MAXWORD];
    char **firstWord = psalloc();
    char *line, *Fline = (char *)calloc(sizeof(char), MAXLINE);
    List *codeList = listalloc();
    List *dataList = listalloc();
    Symbols *SymbolList = Slistalloc();
    Rule *rule;
    char **operands;
    OpWord *operation;
    Int12 *codedOp1 = NULL, *codedOp2 = NULL;
 
    if (Fline == NULL || firstWord == NULL /*|| EXlabel == NULL*/)
    {
        mallocError("string");
    }
    /*line=readLine(file);
    deleteBlanks(line);*/
    createRulesTable();
    IC = 100;
    DC = 0;
    while(fgets(Fline, MAXLINE, file) != NULL)
    {
        line=Fline;
        /*printf("\nfirstRunLoopStart: datalist.value.address = %d, datalist.value.value=%d, labelFlag=%d\n", dataList->value.address, dataList->value.value, labelFlag);*/
        /*if(lineNumber>1)
            printlist(dataList);*/
        labelFlag=0;
        
            deleteBlanks(lineNumber, line);
        /*printf("\nline %d: |%s|\n", lineNumber, Fline);*/
        if(!isEmpty(line))
        {
            line = getWord(line, firstWord);
            /*printf("word: %s\n", *firstWord);*/
            if(isItLable(lineNumber, *firstWord))
            {
                labelFlag=1;
                strcpy(label, *firstWord);
                line = getWord(line, firstWord);
            }
            if(isItDir(*firstWord))
            {
                if (strcmp(*firstWord, ".data")==0 ||  strcmp(*firstWord, ".string")==0)
                {
                    if(labelFlag)
                    {
                        addToTable(SymbolList, label, "data", DC, lineNumber);
                    }
                    tmp=datalen(line, *firstWord);
                    if(tmp)
                    {
                        dataCoding(line, dataList);
                        DC+=tmp;
                        /*dataCoding1(line, dataList1);*/
                        printf("DC=%d\n", DC);
                    }
                    else
                        errorLog(lineNumber, "Invalid data");
                }
                else if(strcmp(*firstWord, ".extern")==0 ||  strcmp(*firstWord, ".entry")==0)
                {
                    if(strcmp(*firstWord, ".extern")==0)
                    {
                        line = getWord(line, firstWord);
                        strcpy(EXlabel, *firstWord);
                        if (validLabel(EXlabel))
                        {
                            if (*line=='\0')
                            {
                                /*printf("checkpoint exteral label\n");*/
                                addToTable(SymbolList, EXlabel, "external", 0, lineNumber);
                            }
                            else
                            {
                                errorLog(lineNumber, "extern direction contains more than one operand");
                            }
                        }
                    }
                }
                else
                {
                    errorLog(lineNumber, strcat("Invalid direction: ", *firstWord));
                }
                
            }
            else /*it is a command line*/
            {
                if(labelFlag)
                {
                    addToTable(SymbolList, label, "code", IC, lineNumber);
                }
                if (isValidCommand(*firstWord))
                {
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

                    
                    if (*operands[0] != '\0')
                    {
                        L++;                      
                        if (*operands[1] != '\0')
                        {
                            L++;
                            codedOp1 = addOperand(operation, rule, operands[0], SOURCE_OPERAND, lineNumber);                            
                            codedOp2 = addOperand(operation, rule, operands[1], TARGET_OPERAND, lineNumber);
                            
                            /*printf("2 operands: operation inVal = %d. outVal = %d.\n", operation->inVal, operation->outVal);*/
                            addRowToCodeList(codeList, IC++, *wordToInt12(operation), 'A');
                            addRowToCodeList(codeList, IC++, *codedOp1, (isNotAbsolute(operation->inVal)) ? 'N' : 'A');
                            addRowToCodeList(codeList, IC++, *codedOp2, (isNotAbsolute(operation->outVal)) ? 'N' : 'A');
                        }
                        else
                        {
                            
                            codedOp1 = addOperand(operation, rule, operands[0], TARGET_OPERAND, lineNumber);
                            /*printf("1 operand: operation inVal = %d. outVal = %d.\n", operation->inVal, operation->outVal);*/
                            addRowToCodeList(codeList, IC++, *wordToInt12(operation), 'A');
                            addRowToCodeList(codeList, IC++, *codedOp1, (isNotAbsolute(operation->outVal)) ? 'N' : 'A');
                        }
                    }
                    else
                    {
                        addRowToCodeList(codeList, IC++, *wordToInt12(operation), 'A');
                    }
                                                     
                }
                else
                {
                    errorLog(lineNumber, strcat("Unknown command: ", *firstWord));
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
        List *tmp;
        ICF=IC-1;
        DCF=DC;
        setVal(SymbolList, ICF);
        setData(dataList);
        printSymbols(SymbolList, 1);
        free(file);
        for(tmp=codeList; tmp->next!=NULL ; tmp=tmp->next)
        ;
        tmp->next=dataList;
        printCodeListDebug(codeList);
        second(fileName, codeList, dataList, SymbolList);
        /*printlist(dataList);*/
    }
    
}

int isEmpty(char *line)
{
    if(line[0]==';' || line[0]=='\0' || line[0]=='\n')
        return 1;
    return 0;
}

int isNotAbsolute(int addressingMethod)
{
    return (addressingMethod == DIRECT_ADDRESSING || addressingMethod == RELATIVE_ADDRESSING);
}

int isItDir(char *line)
{
    if( line[0]=='.')
    {
        return 1;
    }
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
    if(!isalpha(word[i]))
        return 0;
    for( ; word[i]!='\0' ; i++)
    {
        if(!isalpha(word[i]) && !isdigit(word[i]))
            return 0;
    }
    return 1;
}

int datalen(char *line, char *type)
{
    int i, j=0;
    if(strcmp(type, ".string")==0)
    {
        /*printf("string datalen: ||%s||, %d\n", line, strlen(line));*/
        if(strlen(line)<=2)
            return 0;
        for(i=1; line[i]!='\0' && line[i]!='\"' ; i++)
            ;
        /*printf("datalen checkpoint: !%s! %d\n", line, i);*/
        if(line[0]=='\"' && line[i]=='\"' && (line[i+1]=='\0' || (line[i+1] == ' ' /*&& line[i+2]=='\n'*/)))
            return (i);/*starts with appostrophes, ends with appostrophes, total 2 spare cahracters, but indexes starts from 0*/
    }
    if(strcmp(type, ".data")==0)
    {
        /*printf("data datalen: ||%s||, %d\n", line, strlen(line));*/
        for(i=0; line[i]!='\0' ; i++)
        {
            if(isdigit(line[i]) || line[i]==' ' || line[i]==',' || line[i]=='-' || line[i]== '+')
            {
                if((line[i]=='+' || line[i]=='-') && !isdigit(line[i+1]))
                    j=0;
                else if(line[i]==',' && line[i+1]=='\0')
                    j=0;
                else if(line[i]==',' && i==0)
                    j=0;
                else if(line[i]==',' || j==0)
                {
                    j++;
                }
                if(j==0)
                    break;
            }
        }
        /*printf("datalen checkpoint: !%s! %d\n", line, j);*/
    }
    return j;
}

void dataCoding(char *line, struct lnode *dataList)
{
    extern int DC;
    int tmp, i,j;
    char num[MAXWORD];
    Row *TW = ralloc();
    if(*line=='\"')
    {
        line++;
        for(i=1; *line!='\"' ; i++, line++)
        {
            TW->value=(int)(*line);
            TW->address=DC+i;
            TW->ARE = 'A';
            addToList(dataList, TW);
        }
        TW->value=(int)('\0');
        TW->address=DC+i;
        addToList(dataList, TW);
    }
    else
    {
        for(j=1; *line!='\0'; line++)
        {
            for(tmp=0/*, sign=1*/, i=0 ; *line!=',' && *line!='\n' && *line!=' ' && *line!='\0' ; i++, line++)
            {
                /*if(*line=='-')
                    sign=-1;
                else if(*line!='+')
                    tmp=tmp*10+(((int)(*line)-'0')*sign);
                */
                num[i]=*line;
            }
            num[i]='\0';
            tmp=atoi(num);
            if(isdigit(num[0]) || num[0]=='-' || num[0]=='+')
            {
                printf("!%s! = !%d!\n", num, tmp);
                TW->address=DC+j;
                TW->value=tmp;
                TW->ARE = 'A';
                j++;
                /*printf("dataCoding before addToList. datalist: %d, %d, value=%d\n",dataList->value.address, dataList->value.value, TW->value);*/
                addToList(dataList, TW);
                /*printf("dataCoding after addToList. datalist: %d, %d, value=%d\n\n",dataList->value.address, dataList->value.value, TW->value);*/
                /*if(*line==' ')
                    line++;*/
            }
            if(*line=='\0')
                line--;
        }
    }
}

char **getOperands(char *line, int lineNumber)/*Return an array of strings, representing the operands. Comma checks included*/
{       
    char **operands = (char **)calloc(sizeof(char), MAXWORD * 2);
    char **thirdOperand = psalloc();
    char **tmp1 = psalloc(), **tmp2 = psalloc();

    /*printf("inside getOperands. line = '%s'\n", line);*/

    line = getWord(line, tmp1);
    /*printf("getOperands 1: *tmp1 = '%s'\n", *tmp1);*/

    if (*tmp1 != NULL)
    {
        operands[0] = *tmp1;
        /*printf("getOperands 2: operands[0] = '%s'\n", operands[0]);*/
        if (*operands[0] == ',')
        {
            errorLog(lineNumber, "unnecessary ',' character.");
        }
        
        if (!trimComma(operands[0])) /*if first operand doesn't end with a comma*/
        {
            /*printf("getOperands 3: operands[0] = '%s'\n", operands[0]);*/
            line = getWord(line, tmp2);
            if (*tmp2 != NULL && **tmp2 != '\0')
            {
                /*printf("2: tmp2 = '%s'\n", *tmp2);*/
                if (**tmp2 == ',') 
                {
                    line = getWord(line, tmp2); 
                    operands[1] = *tmp2;
                }
                else
                {
                    errorLog(lineNumber, "2 operands without ',' seperate.");
                    operands[1] = *tmp2;                  
                }  
            }                       
        }
        else /*if first operand ends with a comma*/
        {
            line = getWord(line, tmp2);
        }
        operands[1] = *tmp2;  

        if (*operands[1] == ',')
        {
            errorLog(lineNumber, "unnecessary ',' character.");
        }

        line = getWord(line, thirdOperand);  

        if (strcmp(*thirdOperand, ""))
        {
            errorLog(lineNumber, "you can't have more then 2 operands.");
        }


             
        /*printf("5\n");   */
    }
    free(tmp1);
    free(tmp2);
    free(thirdOperand);
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

    if (isComma)
    {
       *word = '\0';
    }
    
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

Int12 *addOperand(OpWord *operation, Rule *rule, char *operand, int operandType, int lineNumber)
{
    /*printf("inside addOperand: %s\n", operand);*/
    Int12 *codedOperand = i12alloc();
    struct addressingMethod *method = getAddressingMethod(rule, operandType);
    if (*operand == '#')/*Immediate Addressing*/
    {
        /*printf("%s is immediate.\n", operand);*/
        if (method->immediate)
        {
            addOperandTypeToWord(operation, IMMEDIATE_ADDRESSING, operandType);
            if (!isStringNumber(++operand))
            {
                /*printf("after ++operand: %s.\n", operand);*/
                errorLog(lineNumber, strcat(operand - 1, " - invalid operand. must be a number."));
            }
            else
            {
                /*printf("after ++operand: %s.\n", operand);*/
                codedOperand->value = atoi(operand);
                /*printf("codedOperand: %d.\n", codedOperand->value);*/
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
            addOperandTypeToWord(operation, DIRECT_ADDRESSING, operandType);
        }
        else
        {
            errorLog(lineNumber, strcat("direct addressing operand is not supported for the command: ", rule->name));
        }       
    }

    return codedOperand;
}

void addRowToCodeList(List *list, int address ,Int12 value, char ARE)
{
    Row *row = ralloc();
    row->address = address;
    row->value = value.value;
    row->ARE = ARE;
    addToList(list, row);
}

void dataCoding1(char *line, Array *dataList)
{
    int tmp, i;
    char num[MAXWORD];
    Row *TW = ralloc();
    if(*line=='\"')
    {
        line++;
        for(; *line!='\"' ; line++)
        {
            TW->value=(int)(*line);
            addToDynamicTable(dataList, TW);
        }
    }
    else
    {
        for(; *line!='\0'; line++)
        {
            for(tmp=0, i=0 ; *line!=',' && *line!='\n' && *line!=' ' && *line!='\0' ; i++, line++)
            {
                num[i]=*line;
            }
            num[i]='\0';
            tmp=atoi(num);
            if(isdigit(num[0]) || num[0]=='-' || num[0]=='+')
            {
                printf("!%s! = !%d!\n", num, tmp);
                TW->value=tmp;
                printf("dataCoding before addToList. datalist: %d, %d, value=%d\n",dataList->array->address, dataList->array->value, TW->value);
                addToDynamicTable(dataList, TW);
                printf("dataCoding after addToList\n");
            }
            if(*line=='\0')
                line--;
        }
    }
}