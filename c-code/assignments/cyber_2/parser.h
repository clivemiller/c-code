#include <stdio.h>
#include <stdbool.h>

char getOperationType(char input[]); // 0 is invalid, +, -, /, *, %
void readSafeInput(char input[]); // reads input. 
bool parseTwoValues(char input[], char out1[], char out2[], char opType); // splits input into two values
int getStrORNumOp(char out1[], char out2[], char opType); // 0 is invalid, 1 is two nums, 2 is num and char, 3 is char and num
bool validateInputCharacters(char input[]);


