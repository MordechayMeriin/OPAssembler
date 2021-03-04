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

/*struct symbols
{
    char symbol[10];
    int value;
    char attributes[4]; /*code/entry/data/external*
};*/
typedef struct symbols{
    Int12 address;
    char *name;
    char *attributes;
    Symbols *next;
    int value;
} Symbols;

Symbols *Slistalloc()
{
    Symbols *p;
    p = (Symbols *)calloc(sizeof(Symbols), 1);
    if (p == NULL)
    {
        mallocError("Symbols list node");
    }  
    return p;
}

void addToTable(struct symblols *newS, char *name, char *attributes, int val)
{
    if(newS->next == NULL)
    {
        if (strcmp(newS->nex.name, *name)==0)
        {
            /*error: two symbols with the same name*/
            break;
        }
        else
        {
            Symbols *tempS;
            strcpy(newS->name ,*name);
            strcpy(newS->attributes ,*attributes);
            newS->value=val;       
            tempS = Slistalloc();          
            newS->next = tempS;
        }
    }
    else
    {
        addToTable(newS->next, name, attributes, val);
    }
        
}

void setAddress(struct symblols *s, char *name, Int12 address) /*for the second run*/
{
    if (strcmp(s->nex.name, *name)==0)
    {
        s->address=address;
    }
    else if(newS->next != NULL)
        setAddress(s->next, name, address);
    else
    {
        /*error*/
    }
}
