#include "rulesHash.h"
#include "linkedList.h"
#include "getInput.h"
#include "tables.h"
#include "errors.h"
#include "binary.h"


void first(FILE *file);
int isEmpty(char * line); /*is it an empty line or a comment line*/
int isItDir(char *line); /*is it a directive statment - data, string, labels etc*/
int isItLable(int lineNumber, char *word/*, Symbols *list*/); /*not implemented the second argument yet*/
int datalen(char *line, char *type);
void dataCoding(char *line, struct lnode *dataList);
int validLabel(char *word);
char **getOperands(char *line, int lineNumber);/*Return an array of strings, representing the operands. Comma checks included*/
int trimComma(char *word);/*delete a comma at the end of an operand, and return an indication if there was a comma.*/
int isRegister(char *operand);