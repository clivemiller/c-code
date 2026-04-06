#include <stdio.h>

int main(int argc, char * argv[], char * envp[]) {
    int i;
    
    for (i=0; envp[i]; i++) {
        printf("%s\n", envp[i]);
    }
    
    return 0;
}

// include stdlib.h
// char *getenv(const char *name)