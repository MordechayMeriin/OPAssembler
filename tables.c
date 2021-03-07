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
    if(newS == NULL)
    {  
        newS= Slistalloc();
        strcpy(newS->name ,*name);
        strcpy(newS->attributes ,*attributes);
        newS->value=val;       
    }
    else if (strcmp(newS->name, *name)==0)
    {
        errorLog("two symbols with the same name");
    }
    else if(newS->next == NULL)
    {  
        newS->next = Slistalloc();
        strcpy(newS->next.name ,*name);
        strcpy(newS->next.attributes ,*attributes);
        newS->next.value=val;       
    }
    else
    {
        addToTable(newS->next, name, attributes, val);
    }
        
}

void setVal(struct symblols *s, int val)
{
    s->value+=val;
    if(S->next != NULL)
        setVal(s->next, val);
}

void setAddress(struct symblols *s, char *name, Int12 address) /*for the second run*/
{
    if (strcmp(s->next.name, *name)==0)
    {
        s->address=address;
    }
    else if(S->next != NULL)
        setAddress(s->next, name, address);
    else
    {
        /*error*/
    }
}
