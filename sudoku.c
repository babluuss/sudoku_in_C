
/*
    Description: A simple Sudoku game that allows users to generate and play Sudoku puzzles.
    Author:
    License:
    
    Inspiration:
*/

// Libraries and neccesary includes
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>
#include <conio.h>
#include <windows.h>

// defined size
# define SIZE 9

#define ENTER 13
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

// Prototipe of functions
int isSafe(int grid[SIZE][SIZE], int row, int col, int num);
int fillGrid(int grid[SIZE][SIZE]);
void removeCells(int grid[SIZE][SIZE], int difficulty);

void generateSudoku(int difficulty, int (*board)[SIZE]);
void printGrid(int grid[SIZE][SIZE]);

int chooseDifficulty();

void playGame(int board[SIZE][SIZE]);

// Main
int main(){
    srand(time(0));

    int board[SIZE][SIZE];
    
    // Choose difficulty 
    int difficulty = chooseDifficulty();

    generateSudoku(difficulty, board);

    playGame(board);

    return 0;
}

int chooseDifficulty() {
    int keyPressed, diff = 0; // 0: Easy, 1: Medium, 2: Hard

    system("cls");

    printf("Choose a difficulty:\n");
    printf("\t\tEasy\n");
    printf("\t\tMedium\n");
    printf("\t\tHard\n");

    while ((keyPressed = getch()) != ENTER) {
        if (keyPressed == 0 || keyPressed == 224) {
            keyPressed = getch(); // Get the actual key pressed
            switch (keyPressed) {
            case UP:
                diff = (diff - 1 + 3) % 3; // Move up in the selection
                break;
            case DOWN:
                diff = (diff + 1) % 3; // Move down in the selection
                break;
            }
            system("cls");
            printf("Choose a difficulty:\n");
            printf("%s\tEasy\n", (diff == 0) ? "->" : "\t");
            printf("%s\tMedium\n", (diff == 1) ? "->" : "\t");
            printf("%s\tHard\n", (diff == 2) ? "->" : "\t");
        }
    }

    return diff + 1;
}

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

int fillGrid(int grid[SIZE][SIZE]) {
    // Recursively fills the grid with a valid Sudoku solution.

    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (grid[row][col] == 0) {
                for (int num = 1; num <= SIZE; num++) {
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
        if(i % 3 == 0 && i != 0) 
            printf("--------- --------- ---------\n");
        for (int j = 0; j < SIZE; j++){
            if(j % 3 == 0 && j != 0) 
                printf("|");
            printf(" %d ", grid[i][j]);
        }
        printf("\n");
    }
}

void playGame(int board[SIZE][SIZE]) {
    int selectedRow = 0, selectedCol = 0;
    int keyPressed;

    while (1) {
        system("cls");
        printGrid(board);
        printf("\nUse arrow keys to move, numbers to fill cells, and 'q' to quit.\n");

        keyPressed = getch();
        if (keyPressed == 'q') {
            break; // Exit the game
        } else if (keyPressed == 0 || keyPressed == 224) {
            keyPressed = getch(); // Get actual key pressed
            switch (keyPressed) {
                case UP:
                    selectedRow = (selectedRow - 1 + SIZE) % SIZE; // Move up
                    break;
                case DOWN:
                    selectedRow = (selectedRow + 1) % SIZE; // Move down
                    break;
                case LEFT:
                    selectedCol = (selectedCol - 1 + SIZE) % SIZE; // Move left
                    break;
                case RIGHT:
                    selectedCol = (selectedCol + 1) % SIZE; // Move right
                    break;
            }
        } else if (keyPressed >= '1' && keyPressed <= '9') {
            if (isSafe(board, selectedRow, selectedCol, keyPressed - '0')) {
                board[selectedRow][selectedCol] = keyPressed - '0'; // Fill cell
            } else {
                printf("Invalid move!\n");
                getch(); // Wait for user to acknowledge
            }
        }
    }
}