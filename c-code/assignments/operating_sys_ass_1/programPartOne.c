#include <stdio.h>
#include <sys/types.h> // for pid_t
#include <unistd.h> // for sleep and getpid()

int main(int argc, char *argv[]) {
    pid_t pid; // Declare a variable of type pid_t to store the PID
    pid = getpid(); // Call getpid() to get the current process's PID
    int count = 0; // counter

    while (1) {
        // fprintf (printf to file) is printing to stderr the argv[0] (exe name), the pid (getpid()), and the count (which is then iterated)
        fprintf(stderr, "My Program Name: %s | PID: %d | Loop Iteration: %d\n", argv[0], getpid(), count++);
        sleep(1);
    }

    return 0;
}
