#ifndef BINARY_INCLUDED
#define BINARY_INCLUDED

#include "dataModel.h"

Int12 *wordToInt12(OpWord *);
unsigned int wordToInt(OpWord *);
unsigned int int12ToInt(Int12 *);
Int12 *intToRegister(int);

#endif