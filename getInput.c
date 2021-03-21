#include "getInput.h"
#include "common.h"
#include "errors.h"
#include <string.h>

FILE *openFile(char *fileName)
{
	FILE *pf;
	char *fullFileName;
	char ending[] = ".as";
	fullFileName = (char *)malloc(strlen(fileName) + strlen(ending));
	if (fullFileName == NULL)
	{
		mallocError("string");
	}
	
	fullFileName[0] = '\0';

	strcat(fullFileName, fileName);
	strcat(fullFileName, ending);
	pf = fopen(fullFileName, "r");
	if (pf == NULL)
	{
		printf("An error occured when trying to read the file filename");
		exit(2);
	}
	free(fullFileName);
	return pf;
}

void deleteBlanks(int lineNumber, char *line)
{
	char tmp[MAXLINE];
	int i=0, j;
	for (j=0 ; j<MAXLINE && line[j]!='\0' ; j++)
	{
		if(line[j]=='\n')
		{
			break;
		}
		else if(!isspace(line[j]))
		{
			tmp[i++]=line[j];
			if(line[j]==',' || line[j]==':') /*',' and ':' could appear without a space after them, but it easier to analye when there is one*/
				tmp[i++]=' ';
		}
		else if(i==0 || line[j+1]==',' || tmp[i-1]==' ')
		{
			if(tmp[i-2]==',' && line[j+1]==',')
				errorLog(lineNumber, "Syntax error: two commas in a row");
		}
		else if(line[j]!='\n' || (isdigit(tmp[i-1]) && isdigit(line[j+1])))
		{
			tmp[i++]=' ';
		}
	}
	while(isSpace(tmp[i-1]) && i>1)
	{
		i--;
	}
	tmp[i]='\0';
	strcpy(line, tmp);
}

char *getWord(char *line, char **word, int lineNumber)
{
	char *c = (char *)calloc(sizeof(char), MAXWORD);
	char *str = c;
	int wordCounter = 0;
	while (isSpace(*line) && *line != '\0')
		line++;

	while (!isSpace(*line) && *line != '\0')
	{
		
		if (wordCounter == MAXWORD - 1)
		{
			errorLog(lineNumber, "word is too long");
			strcpy(c,"-exception");
			c+=10;
			break;
		}
		
		*c = *line;
		if (*c == ',')
		{
			c++;
			line++;
			break;
		}
		c++;
		line++;
		wordCounter++;
	}
	*c = '\0';
	*word = str;

	if(*line == ' ')
		line++;
	return line;
}

int isSpace(char c)
{
	return(c == ' ' || c == '\t' || c == '\n');
}
