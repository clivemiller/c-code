#include <stdio.h>

char *my_strstr(const char *haystack, const char *needle) {
    if (!*needle) {
        return (char *)haystack;
    }

    while (*haystack) {
        const char *h = haystack;
        const char *n = needle;
        
        // Compare each char of haystack and needle
        // if they match, continue checking the next chars
        while (*h && *n && *h == *n) {
            h++;
            n++;
        }

        // If we have reached the end of needle, it means we found a match
        if (!*n) {
            return (char *)haystack;
        }
        
        // Move to the next char in haystack and repeat
        haystack++;
    }
    
    return NULL;
}

int main() {
    const char *haystack = "This is a test string.";
    const char *needle = "test";
    char *result = my_strstr(haystack, needle);
    
    if (result) {
        printf("Found needle at: %s\n", result);
    } else {
        printf("Needle not found\n");
    }
    
    return 0;
}
