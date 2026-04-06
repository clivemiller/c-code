#include <stdio.h>
#include <stdlib.h>

// Programming Log
// 11 | 3 | 2025 - read assignment, copied prototype and main into file, wrote some parsing logic in makearg
// 11 | 4 | 2025 - realized addition information on the size of each token was needed, wrote more parsing logic, broke it out into separate functions
// 11 | 5 | 2025 - did some googling on pointers, figured out how to allocate and access the memory properly, wrote the debug function and the rest of makeargs

int getArgCount(char s[]) {
    int arg_count = 0;
    int in_word = 0;  // Track if we're currently inside a word

    // Count words, not spaces
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == ' ' || s[i] == '\t' || s[i] == '\n') {
            in_word = 0;  // We're now in whitespace
        } else {
            if (in_word == 0) {
                // We just started a new word
                arg_count++;
                in_word = 1;
            }
        }
    }

    return arg_count;
}

void getEachArgSize(int arg_sizes[], char s[]) {
    int arg_index = 0;
    int size_counter = 0;
    int in_word = 0;
    
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == ' ' || s[i] == '\t' || s[i] == '\n') {
            if (in_word) {
                // End of a word, store its size
                arg_sizes[arg_index] = size_counter;
                arg_index++;
                size_counter = 0;
                in_word = 0;
            }
        } else {
            // Character is part of a word
            size_counter++;
            in_word = 1;
        }
    }
    // Store the size of the last word if we ended in one
    if (in_word) {
        arg_sizes[arg_index] = size_counter;
    }
}

int makearg(char s[], char **args[]) {  
    int arg_count = getArgCount(s);
    int num_args = arg_count;

    // Determine the size of each argument
    int arg_sizes[arg_count];
    getEachArgSize(arg_sizes, s);

    // Allocate array of char pointers (with room for NULL at the end)
    *args = (char **)malloc((arg_count + 1) * sizeof(char *));
    
    // Allocate memory for each individual token/string
    for (int i = 0; i < arg_count; i++) {
        (*args)[i] = (char *)malloc((arg_sizes[i] + 1) * sizeof(char));  // +1 for null terminator
    }
    
    // Reset the index and count vars for our use 
    // char_pos will index chars to correct positions
    int counter = 0;
    int arg_index = 0;
    int char_pos = 0;
    int in_word = 0;
    
    // loop through and set each token
    while (s[counter] != '\0') {
        if (s[counter] == ' ' || s[counter] == '\n') {
            if (in_word) {
                // End of word - null terminate it
                (*args)[arg_index][char_pos] = '\0';
                arg_index++;
                char_pos = 0;
                in_word = 0;
            }
        } else {
            // Copy character to current word
            (*args)[arg_index][char_pos] = s[counter];
            char_pos++;
            in_word = 1;
        }
        counter++;
    }
    // Null terminate the last word if we ended in one
    if (in_word) {
        (*args)[arg_index][char_pos] = '\0';
    }
    // Add NULL pointer at the end of the array
    (*args)[arg_count] = NULL;

    return num_args;
}

// print_args is a dubugging function so I can print what we make
void print_args(char **args, int argc) {
    printf("\n=== Debug: Final Args Array ===\n");
    printf("argc = %d\n", argc);
    for (int i = 0; i < argc; i++) {
        printf("args[%d] = \"%s\"\n", i, args[i]);
    }
    printf("args[%d] = %p (NULL)\n", argc, (void *)args[argc]);
    printf("===============================\n\n");
}

void main() {
    char **args, str[] = "ls -l file";
    int argc;
    argc = makearg(str, &args);
    
    // Debug print the final array
    print_args(args, argc);
}

