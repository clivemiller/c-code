#include <stdio.h>
#include <string.h>
#include "./overFlowChecker.h"
#include "./main.h"

bool multNum(int Num1, int Num2, int* ans) 
{
    if (!isValidMultOp(Num1, Num2)) return false;
    *ans = Num1*Num2;
    return true;
};


void multModString(int Num, int len, char InputString[], char multCharOutput[]) 
{
    multCharOutput[0] = '\0';  // Initialize empty string
    
    for (int i = 0; i < Num; i++) {
        // Check if adding another copy would exceed 1024 characters
        if (strlen(multCharOutput) + len > 1024) {
            // Only add as much as possible to reach 1024
            int remaining = 1024 - strlen(multCharOutput);
            strncat(multCharOutput, InputString, remaining);
            printf("Warning: Result string is too long. Truncated to 1024 characters.\n");
            break;
        }
        strcat(multCharOutput, InputString);
    }
};