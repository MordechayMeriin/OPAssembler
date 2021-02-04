
#include <stdlib.h>
typedef struct opword /*12 digit machine code line*/
{
    unsigned int opcode: 4;
    unsigned int funct: 4;
    unsigned int inVal: 2;
    unsigned int outval: 2;
} OpWord;

typedef struct int12{
    signed int value: 12;
} Int12;

typedef union
{
    OpWord op;
    Int12 val12;
} Word;

typedef struct addressingMethod
{
    unsigned int m0: 1;
    unsigned int m1: 1;
    unsigned int m2: 1;
    unsigned int m3: 1;
}AddressingMethod;


typedef struct rule
{
    unsigned int opcode: 4;
    unsigned int funct: 4;
    char *name;
    AddressingMethod inAd;
    AddressingMethod outAd;
} Rule;


Word *walloc()
{
    Word *p;
    p = (Word *)calloc(sizeof(Word), 1);
    if (p == NULL)
    {
        printf("%s\n", "Failed to allocate memory for a new word.");
        exit(2);
    }  
    return p;
}
