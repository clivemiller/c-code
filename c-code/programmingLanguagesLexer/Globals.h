#ifndef GLOBALS
#define GLOBALS

#include <stdio.h>

#define MAX_TOKENS 1000
#define MAX_TOKEN_LEN 256

extern char tokenArray[MAX_TOKENS][MAX_TOKEN_LEN];
extern int tokensIndex;
extern int currentTokenIndex;
extern int isInString;
extern int currentStringIndex;
extern FILE *filePtr;

#endif
