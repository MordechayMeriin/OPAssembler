struct word /*12 digit machine code line*/
{
    int opcode: 4;
    int funct: 4;
    int inVal: 2;
    int outval: 2;
};

struct objects /*output table*/
{
    int address;
    int line: 12;
    char ARE;
};

struct label /*entries and externals tables*/
{
    char name[10];
    int address;
};

struct symbols
{
    char symbol[10];
    int value;
    char attributes[4]; /*code/entry/data/external*/
};



