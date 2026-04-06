#ifndef TOKENIZER
#define TOKENIZER

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "Helpers.h"

// tokenize:
// - Opens and reads a file character by character
// - Splits the content into tokens based on whitespace
// - Stores tokens in a 2D array
// - Returns the number of tokens found
int tokenize(char *fileName);

#endif