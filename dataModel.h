#ifndef DATAMODEL_INCLUDED
#define DATAMODEL_INCLUDED

#define WORD_SIZE 12
#define OPCODE_SIZE 4
#define FUNCT_SIZE 4
#define INVAL_SIZE 2
#define OUTVAL_SIZE 2


typedef struct opword /*12 digit machine code line*/
{
    unsigned int opcode: OPCODE_SIZE;
    unsigned int funct: FUNCT_SIZE;
    unsigned int inVal: INVAL_SIZE;
    unsigned int outval: OUTVAL_SIZE;
} OpWord;

typedef struct int12{
    signed int value: WORD_SIZE;
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
    unsigned int opcode: OPCODE_SIZE;
    unsigned int funct: FUNCT_SIZE;
    char *name;
    AddressingMethod inAd;
    AddressingMethod outAd;
} Rule;

Word *walloc();

#endif