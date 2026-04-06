#include <stdio.h>

#define COLS 4 

void spiral_traversal(int matrix[][COLS], int rows, int cols) {
    while (rows > 0 && cols > 0) {
        // Traverse the top row
        for (int i = 0; i < cols; i++) {
            printf("%d ", matrix[0][i]);
        }
        // Shift the matrix up
        for (int i = 1; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                matrix[i - 1][j] = matrix[i][j];
            }
        }
        rows--;

        if (rows == 0) break;

        // Traverse the rightmost column
        for (int i = 0; i < rows; i++) {
            printf("%d ", matrix[i][cols - 1]);
        }
        cols--;

        if (cols == 0) break;

        // Traverse the bottom row
        for (int i = cols - 1; i >= 0; i--) {
            printf("%d ", matrix[rows - 1][i]);
        }
        rows--;

        if (rows == 0) break;

        // Traverse the leftmost column
        for (int i = rows - 1; i >= 0; i--) {
            printf("%d ", matrix[i][0]);
        }
        cols--;
    }
}

int main() {
  int matrix[][COLS] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
  };
  int rows = 4;
  int cols = COLS;

  spiral_traversal(matrix, rows, cols); 
  // Output: 1 2 3 4 8 12 16 15 14 13 9 5 6 7 11 10

  return 0;
}