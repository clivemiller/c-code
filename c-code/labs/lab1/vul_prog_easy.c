/* vul_prog.c */

#include<stdio.h>
#include<stdlib.h>


int main(int argc, char *argv[])
{
    char user_input[100];
    int secret[2];
    int a = 0x111; //variable not used
    int b = 0x222; //variable not used
    int int_input[2];
    int c = 0x333; //variable not used
    int d = 0x444; //variable not used
       

    secret[0] = 0x43; //'C'
    secret[1] = 0x53; //'S'
    
    printf("user_input's address is 0x%llx (on stack)\n", &user_input);
    printf("The array secret's address is 0x%llx (on stack)\n", &secret);
    printf("secret[0]'s address is 0x%llx (on stack)\n", &secret[0]);
    printf("secret[1]'s address is 0x%llx (on stack)\n", &secret[1]);
    printf("variable a is located at 0x%llx (on stack)\n",&a);
    printf("variable b is located at 0x%llx (on stack)\n",&b);
    printf("The variable int_input1's address is 0x%llx (on stack)\n", &int_input[0]);
    printf("The variable int_input2's address is 0x%llx (on stack)\n", &int_input[1]);
    printf("variable c is located at 0x%llx (on stack)\n",&c);
    printf("variable d is located at 0x%llx (on stack)\n",&d);

    
    // decimal integer needed, be careful, not in hex
    printf("\nPlease enter a decimal integer\n");
    scanf("%d", &int_input[0]);  /* getting an input1 from user */
    printf("Please enter a decimal integer for integer2\n");
    scanf("%d", &int_input[1]);  /* getting an input2 from user */
    printf("Please enter a string\n");
    scanf("%s", user_input); /* getting a string from user */
    
    /* Vulnerable place */
    printf(user_input); 
    printf("\n");

    return 0;
}

// TO make it segfault, it is easy, just enter %s on the decimal integer input request. 
// To extract the letter "d" per task 3, we just spammed %llx format strings into the input to get all the spare values from the stack
