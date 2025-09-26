#include <iostream>
#include <stdio.h>
using namespace std;

// Strict integer parsing function
static bool parse_int_strict(const char* s, int& out)
{
    if (!s) return false;
    int i = 0;
    // Skip leading spaces/tabs
    while (s[i] == ' ' || s[i] == '\t') i++;

    int sign = 1;
    if (s[i] == '+' || s[i] == '-') {
        if (s[i] == '-') sign = -1;
        i++;
    }

    // Require at least one digit
    if (s[i] < '0' || s[i] > '9') return false;

    long val = 0;
    while (s[i] >= '0' && s[i] <= '9') {
        val = val * 10 + (s[i] - '0');
        i++;
    }

    // Skip trailing spaces/tabs and optional newline
    while (s[i] == ' ' || s[i] == '\t') i++;
    if (s[i] == '\n') i++;

    // Reject any other trailing characters
    if (s[i] != '\0') return false;

    val *= sign;
    if (val < -2147483648L || val > 2147483647L) return false;
    out = (int)val;
    return true;
}

// This program gets up to 10 scores from a students, calculates the average and final grade

int main()
{
    //------DO NOT CHANGE THESE------
    int scores[10];
    char name[100] = "abc";
    char id[12] = "";
    int number_of_score = 0;
    double average = 0;
    int sum = 0;
    char grade = 'X';
    char comments[5] = "NONE";
    //--------------------------------

    printf("\n---------------------------------------\n");
    printf("Welcome to the scoring system!\n");

    printf("Enter student's name: ");
    
    fgets(name, sizeof(name), stdin);

    printf("Extracted name: %s\n", name);

    printf("\nPlease enter student ID: ");
    fgets(id, sizeof(id), stdin);

    printf("Extracted ID: %s\n", id);

    printf("Enter up to 10 student's scores (0-100) (if done, enter -1 to stop): \n");

    for (int i = 0; i < 10; )
    {
        printf("Score %d: ", i + 1);

        char line[32];
        if (!fgets(line, sizeof(line), stdin)) {
            printf("Input error reading score.\n");
            break;
        }

        // If input didn't fit in buffer (no newline), we flush it all
        bool saw_newline = false;
        for (int j = 0; line[j] != '\0'; ++j) {
            if (line[j] == '\n') { saw_newline = true; break; }
        }
        if (!saw_newline) {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) { }
        }

        int parsed = 0;
        if (!parse_int_strict(line, parsed)) {
            printf("Please enter an integer between 0 and 100, or -1 to stop.\n");
            continue;
        }
        if (parsed == -1) {
            break;
        }
        if (parsed < 0 || parsed > 100) {
            printf("Score must be between 0 and 100. Please try again.\n");
            continue;
        }

        scores[i] = parsed;
        printf("Extracted score: %d\n", scores[i]);
        sum += scores[i];
        number_of_score++;
        i++;
    }

    if (number_of_score > 0) {
        average = (double)sum / (double)number_of_score;
    } else {
        average = 0.0;
    }
    printf("Student's name is: %s\n", name);
    printf("Student has %d scores, sum is %d, and the average score is %.2f\n", number_of_score, sum, average);

    // figure out the final grade, A, B, C, D, or F
    if( average >= 90)
        grade = 'A';
    if(average < 90 and average >= 80)
        grade = 'B';
    if (average < 80 and average >= 70)
        grade = 'C';
    if (average < 70 and average >= 60)
        grade = 'D';
    if (average < 60 and average >= 0)
        grade = 'F';

    printf("Based on the average score, final grade is: %c\n", grade);
    printf("Looks good? (Yes or No): ");

    fgets(comments, sizeof(comments), stdin);

    printf("Comments - Looks good? - %s\n\n", comments);
    printf("Student name: %s\n", name);
    printf("Student ID: %s\n", id);
    printf("Final grade is: %c\n\n", grade);
    printf("Program exits successfully...\n");
}
