#ifndef ERRORS_INCLUDED
#define ERRORS_INCLUDED

void errorLog(int, char *);
void errorLogCat(int line, char *errorCat1, char *errorCat2);

void printErrors();

void freeLogMemory();

int areErrorsExist();

#endif