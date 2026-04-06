#ifndef HELPERS
#define HELPERS

#include <stdint.h>
#include "Globals.h"

enum { 
    UN_SORTED = 0, 
    STRING = 1, 
    CHARACTER_LITERAL = 2, 
    OPERATOR = 3, 
    KEY_WORD = 4,
    KW_WHILE = 5,
    KW_IF = 6,
    STATEMENT = 7
};

void printTokens(int n);
int CommentHandler(void);
void StringCapHandler(void);
void InStringHandler(int c);
void CharLiteralHandler(void);
void WhitespaceHandler(void);
void AddCharToToken(int c);
void FinalizeLastToken(void);
int OperatorHandler(int c);
void ClassifyKeywords();

#endif