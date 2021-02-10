#include <stdio.h>
#include <stdlib.h>
#include "binary.h"

void testBinary();

int main()
{
    testBinary();

    return 0;
}

void testBinary()
{
    OpWord *word;
    Int12 *a;
    Int12 *b;
    Int12 *reg;
    /*unsigned int wordNum;
    unsigned int negative;*/

    word = (OpWord *)malloc(sizeof(OpWord));
    a = (Int12 *)malloc(sizeof(Int12));
    b = (Int12 *)malloc(sizeof(Int12));
    reg = (Int12 *)malloc(sizeof(Int12));

    word->opcode = 2;
    word->funct = 10;
    word->inVal = 3;
    word->outval = 1;

    a->value = -1;
    b->value = 1;
    reg= intToRegister(3);

    printf("\nbinary word: %03X \nbinary negative one: %03X \nbinary one: %03X \nbinary register 3: %03X \n", 
        wordToInt(word), int12ToInt(a), int12ToInt(b),int12ToInt(reg));

    free(word);
    free(a);
    free(b);
    free(reg);
}
