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
    int L, lineNumber = 1, tmp=0;
    char label[MAXWORD], EXlabel[MAXWORD];
    char **firstWord = psalloc();
    char *line, *Fline = (char *)calloc(sizeof(char), MAXLINE);
    /*List *codeList = listalloc();*/
    List *dataList = listalloc();
    Symbols *SymbolList = Slistalloc();
    Rule *rule;
    char **operands;
    OpWord *operation;
    Int12 *codedOp1 = NULL, *codedOp2 = NULL;
    Array *codeList1 = createDynamicTable();
    /*Array *dataList1 = createDynamicTable();*/
 
    if (line == NULL || firstWord == NULL /*|| EXlabel == NULL*/)
    {
        mallocError("string");
    }
    /*line=readLine(file);
    deleteBlanks(line);*/
    createRulesTable();
    IC = 100;
    DC = 0;
    while(fgets(Fline, MAXLINE, Sfile) != NULL)
    {
        line=Fline;
        /*printf("\nfirstRunLoopStart: datalist.value.address = %d, datalist.value.value=%d, labelFlag=%d\n", dataList->value.address, dataList->value.value, labelFlag);*/
        if(lineNumber>1)
            printlist(dataList);
        labelFlag=0;
        deleteBlanks(lineNumber, line);
        printf("line %d: |%s|\n", lineNumber, line);
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
                                printf("checkpoint exteral label\n");
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
                        codedOp1 = i12alloc();                       
                        if (*operands[1] != '\0')
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
                    
                    /*addRowToCodeList(codeList, IC++, *wordToInt12(operation), 'A');*/
                    addRowToDynamicTable(codeList1, IC++, *wordToInt12(operation), 'A');
                    if (operands[0] != NULL)
                    {
                        /*addRowToCodeList(codeList, IC++, *codedOp1, 'N');*/
                        addRowToDynamicTable(codeList1, IC++, *codedOp1, 'N');
                        if (operands[1] != NULL)
                        {
                            /*addRowToCodeList(codeList, IC++, *codedOp2, 'N');*/
                            addRowToDynamicTable(codeList1, IC++, *codedOp2, 'N');
                        }                        
                    }                                        
                }
                else
                {
                    errorLog(lineNumber, strcat("Unknown command: ", *firstWord));
                }
                 
                
            }
            /*line=readLine(file);
            deleteBlanks(line);*/
        }
        lineNumber++;
        /*printSymbols(SymbolList, 1);*/
        printf("firstRunLoopEnd: datalist.value.address = %d, datalist.value.value=%d, labelFlag=%d\n", dataList->value.address, dataList->value.value, labelFlag);
    }
    printf("now what??\n");
    if(areErrorsExist())
    {
        printf("errors\n");
        printErrors();
    }
    else
    {
        printf("No errors\n");
        ICF=IC;
        DCF=DC;
        setVal(SymbolList, ICF);
        /*second(Sfile, codeList, dataList, SymbolList);*/
    }
    /*printCodeListDebug(codeList);*/
    printDynamicListDebug(codeList1);
}

int isEmpty(char *line)
{
    if(line[0]==';' || line[0]=='\0')
        return 1;
    return 0;
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
            return (i-1);/*starts with appostrophes, ends with appostrophes, total 2 spare cahracters, but indexes starts from 0*/
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
    int tmp, i,j/*, sign*/;
    char num[MAXWORD];
    Row *TW = ralloc();
    /*printf("!%s!\n", line);*/
    if(*line=='\"')
    {
        line++;
        for(i=1; *line!='\"' ;i++, line++)
        {
            TW->value=(int)(*line);
            TW->address=DC+i;
            addToList(dataList, TW);
        }
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
                printf("dataCoding before addToList. datalist: %d, %d, value=%d\n",dataList->value.address, dataList->value.value, TW->value);
                addToList(dataList, TW);
                printf("dataCoding after addToList. datalist: %d, %d, value=%d\n\n",dataList->value.address, dataList->value.value, TW->value);
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
    /*printf("inside getOperands with: %s\n", line);*/
    line = getWord(line, tmp1);

    if (*tmp1 != NULL)
    {
        operands[0] = *tmp1;
        if (*operands[0] == ',')
        {
            errorLog(lineNumber, "unnecessary ',' character.");
        }
        
        if (!trimComma(operands[0])) /*if first operand doesn't end with a comma*/
        {
            line = getWord(line, tmp2);
            if (*tmp2 != NULL && **tmp2 != '\0')
            {
                printf("2: tmp2 = '%s'\n", *tmp2);
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
    printf("inside addRowToCodeList\n");
    row->address = address;
    row->value = value.value;
    row->ARE = ARE;
    printf("row: address = %d, value = %d, ARE = %c\n", row->address, row->value, row->ARE);
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