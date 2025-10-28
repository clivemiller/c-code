#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

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

// Validate that input contains only allowed characters
bool validateInputCharacters(char input[]) {
    for (int i = 0; input[i] != '\0'; i++) {
        char c = input[i];
        // Allow: digits, letters (a-z, A-Z), and operators (+, -, *, /, %)
        if (!((c >= '0' && c <= '9') || 
              (c >= 'a' && c <= 'z') || 
              (c >= 'A' && c <= 'Z') ||
              c == '+' || c == '-' || c == '*' || c == '/' || c == '%')) {
            return false;
        }
    }
    return true;
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

// Validate that string contains only letters a-z and A-Z
bool isValidString(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))) {
            return false;
        }
    }
    return true;
}

// Validate that string contains only digits
bool isValidNumber(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9') {
            return false;
        }
    }
    return true;
}

// Check if number string is in valid range [0, INT_MAX]
bool isNumberInRange(char str[]) {
    // Check for empty string
    if (strlen(str) == 0) return false;
    
    // Convert to long long to check range
    char* endptr;
    long long val = strtoll(str, &endptr, 10);
    
    // Check if conversion was successful and entire string was consumed
    if (*endptr != '\0') return false;
    
    // Check range: must be >= 0 and <= INT_MAX
    if (val < 0 || val > INT_MAX) {
        return false;
    }
    
    return true;
}

// 0 is invalid, 1 is two nums, 2 is num and char, 3 is char and num
int getStrORNumOp(char out1[], char out2[], char opType)
{
    bool out1isNum = isValidNumber(out1);
    bool out2isNum = isValidNumber(out2);
    
    // Check for empty operands
    if (strlen(out1) == 0 || strlen(out2) == 0) {
        printf("Error: Empty operand detected.\n");
        return 0;
    }
    
    // If both are numbers, validate range
    if (out1isNum && out2isNum) {
        if (!isNumberInRange(out1)) {
            printf("Error: First number is out of range [0, %d].\n", INT_MAX);
            return 0;
        }
        if (!isNumberInRange(out2)) {
            printf("Error: Second number is out of range [0, %d].\n", INT_MAX);
            return 0;
        }
        return 1;  // two nums
    }
    
    // If operator is %, only allow two numbers
    if (opType == '%') {
        printf("Error: Modulo operation (%%) requires two integers.\n");
        return 0;
    }
    
    // Check if both are strings (not allowed)
    if (!out1isNum && !out2isNum) {
        printf("Error: Two strings entered as operands. Only accept two integers or one integer and one string.\n");
        return 0;
    }
    
    // One is number, one is string
    if (out1isNum) {
        // out1 is number, out2 is string
        if (!isNumberInRange(out1)) {
            printf("Error: Number is out of range [0, %d].\n", INT_MAX);
            return 0;
        }
        if (strlen(out2) > 100) {
            printf("Error: String has more than 100 characters.\n");
            return 0;
        }
        if (!isValidString(out2)) {
            printf("Error: String contains invalid characters. Only a-z and A-Z allowed.\n");
            return 0;
        }
        return 2;  // num and char
    } else {
        // out1 is string, out2 is number
        if (!isNumberInRange(out2)) {
            printf("Error: Number is out of range [0, %d].\n", INT_MAX);
            return 0;
        }
        if (strlen(out1) > 100) {
            printf("Error: String has more than 100 characters.\n");
            return 0;
        }
        if (!isValidString(out1)) {
            printf("Error: String contains invalid characters. Only a-z and A-Z allowed.\n");
            return 0;
        }
        return 3;  // char and num
    }
}
