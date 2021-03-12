#include "dataModel.h"
#include "common.h"

#define HASHSIZE 101
#define RULESNUM 16
#define LETTERSNUM 31


unsigned int hash(char *s);

Rule *getRule(char *s);

Rule *setRule(Rule rule);

void createRulesTable();

int isValidCommand(char *command);

int getAddressingMethod(Rule *rule, int operandType)
