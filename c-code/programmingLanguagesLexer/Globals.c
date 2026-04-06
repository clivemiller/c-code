#include "Globals.h"

char tokenArray[MAX_TOKENS][MAX_TOKEN_LEN];
int tokensIndex = 0;
int currentTokenIndex = 0;
int isInString = 0;
int currentStringIndex = 0;
FILE *filePtr = NULL;
