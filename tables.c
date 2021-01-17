struct mCode /*12 digit machine code line*/
{
    /* 12 digit */
};

struct objects /*output table*/
{
    int address;
    mCode line;
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



