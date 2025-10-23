#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include "./overFlowChecker.h"

bool isValidAddOp(int Num1, int Num2) {
	if (Num2 > 0 && Num1 > INT_MAX - Num2) return false;
	if (Num2 < 0 && Num1 < INT_MIN - Num2) return false;
	return true;
};

bool isValidSubOp(int Num1, int Num2) 
{
	if (Num2 < 0 && Num1 > INT_MAX + Num2) return false;
	if (Num2 > 0 && Num1 < INT_MIN + Num2) return false;
	return true;
};

bool isValidMultOp(int Num1, int Num2) 
{
	if (Num1 == 0 || Num2 == 0) return true;
	long long prod = (long long)Num1 * (long long)Num2;
	if (prod > INT_MAX || prod < INT_MIN) return false;
	return true;
};

bool isValidDivOrModOp(int Num1, int Num2) 
{
	if (Num2 == 0) return false;
	if (Num1 == INT_MIN && Num2 == -1) return false;
	return true;
};