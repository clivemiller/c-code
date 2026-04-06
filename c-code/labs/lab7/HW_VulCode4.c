#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

void get_date(short d);

int main() {
	printf("The following program performs several activities related to the singer Sinatra.\n");

	//1.Uninitialized variable, called "age"
	int age = 10;  
	printf("Frank Sinatra's age is: %d\n", age);

	//2.Buffer overflow+unsafe function, in first_name if input is longer than 5
	char first_name[5];
	char input[] = "Frankie";
	char full_name[] = "Sinatra"; //Full name will be "Frank Sinatra"
	strcpy(first_name, "Frankie");

	printf("Mr. Sinatra's first name is: %s\n", first_name);  

	//3.strcat() does not check the final length of the string and overflows full_name's bounds
	//in addition to buffer overflow, strcpy is an unsafe function

	strcat(input, full_name); //input makes the concatenated string too long    	 

	//4.type mistmatch, from int to short in get_date
	int year_born = 1915;
	get_date(year_born);

	//5.format string vulnerability
	char last_concert[10] = "%x/%x/1994";
	printf(last_concert);

	//6.integer overflow, going beyond MAX_INT of 2147483647
	int tickets_sold = 2147483646;
	tickets_sold = tickets_sold + 100;
	printf("Over Sinatra's career, he's sold a lot of tickets...and he just sold 100 more. Total sold = %d\n", tickets_sold);
	
	printf("Sinatra's three top songs are: \n");
	char *songs[] = {"Strangers in the Night", "Somethin' Stupid", "Three Coins in the Fountain"};
	int i = 0;
	for (i = 0; i < 3; i++) { //should be 3, not 4  
			printf("%d. %s\n", i, songs[i]);
	}

	int *arr2 = (int *)malloc(sizeof(int));
		*arr2 = 0; 
		
	free(arr2);

	int ptr = 0;
	int val = 10;
	ptr = val;
	printf("Frank Sinatra has %d awards.\n", ptr);

	int *arr = (int *)malloc(4 * sizeof(int));
	int j = 0;

	for (j = 1; j <=3; j++) {
			arr[j] = j;
	}



	printf("All done, program will exit in...\n");
	for (j = 3; j >= 1; j--) {
			sleep(1);
			printf("%d\n", arr[j]);
	}
	free(arr);

	return 0;
}

void get_date(short d) {
	printf("He was born in %d \n", d);
}
