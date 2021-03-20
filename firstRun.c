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
    char label[MAXWORD], EXlabel[MAXWORD]; /*lables names*/
    char **firstWord = psalloc(); /*first word in line*/
    char *line /**/, *Fline /*pointer to first char in line*/ = (char *)calloc(sizeof(char), MAXLINE);
    List *codeList = listalloc(); /*list of commands and arguments*/
    List *dataList = listalloc(); /**/
    Symbols *SymbolList = Slistalloc(); /*list of symbols labeles etc*/
    Rule *rule;
    char **operands;
    OpWord *operation;
    Int12 *codedOp1 = NULL, *codedOp2 = NULL;
 
    if (Fline == NULL || firstWord == NULL)
    {
        mallocError("string");
    }
    createRulesTable();
    IC = 100;
    DC = 0;
    while(fgets(Fline, MAXLINE, file) != NULL)
    {
        line=Fline;
        labelFlag=0;
        deleteBlanks(lineNumber, line);
        if(!isEmpty(line))
        {
            line = getWord(line, firstWord); /*takes the first word in the line to firstWord, and moves line to point to the next word*/
            if(isItLable(lineNumber, *firstWord)) /*if the first word is a label*/
            {
                labelFlag=1;
                strcpy(label, *firstWord);
                line = getWord(line, firstWord); /*saves the label in another var and moved to the next word*/
            }
            if(isItDir(*firstWord)) /*it is a direction*/
            {
                if (strcmp(*firstWord, ".data")==0 ||  strcmp(*firstWord, ".string")==0)
                {
                    if(labelFlag)
                    {
                        addToTable(SymbolList, label, "data", DC, lineNumber); /*adds the label's details to the symbols list*/
                    }
                    tmp=datalen(line, *firstWord);
                    if(tmp)
                    {
                        dataCoding(line, dataList); /*saves the data to the memory in a seperate list*/
                        DC+=tmp;
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
                    addToTable(SymbolList, label, "code", IC, lineNumber);/*adds the label's details to the symbols list*/
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
                            
                            addRowToCodeList(codeList, IC++, *wordToInt12(operation), 'A');
                            addRowToCodeList(codeList, IC++, *codedOp1, (isNotAbsolute(operation->inVal)) ? 'N' : 'A');
                            addRowToCodeList(codeList, IC++, *codedOp2, (isNotAbsolute(operation->outVal)) ? 'N' : 'A');
                        }
                        else
                        {
                            
                            codedOp1 = addOperand(operation, rule, operands[0], TARGET_OPERAND, lineNumber);
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
        List *tmpList;
        ICF=IC-1;
        DCF=DC;
        setVal(SymbolList, ICF);
        setData(dataList);
        printSymbols(SymbolList, 1);
        free(file);
        for(tmpList=codeList; tmpList->next->next!=NULL ; tmpList=tmpList->next)
        ;
        tmpList->next=dataList;/*ataches dataList to the end of codelist*/

        printCodeListDebug(codeList);
        second(fileName, codeList, dataList, SymbolList); /*start the second run*/
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
        if(strlen(line)<=2)
            return 0;
        for(i=1; line[i]!='\0' && line[i]!='\"' ; i++)
            ;
        if(line[0]=='\"' && line[i]=='\"' && (line[i+1]=='\0' || (line[i+1] == ' ')))
            return (i);/*starts with appostrophes, ends with appostrophes, total 2 spare cahracters, but indexes starts from 0*/
    }
    if(strcmp(type, ".data")==0)
    {
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
            for(tmp=0, i=0 ; *line!=',' && *line!='\n' && *line!=' ' && *line!='\0' ; i++, line++)
            {
                num[i]=*line;
            }
            num[i]='\0';
            tmp=atoi(num);
            if(isdigit(num[0]) || num[0]=='-' || num[0]=='+')
            {
                TW->address=DC+j;
                TW->value=tmp;
                TW->ARE = 'A';
                j++;
                addToList(dataList, TW);
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
    Int12 *codedOperand = i12alloc();
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