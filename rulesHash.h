#ifndef RULES_HASH_INCLUDED
#define RULES_HASH_INCLUDED

#include "dataModel.h"
#include "common.h"

#define HASHSIZE 101
#define RULESNUM 16
#define LETTERSNUM 31


unsigned int hash(char *s);

Rule *getRule(char *s);

Rule *setRule(Rule rule);

void createRulesTable();

void freeRulesTable();

int isValidCommand(char *command);

AddressingMethod *getAddressingMethod(Rule *rule, int operandType);

#endif