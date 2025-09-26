#include <stdio.h>
#include <string.h>

char * strncpy(char *dest, const char *src, size_t n)
{
    size_t i;

    for (i = 0; i < n && src[i] != '\0'; i++)
        dest[i] = src[i];
    for ( ; i < n; i++)
        dest[i] = '\0';
    return dest;
}

int main() 
{
    char buf[11] = "ten chars in"; // buf 11 size with ten chars and null terminator
    char test[1] = "1"; 
    strcat(buf, test); // overwrite the null terminator
    char replace[11] = "hello there";

    strncpy(buf, replace, 11); // attempt to copy -> cuases core dump

    printf("%s\n", buf);
}