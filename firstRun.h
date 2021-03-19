#ifndef FIRST_RUN_INCLUDED
#define FIRST_RUN_INCLUDED

#include "rulesHash.h"
#include "linkedList.h"
#include "getInput.h"
#include "tables.h"
#include "errors.h"
#include "binary.h"
#include "output.h"
#include "dynamicTable.h"


void first(char *fileName);
int isEmpty(char * line); /*is it an empty line or a comment line*/
int isNotAbsolute(int addressingMethod);
int isItDir(char *line); /*is it a directive statment - data, string, labels etc*/
int isItLable(int lineNumber, char *word/*, Symbols *list*/); /*not implemented the second argument yet*/
int datalen(char *line, char *type);
void dataCoding(char *line, struct lnode *dataList);
void dataCoding1(char *line, Array *dataList);
int validLabel(char *word);
char **getOperands(char *line, int lineNumber);/*Return an array of strings, representing the operands. Comma checks included*/
int trimComma(char *word);/*delete a comma at the end of an operand, and return an indication if there was a comma.*/
int isRegister(char *operand);
void addOperandTypeToWord(OpWord *word, int value, int operandType);
Int12 *addOperand(OpWord *operation, Rule *rule, char *operand, int operandType, int lineNumber);
void addRowToCodeList(List *list, int address ,Int12 value, char ARE);
void second(char *file, List *codeList, List *dataList, Symbols *SymbolList);

#endif