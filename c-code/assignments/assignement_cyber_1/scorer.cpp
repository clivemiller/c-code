#include <iostream>
#include <stdio.h>
#include <cctype>
#include <cstring>
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

// Flush remaining characters in stdin until newline or EOF
static void flush_stdin()
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) { }
}

// Trim trailing newline and carriage return characters from a string
// we get /n from fgets, and possibly /r from Windows, had some issues with that on my Windows machine
static void trim_newline(char* s)
{
    if (!s) return;
    size_t len = strlen(s);
    // Remove trailing \n and \r by replacing them with null terminator
    while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r')) {
        s[len - 1] = '\0';
        len--;
    }
}

// Validate student ID format: 3 letters, hyphen, 5 digits (e.g., ABC-12345)
static bool is_valid_student_id(const char* s)
{
    // Length must be exactly 9
    if (!s) return false;
    if (strlen(s) != 9) return false;

    // Check first 3 characters are letters
    for (int i = 0; i < 3; ++i) {
        if (!isalpha(static_cast<unsigned char>(s[i]))) {
            return false;
        }
    }

    // Check 4th character is hyphen
    if (s[3] != '-') {
        return false;
    }

    // Check last 5 characters are digits
    for (int i = 4; i < 9; ++i) {
        if (!isdigit(static_cast<unsigned char>(s[i]))) {
            return false;
        }
    }

    return true;
}

// Case-insensitive string comparison
static bool equals_ignore_case(const char* a, const char* b)
{
    // Handle null pointers
    if (!a || !b) return false;

    size_t i = 0;
    // Compare characters case-insensitively
    for (; a[i] != '\0' && b[i] != '\0'; ++i) {
        // Cast chars to unsigned chars to avoid undefined behavior with negative char values
        // Convert both characters to uppercase for comparison
        if (toupper(static_cast<unsigned char>(a[i])) != toupper(static_cast<unsigned char>(b[i]))) {
            return false;
        }
    }

    // Both strings must end at the same time
    return a[i] == '\0' && b[i] == '\0';
}

// Check if comment response is valid (YES, NO, Y, N)
static bool is_valid_comment_response(const char* s)
{
    if (!s) return false;

    return equals_ignore_case(s, "YES") || equals_ignore_case(s, "NO") ||
           equals_ignore_case(s, "Y") || equals_ignore_case(s, "N");
}

// Normalize comment to "Y" or "N"
static void normalize_comment(char* s)
{
    if (!s) return;

    if (equals_ignore_case(s, "Y")) {
        s[0] = 'Y';
        s[1] = '\0';
        return;
    }
    if (equals_ignore_case(s, "N")) {
        s[0] = 'N';
        s[1] = '\0';
        return;
    }

    for (size_t i = 0; s[i] != '\0'; ++i) {
        s[i] = static_cast<char>(toupper(static_cast<unsigned char>(s[i])));
    }
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

    // Read name input
    if (!fgets(name, sizeof(name), stdin)) {
        printf("Input error reading name.\n");
        return 1;
    }
    // Check for newline character, if not present, flush stdin
    if (!strchr(name, '\n')) {
        flush_stdin();
    }

    // Trim trailing newline and carriage return characters
    trim_newline(name);

    printf("Extracted name: %s\n", name);

    // Read and validate student ID
    while (true) {
        printf("\nPlease enter student ID (format ABC-12345): ");
        // Read ID input
        if (!fgets(id, sizeof(id), stdin)) {
            printf("Input error reading student ID. Please try again.\n");
            continue;
        }

        // Check for newline character, if not present, flush stdin
        if (!strchr(id, '\n')) {
            flush_stdin();
        }
        // Trim trailing newline and carriage return characters
        trim_newline(id);

        // Validate ID format
        if (!is_valid_student_id(id)) {
            printf("Invalid student ID. Use 3 letters, a hyphen, and 5 digits (example: ABC-12345).\n");
            continue;
        }

        break;
    }

    printf("ID: %s\n", id);

    printf("Enter up to 10 student's scores (0-100) (if done, enter -1 to stop): \n");

    for (int i = 0; i < 10; )
    {
        printf("Score %d: ", i + 1);

        char line[32];
        // Read score input
        if (!fgets(line, sizeof(line), stdin)) {
            printf("Input error reading score.\n");
            flush_stdin();  
            break;
        }
        // Check for newline character, if not present, flush stdin
        if (!strchr(line, '\n')) {
            flush_stdin();
        }

        int parsed = 0;
        // Strictly parse the input as an integer
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

    while (true) {
        printf("Looks good? Enter YES, NO, Y, or N: ");
        if (!fgets(comments, sizeof(comments), stdin)) {
            printf("Input error reading response. Please try again.\n");
            continue;
        }
        if (!strchr(comments, '\n')) {
            flush_stdin();
        }
        trim_newline(comments);

        if (!is_valid_comment_response(comments)) {
            printf("Please respond with YES, NO, Y, or N.\n");
            continue;
        }

        normalize_comment(comments);
        break;
    }

    printf("Comments - Looks good? - %s\n\n", comments);
    printf("Student name: %s\n", name);
    printf("Student ID: %s\n", id);
    printf("Final grade is: %c\n\n", grade);
    printf("Program exits successfully...\n");
}
