#include "Tokenize.h"

// implementation of tokenize function
int tokenize(char *fileName) {
  filePtr = fopen(fileName, "r");
  if (filePtr == NULL) {
    printf("Error opening file.\n");
    exit(1);
  }

  // reset globals
  tokensIndex = 0;
  currentTokenIndex = 0;
  isInString = 0; 
  currentStringIndex = 0;

  int c = 0;

  while (((c = fgetc(filePtr)) != EOF) && tokensIndex < MAX_TOKENS) {
    // comment handling: skip over comments
    if (c == '/') {
        if (CommentHandler()) {
            continue;
        }
    }

    // string handling: store the string literal
    if (c == '"') {
      StringCapHandler();

      continue;
    }

    // if we are currently in a string, add the character to the current string token and continue
    if (isInString) {
      InStringHandler(c);

      continue;
    }

    // character literal handling: store the character literal
    if (c == '\'') {
        CharLiteralHandler();

        continue;
    }

    // handling token end based on whitespace, and whitespace skipping
    if (isspace(c)) {
      WhitespaceHandler();

      // no current token (passing over consecutive spaces)
      continue;
    }

    // operator handling
    if (OperatorHandler(c)) {
        continue;
    }

    // if we reach here, we are at the start or middle of a token. If at the start, set the token type to unsorted
    AddCharToToken(c);
  }

  // null terminator for last token since while loop wont reach it
  FinalizeLastToken();

  fclose(filePtr);

  // Classify all tokens as keywords
  ClassifyKeywords();

  // return the amount of tokens
  return tokensIndex;
}