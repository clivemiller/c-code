#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 256

int main() {
    int pipe_parent_to_child[2];  // Parent writes, child reads
    int pipe_child_to_parent[2];  // Child writes, parent reads
    pid_t pid;
    char buffer[BUFFER_SIZE];

    // Create both pipes
    if (pipe(pipe_parent_to_child) == -1 || pipe(pipe_child_to_parent) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        close(pipe_parent_to_child[1]);  // Close write end of parent->child
        close(pipe_child_to_parent[0]);  // Close read end of child->parent

        // Read message from parent
        ssize_t bytes = read(pipe_parent_to_child[0], buffer, BUFFER_SIZE);
        if (bytes > 0) {
            buffer[bytes] = '\0';
            printf("Child received: \"%s\"\n", buffer);
        }

        // Send response back to parent
        char response[] = "Hello back from child!";
        write(pipe_child_to_parent[1], response, strlen(response));
        printf("Child sent response.\n");

        close(pipe_parent_to_child[0]);
        close(pipe_child_to_parent[1]);
        exit(EXIT_SUCCESS);

    } else {
        // Parent process
        close(pipe_parent_to_child[0]);  // Close read end of parent->child
        close(pipe_child_to_parent[1]);  // Close write end of child->parent

        // Send message to child
        char message[] = "Hello from parent!";
        write(pipe_parent_to_child[1], message, strlen(message));
        printf("Parent sent: \"%s\"\n", message);

        // Read response from child
        ssize_t bytes = read(pipe_child_to_parent[0], buffer, BUFFER_SIZE);
        if (bytes > 0) {
            buffer[bytes] = '\0';
            printf("Parent received: \"%s\"\n", buffer);
        }

        close(pipe_parent_to_child[1]);
        close(pipe_child_to_parent[0]);

        wait(NULL);
        printf("Communication complete.\n");
    }

    return 0;
}
