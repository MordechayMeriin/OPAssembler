#ifndef FIRST_RUN_INCLUDED
#define FIRST_RUN_INCLUDED

#include "rulesHash.h"
#include "linkedList.h"
#include "getInput.h"
#include "errors.h"
#include "binary.h"
#include "output.h"


void first(char *fileName);
int isEmpty(char * line); /*is it an empty line or a comment line*/
int isNotAbsolute(int addressingMethod);
int isItDir(char *line); /*is it a directive statment - data, string, labels etc*/
int isItLable(int lineNumber, char *word); /**/
int datalen(char *line, char *type, int lineNumber); /*returns the number of data cells*/
void dataCoding(char *line, struct lnode *dataList, int DC, int lineNumber); /*codes the data to datalist*/
int validLabel(char *word); /*returns 1 if the string is a valid label name and 0 if not*/
char **getOperands(char *line, int lineNumber);/*Return an array of strings, representing the operands. Comma checks included*/
int trimComma(char *word);/*delete a comma at the end of an operand, and return an indication if there was a comma.*/
int isRegister(char *operand);/*returns 1 if the string is a register name and 0 if not*/
void addOperandTypeToWord(OpWord *word, int value, int operandType);
Int12 *addOperand(OpWord *operation, Rule *rule, char *operand, int operandType, int lineNumber);
void addRowToCodeList(List *list, int address ,Int12 value, char ARE);
void second(char *file, List *codeList, List *dataList, Symbols *SymbolList, int ICF, int DCF);

#endif