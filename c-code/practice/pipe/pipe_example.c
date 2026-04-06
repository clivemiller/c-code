#include <stdio.h>
#include <unistd.h>

int main() {
    int fd[2];
    char buf[32];

    pipe(fd);

    if (fork() == 0) {
        // Child: read from pipe
        read(fd[0], buf, sizeof(buf));
        printf("Child got: %s\n", buf);
    } else {
        // Parent: write to pipe
        write(fd[1], "Hello!", 7);
    }

    return 0;
}
