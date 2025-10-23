#include <stdio.h>
#include "./overFlowChecker.h"
#include "./main.h"

bool multNum(int Num1, int Num2, int* ans) 
{
    if (!isValidMultOp(Num1, Num2)) return false;
    *ans = Num1*Num2;
    return true;
};


void multModString(int Num, int len, char InputString[]) 
{

};