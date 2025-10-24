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
    for (int i = 0; i < Num; i++) {
        InputString[len-i] = '\0';
    }
};