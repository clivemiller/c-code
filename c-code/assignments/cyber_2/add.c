#include <stdio.h>
#include "./overFlowChecker.h"
#include "./main.h"

bool addNum(int Num1, int Num2, int* ans) 
{
    if (!isValidAddOp(Num1, Num2)) return false;
    *ans = Num1+Num2;
    return true;
};

void addModString(int Num, int len, char InputString[]) 
{
    // Shift each letter right by Num positions in the alphabet
    int shift = Num % 26;  // Only need to shift by remainder when divided by 26
    
    for (int i = 0; i < len; i++) 
    {
        if (InputString[i] >= 'a' && InputString[i] <= 'z') {
            // Lowercase letter
            InputString[i] = 'a' + (InputString[i] - 'a' + shift) % 26;
        } else if (InputString[i] >= 'A' && InputString[i] <= 'Z') {
            // Uppercase letter
            InputString[i] = 'A' + (InputString[i] - 'A' + shift) % 26;
        }
    }
};