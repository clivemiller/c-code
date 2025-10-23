#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// 0 is invalid, 1 is +, 2 is -, 3 is /, 4 is *, 5 is %
char getOperationType(char input[])
{
    if (input == NULL) return 0;
    for (int i = 0; input[i] != '\0'; ++i) {
        char c = input[i];
        switch (c) {
            case '+': return c;
            case '-': return c;
            case '/': return c;
            case '*': return c;
            case '%': return c;
            default: break;
        }
    }
    return '0';
}

// reads input. 
void readSafeInput(char input[])
{
    // 100 chars and a int up to int max, 11 chars, plus a operator 1 char, plus null terminator, buffer 113 chars
    char buff[113];
    int max = sizeof(buff);
    printf("Please enter (1) two integers or (2) one integer and one string (up to\n");
    printf("100 characters, contains letters a-z and/or A-Z only). Enter everything in one\n");
    printf("line, separated by an operator (NO WHITESPACES): \n");
    
    if (fgets(buff, max, stdin) != NULL) {
        // Remove trailing newline if present
        size_t len = strlen(buff);
        if (len > 0 && buff[len-1] == '\n') {
            buff[len-1] = '\0';
        }
        // Copy to output parameter
        strcpy(input, buff);
    }
}; 

// splits input into two values
void parseTwoValues(char input[], char out1[], char out2[], char opType)
{
    int out1d_index = 0;
    int out2d_index = 0;
    bool firstDone = false;
    
    for (int i = 0; i < strlen(input); i++) {
        if (!firstDone) {
            if (input[i] == opType) {
                firstDone = true;
                continue;
            }
            out1[out1d_index++] = input[i];
        } else {
            out2[out2d_index++] = input[i];
        }
    }
    out1[out1d_index] = '\0';
    out2[out2d_index] = '\0';
}; 

// 0 is invalid, 1 is two nums, 2 is num and char, 3 is char and num
int getStrORNumOp(char out1[], char out2[], char opType)
{
    bool out1isNum = true;
    bool out2isNum = true;
    
    // Check if out1 is a number
    for (int i = 0; out1[i] != '\0'; i++) {
        if ((out1[i] < '0' || out1[i] > '9') && out1[i] != '-' && out1[i] != '+') {
            out1isNum = false;
            break;
        }
    }
    
    // Check if out2 is a number
    for (int i = 0; out2[i] != '\0'; i++) {
        if ((out2[i] < '0' || out2[i] > '9') && out2[i] != '-' && out2[i] != '+') {
            out2isNum = false;
            break;
        }
    }

    if (!out1isNum) {
        // check if it is char array a-z A-Z
        for (int i = 0; out1[i] != '\0'; i++) {
            if (!((out1[i] >= 'a' && out1[i] <= 'z') || (out1[i] >= 'A' && out1[i] <= 'Z'))) {
                return 0;  // invalid character found
            }
        }
    }
    
    if (!out2isNum) {
        // check if it is char array a-z A-Z
        for (int i = 0; out2[i] != '\0'; i++) {
            if (!((out2[i] >= 'a' && out2[i] <= 'z') || (out2[i] >= 'A' && out2[i] <= 'Z'))) {
                return 0;  // invalid character found
            }
        }
    }
    
    if (out1isNum && out2isNum) return 1;  // two nums
    // if it isn't two nums and optype is % then it is invalid
    if (opType == '%') return 0;
    if (out1isNum && !out2isNum) return 2;  // num and char
    if (!out1isNum && out2isNum) return 3;  // char and num
    return 0;  // invalid
}
