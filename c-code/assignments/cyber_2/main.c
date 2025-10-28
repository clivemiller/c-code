#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "./main.h"
#include "./parser.h"

void main() 
{
    bool run = true;
    while (run) {
        // Read input
        char input[113];
        readSafeInput(input);
        int len = strlen(input);

        // exit case 
        if(strcmp(input, "exit") == 0) {
            run = false;
            printf("%s\n", "Breaking out of Program...");
            break;
        }

        // Validate input characters first
        if (!validateInputCharacters(input)) {
            printf("Error: Input contains invalid characters. Only digits (0-9), letters (a-z, A-Z), and operators (+, -, *, /, %%) are allowed.\n\n");
            continue;
        }

        // get op Type
        char opType = getOperationType(input);
        if (opType == '0') {
            printf("Error: No valid operator found in input.\n\n");
            continue;
        }

        char left[101];
        char right[101];
        signed int num1;
        signed int num2;
        char charInput[101];
        bool isStrOP = false;

        parseTwoValues(input, left, right, opType);
        int operationNum = getStrORNumOp(left, right, opType);
        
        switch (operationNum) {
            case 0: 
                printf("%s\n\n", "Invalid Input! Ensure you have two numbers or a number and a string with a valid operation.");
                continue;
            case 1:
                num1 = (signed int)atoi(left); 
                num2 = (signed int)atoi(right);
                break;
            case 2:
                num1 = (signed int)atoi(left); 
                strcpy(charInput, right);
                isStrOP = true;
                break;
            case 3:
                strcpy(charInput, left); 
                num1 = (signed int)atoi(right);
                isStrOP = true;
                break;
        }

        signed int ans;
        char multCharOutput[1025];  // 1024 + null terminator
        bool errorOperating = false;
        bool isMult = false;

        switch (opType) {
            // invalid
            case '0':
                printf("%s\n", "Error getting operation type!");
                break;
            // +
            case '+':
                printf("%s\n", "Operation type: +");
                if (isStrOP) {
                    addModString(num1, strlen(charInput), charInput);
                    break;
                }
                if (!addNum(num1, num2, &ans)) {
                    errorOperating = true;
                    printf("%s\n", "Error adding numbers; integer overflow detected.");
                }
                break;
            // -
            case '-':
                printf("%s\n", "Operation type: -");
                if (isStrOP) {
                    subModString(num1, strlen(charInput), charInput);
                    break;
                }
                if (!subNum(num1, num2, &ans)) {
                    errorOperating = true;
                    printf("%s\n", "Error subtracting numbers; integer overflow/underflow detected.");
                }
                break;
            // /
            case '/':
                printf("%s\n", "Operation type: /");

                if (isStrOP) {
                    divModString(num1, strlen(charInput), charInput);
                    break;
                }
                if (!divNum(num1, num2, &ans)) {
                    errorOperating = true;
                    printf("%s\n", "Error dividing numbers; division by zero.");
                }
                break;
            // *
            case '*':
                isMult = true;
                printf("%s\n", "Operation type: *");
                if (isStrOP) {
                    multModString(num1, strlen(charInput), charInput, multCharOutput);
                    break;
                }
                if (!multNum(num1, num2, &ans)) {
                    errorOperating = true;
                    printf("%s\n", "Error multiplying numbers; integer overflow detected.");
                }
                break;
            // % 
            case '%':
                printf("%s\n", "Operation type: %");
                if (!modNum(num1, num2, &ans)) {
                    errorOperating = true;
                    printf("%s\n", "Error modding numbers; modulo by zero.");
                }
                break;
        }
        if (!errorOperating) {
            if (isStrOP) {
                if (isMult) {
                    printf("%s %s\n\n", "Output String is:", multCharOutput);
                } else {
                    printf("%s %s\n\n", "Output String is:", charInput);
                }
            } else {
                printf("%s %d\n\n", "Output Number is:", ans);
            }
        } else {
            printf("\n");
        }
    }
};