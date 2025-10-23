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
    for (int i = 0; i < Num; i++) 
    {
        // Save the last character
        char last = InputString[len - 1];
        
        // Shift chars one to the right
        for (int j = len - 1; j > 0; j--)
        {
            InputString[j] = InputString[j - 1];
        }
        
        // Put the last character at the front
        InputString[0] = last;
    }
};