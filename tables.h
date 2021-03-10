#ifndef TABLES_INCLUDED
#define TABLES_INCLUDED

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

/*struct symbols
{
    char symbol[10];
    int value;
    char attributes[4]; /*code/entry/data/external*
};*/


#endif