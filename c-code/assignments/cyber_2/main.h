#include <stdio.h>
#include <stdbool.h>

bool addNum(signed int Num1, signed int Num2, signed int *ans);
void addModString(int Num, int len, char InputString[]);

bool subNum(signed int Num1, signed int Num2, signed int* ans);
void subModString(int Num, int len, char InputString[]);

bool multNum(signed int Num1, signed int Num2, signed int* ans);
void multModString(int Num, int len, char InputString[], char multCharOutput[]);

bool divNum(signed int Num1, signed int Num2, signed int* ans);
bool modNum(signed int Num1, signed int Num2, signed int* ans);
void divModString(int Num, int len, char InputString[]);

