/* vul_prog.c */

#include<stdio.h>
#include<stdlib.h>

#define SECRET1 0x45  //'E'
#define SECRET2 0x56  //'V'



int main(int argc, char *argv[])
{
    char user_input[100];
    int a = 0x111; /* other variables, not used here.*/
    int b = 0x222; /* other variables, not used here.*/
    long long int int_input[2];
    int c = 0x333; /* other variables, not used here.*/
    int d = 0x444; /* other variables, not used here.*/
    
    /* The secret value is stored on the heap */
    
    int *secret_heap;
    secret_heap = (int *) malloc(2*sizeof(int));
    secret_heap[0] = SECRET1; 
    secret_heap[1] = SECRET2;
    
    printf("user_input's address is 0x%llx (on stack)\n", &user_input);
    printf("variable a is located at 0x%llx (on stack)\n",&a);
    printf("variable b is located at 0x%llx (on stack)\n",&b);
    printf("The variable int_input1's address is 0x%llx (on stack)\n", &int_input[0]);
    printf("The variable int_input2's address is 0x%llx (on stack)\n", &int_input[1]);
    printf("variable c is located at 0x%llx (on stack)\n",&c);
    printf("variable d is located at 0x%llx (on stack)\n",&d);
    printf("The pointer secret_heap is located at 0x%llx (on stack)\n", &secret_heap);
    printf("The pointer secret_heap has value: 0x%llx (on stack)\n", secret_heap);
    printf("The newly allocated memory secret_heap[0] (pointed by *secret_heap is located at 0x%llx (on heap)\n", &secret_heap[0]);
    printf("The newly allocated memory secret_heap[1] (pointed by *secret_heap is located at 0x%llx (on heap)\n", &secret_heap[1]);
    
    
    printf("Please enter a decimal integer\n");
    scanf("%lld", &int_input[0]);  /* getting an input1 from user */
    printf("Please enter a decimal integer for integer2\n");
    scanf("%lld", &int_input[1]);  /* getting an input2 from user */
    printf("The 2 inputs are: %lld (0x%llx) and %lld (0x%llx). \n", int_input[0], int_input[0], int_input[1], int_input[1]);
    printf("Please enter a string\n");
    scanf("%s", user_input); /* getting a string from user */
    
    /* Vulnerable place */
    printf(user_input);
    printf("\n");

    return 0;
}
