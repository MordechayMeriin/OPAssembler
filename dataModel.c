
typedef struct opword /*12 digit machine code line*/
{
    signed int opcode: 4;
    signed int funct: 4;
    signed int inVal: 2;
    signed int outval: 2;
} OpWord;

typedef struct int12{
    signed int value: 12;
} Int12;

typedef union
{
    OpWord op;
    Int12 val12;
} Word;

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
