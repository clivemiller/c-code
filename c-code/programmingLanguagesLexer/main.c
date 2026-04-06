#include "Tokenize.h"

// main:
// - expected command line argument: file name
// - initializes the tokenization process and prints the tokens
int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: %s <filename>\n", argv[0]);
    return 1;
  }
  
  char *fileName = argv[1];
  int count = tokenize(fileName);

  printf("--- TOKENS ---\n");
  printTokens(count);

  return 0;
}



