#include <stdio.h>
#include "./overFlowChecker.h"
#include "./main.h"

bool divNum(int Num1, int Num2, int* ans) 
{
    if (!isValidDivOrModOp(Num1, Num2)) return false;
    *ans = Num1/Num2;
    return true;
};

bool modNum(int Num1, int Num2, int* ans) 
{
    if (!isValidDivOrModOp(Num1, Num2)) return false;
    *ans = Num1%Num2;
    return true;
};

void divModString(int Num, int len, char InputString[]) 
{
    // Cut string from the end by Num characters
    if (Num >= len) {
        // If Num is larger than or equal to string length, result is empty string
        InputString[0] = '\0';
    } else {
        // Terminate the string at the new length
        InputString[len - Num] = '\0';
    }
};