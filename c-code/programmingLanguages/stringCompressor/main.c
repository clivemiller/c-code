#include <stdio.h>

// find the missing number in the array
int find_missing_number(int* nums, int n) {
    int expectedSum = 0;
    int realSum = 0;

    // Calculate the expected sum of numbers from 0 to n
    for (int i = 0; i <= n; i++) {
        expectedSum += i;
    }
    // Calculate the actual sum of the numbers in the array
    for (int i = 0; i < n; i++) {
        realSum += nums[i];
    }

    return expectedSum - realSum;
}

int main() {
    int nums[] = {3, 0, 1};
    int n = sizeof(nums) / sizeof(int); 
    int missing = find_missing_number(nums, n);
    printf("The missing number is: %d\n", missing); // Output: 2
    return 0;
}