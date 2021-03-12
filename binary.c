#include <stdlib.h>
#include <stdio.h>
#include "binary.h"
#include "common.h"


Int12 *wordToInt12(OpWord *pword)
{
    Int12 *pint;
    unsigned int outval;
    unsigned int inval;
    unsigned int funct;
    unsigned int opcode;

    pint = (Int12 *)calloc(sizeof(Int12), 1);
    if (pint == NULL)
    {
        mallocError("Int12");
    }

    outval = pword->outVal;
    inval = pword->inVal << OUTVAL_SIZE;
    funct = pword->funct << (OUTVAL_SIZE + INVAL_SIZE);
    opcode = pword->opcode << (OUTVAL_SIZE + INVAL_SIZE + FUNCT_SIZE);

    pint->value = outval | inval | funct | opcode;

    return pint;
}

unsigned int int12ToInt(Int12 *pint)
{
    unsigned int num;
    unsigned int mask;

    mask = MAX_12BIT_NUMBER;
    num = pint->value & mask;

    return num;
}

unsigned int wordToInt(OpWord *pword)
{
    unsigned int num;
    Int12 *pint;

    pint = wordToInt12(pword);
    num = int12ToInt(pint);

    free(pint);

    return num;
}

Int12 *intToRegister(int reg)
{
    Int12 *pint;

    if (reg > 7)
    {
        printf("r%d is not a valid register!", reg);
        exit(3);
    }
       
    pint = (Int12 *)calloc(sizeof(Int12), 1);
    if (pint == NULL)
    {
        mallocError("Int12");
    }

    pint->value = 1 << reg;

    return pint;
}