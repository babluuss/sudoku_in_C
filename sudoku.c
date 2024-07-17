
/*
    Description:
    Author:
    License:
    
    Inspiration:
*/

// Libraries and neccesary includes
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

// defined size
# define SIZE 9

// Prototipe of functions
int isSafe(int grid[SIZE][SIZE], int row, int col, int num);
int fillGrid(int grid[SIZE][SIZE]);
void removeCells(int grid[SIZE][SIZE], int difficulty);

// Main
int main(){
    srand(time(0));

    int board[SIZE][SIZE];
    int difficulty = 2; // Medium difficulty

    generateSudoku(difficulty, board);
    printGrid(board);

    return 0;
}

// Functions
void generateSudoku(int difficulty, int (*board)[SIZE]) {
    // The main function that initializes the grid, fills it, and then removes cells to create the puzzle.

    // Initialize grid
    int grid[SIZE][SIZE] = {0};

    // Fill the grid with a valid Sudoku solution
    fillGrid(grid);

    // Remove cells based on difficulty
    removeCells(grid, difficulty);

    // Copy the grid to the board
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = grid[i][j];
        }
    }
}

int isSafe(int grid[SIZE][SIZE], int row, int col, int num) {
    // Checks if placing a number in a specific cell is valid according to Sudoku rules.

    for (int x = 0; x < SIZE; x++) {
        if (grid[row][x] == num || grid[x][col] == num ||
            grid[row - row % 3 + x / 3][col - col % 3 + x % 3] == num) {
            return 0;
        }
    }
    return 1;
}

int fillGrid(int grid[SIZE][SIZE]) {
    // Recursively fills the grid with a valid Sudoku solution.

    int row, col, num;
    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            if (grid[row][col] == 0) {
                for (num = 1; num <= SIZE; num++) {
                    if (isSafe(grid, row, col, num)) {
                        grid[row][col] = num;
                        if (fillGrid(grid)) {
                            return 1;
                        }
                        grid[row][col] = 0;
                    }
                }
                return 0;
            }
        }
    }
    return 1;
}

void removeCells(int grid[SIZE][SIZE], int difficulty) {
    // Removes cells from the grid based on the chosen difficulty level (easy, medium, or hard).

    int cellsToRemove;

    switch (difficulty) {
        case 1:
            cellsToRemove = 20; // Easy
            break;
        case 2:
            cellsToRemove = 40; // Medium
            break;
        case 3:
            cellsToRemove = 60; // Hard
            break;
        default:
            cellsToRemove = 20; // Default to easy
    }

    while (cellsToRemove > 0) {
        int cellId = rand() % (SIZE * SIZE);
        int row = cellId / SIZE;
        int col = cellId % SIZE;
        if (grid[row][col] != 0) {
            grid[row][col] = 0;
            cellsToRemove--;
        }
    }
}

void printGrid(int grid[SIZE][SIZE]) {
    // Helper function to print the generated Sudoku grid.


    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%2d", grid[i][j]);
        }
        printf("\n");
    }
}