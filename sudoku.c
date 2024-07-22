/*
    Description: A simple Sudoku game that allows users to generate and play Sudoku puzzles.
    Author: Pinedah
    License: MIT License - Copyright (c) 2021 Hua-Ming Huang

    Inspiration: fxna
*/

// Libraries and necessary includes
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

// defined size
#define SIZE 9

#define ENTER 13
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

// Prototype of functions
int chooseDifficulty();
void generateSudoku(int difficulty, int (*board)[SIZE], int (*fixedCells)[SIZE]);
int fillGrid(int grid[SIZE][SIZE]);
int isSafe(int grid[SIZE][SIZE], int row, int col, int num);
void removeCells(int grid[SIZE][SIZE], int difficulty);
void setColor(int color);
void printGrid(int grid[SIZE][SIZE], int fixedCells[SIZE][SIZE]);
void playGame(int board[SIZE][SIZE], int fixedCells[SIZE][SIZE]);
int isBoardComplete(int board[SIZE][SIZE]);
int isValidSudoku(int board[SIZE][SIZE]);

// Main
int main(){ 
    srand(time(0)); // for random numbers

    int board[SIZE][SIZE];
    int fixedCells[SIZE][SIZE] = {0}; // Array to track fixed cells

    // Choose difficulty
    int difficulty = chooseDifficulty();

    // Generate random sudoku game based on the difficulty chosen
    generateSudoku(difficulty, board, fixedCells);

    // Start game
    playGame(board, fixedCells);

    return 0;
}

int chooseDifficulty(){
    int keyPressed, diff = 0; 

    system("cls");

    printf("Choose a difficulty:\n");
    printf("\t\tEasy\n");
    printf("\t\tMedium\n");
    printf("\t\tHard\n");

    while ((keyPressed = getch()) != ENTER){
        if (keyPressed == 0 || keyPressed == 224){ // Look for special keys
            keyPressed = getch(); // Get the actual key pressed
            switch (keyPressed){
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

void generateSudoku(int difficulty, int (*board)[SIZE], int (*fixedCells)[SIZE]){
    // The main function that initializes the grid, fills it, and then removes cells to create the puzzle.

    // Initialize grid
    int grid[SIZE][SIZE] = {0};

    // Fill the grid with a valid Sudoku solution
    fillGrid(grid);

    // Remove cells based on difficulty
    removeCells(grid, difficulty);

    // Copy the grid to the board and mark fixed cells
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            board[i][j] = grid[i][j];
            if (grid[i][j] != 0) {
                fixedCells[i][j] = 1; // Mark as a fixed cell
            }
        }
    }
}

int fillGrid(int grid[SIZE][SIZE]){
    // Recursively fills the grid with a valid Sudoku solution.

    for (int row = 0; row < SIZE; row++){
        for (int col = 0; col < SIZE; col++){
            if (grid[row][col] == 0){
                for (int num = 1; num <= SIZE; num++){
                    if (isSafe(grid, row, col, num)){
                        grid[row][col] = num;
                        if (fillGrid(grid))
                            return 1;
                        grid[row][col] = 0;
                    }
                }
                return 0;
            }
        }
    }
    return 1;
}

int isSafe(int grid[SIZE][SIZE], int row, int col, int num){
    // Checks if placing a number in a specific cell is valid according to Sudoku rules.

    for (int x = 0; x < SIZE; x++){
        if (grid[row][x] == num || grid[x][col] == num ||
            grid[row - row % 3 + x / 3][col - col % 3 + x % 3] == num)
            return 0;
    }
    return 1;
}

void removeCells(int grid[SIZE][SIZE], int difficulty){
    // Removes cells from the grid based on the chosen difficulty level (easy, medium, or hard).

    int cellsToRemove;

    switch (difficulty){
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

    while (cellsToRemove > 0){
        int cellId = rand() % (SIZE * SIZE);
        int row = cellId / SIZE;
        int col = cellId % SIZE;
        if (grid[row][col] != 0){
            grid[row][col] = 0;
            cellsToRemove--;
        }
    }
}

void setColor(int color){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void printGrid(int grid[SIZE][SIZE], int fixedCells[SIZE][SIZE]){
    // Helper function to print the generated Sudoku grid.
    printf("\n");

    for (int i = 0; i < SIZE; i++){
        if (i % 3 == 0 && i != 0)
            printf("--------- --------- ---------\n");
        for (int j = 0; j < SIZE; j++){
            if (j % 3 == 0 && j != 0)
                printf("|");

            // Print numbers: non-zero in green, zero in default color
            if (grid[i][j] != 0){
                if (fixedCells[i][j])
                    setColor(10); // Set color to green for fixed cells
                else
                    setColor(12); // Set color to red for user inputs
                
                printf(" %d ", grid[i][j]);
                setColor(7); // Reset to default color
            }else
                printf(" 0 "); // Default color for 0
            
        }
        printf("\n");
    }
}

void printGridForSelection(int grid[SIZE][SIZE], int fixedCells[SIZE][SIZE], int userRow, int userCol)
{
    // Helper function to print the generated Sudoku grid with selection highlighting.
    system("cls");
    printf("\n");

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Get the console output handle

    for (int i = 0; i < SIZE; i++)
    {
        if (i % 3 == 0 && i != 0)
            printf("------------ ------------ ------------\n");
        for (int j = 0; j < SIZE; j++)
        {
            if (j % 3 == 0 && j != 0)
                printf("|");
            if (i == userRow && j == userCol)
            {
                SetConsoleTextAttribute(hConsole, 9);
                printf(" * ");
            }
            else
            {
                // Print numbers: non-zero in green or red, zero in default color
                if (grid[i][j] != 0)
                {
                    if (fixedCells[i][j])
                        setColor(10); // Set color to green for fixed cells
                    else
                        setColor(12); // Set color to red for user inputs
                    printf(" %d ", grid[i][j]);
                    setColor(7); // Reset to default color
                }
                else
                {
                    printf(" 0 "); // Default color for 0
                }
            }
            SetConsoleTextAttribute(hConsole, 0x07);
            printf(" ");
        }
        printf("\n");
    }
}

void playGame(int board[SIZE][SIZE], int fixedCells[SIZE][SIZE])
{
    int selectedRow = 0, selectedCol = 0, userRow = 0, userCol = 0;

    char keyPressed;

    while (1)
    {
        system("cls");
        printGridForSelection(board, fixedCells, userRow, userCol);

        printf("\nUse arrow keys to move, numbers to fill cells, and 'q' to quit.\n");

        keyPressed = getch();

        if (keyPressed == 'q' || keyPressed == 'Q')
        {
            break; // Exit the game
        }

        if (keyPressed >= '1' && keyPressed <= '9')
        {
            if (!fixedCells[userRow][userCol]) // Only allow changes to non-fixed cells
            {
                board[userRow][userCol] = keyPressed - '0';

                // Check if the entire board is valid and complete
                if (isValidSudoku(board))
                {
                    printGrid(board, fixedCells);
                    printf("Congratulations! You've solved the Sudoku puzzle!\n");
                    getch(); // Wait for user to acknowledge
                    break; // Exit the game
                }
            }
        }

        switch (keyPressed)
        {
        case UP:
            userRow = (userRow - 1 + SIZE) % SIZE; // Move up
            break;
        case DOWN:
            userRow = (userRow + 1) % SIZE; // Move down
            break;
        case LEFT:
            userCol = (userCol - 1 + SIZE) % SIZE; // Move left
            break;
        case RIGHT:
            userCol = (userCol + 1) % SIZE; // Move right
            break;
        default:
            break;
        }
    }
}

int isBoardComplete(int board[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (board[i][j] == 0)
                return 0; // Return false if there is any empty cell
        }
    }
    return 1; // Return true if all cells are filled
}

int isValidSudoku(int board[SIZE][SIZE]){
    
    int row[SIZE][SIZE] = {0};
    int col[SIZE][SIZE] = {0};
    int subgrid[SIZE][SIZE] = {0};

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            int num = board[i][j];
            if (num != 0)
            {
                num--; // Decrease num to use as index (0-8 instead of 1-9)

                // Check row
                if (row[i][num])
                    return 0;
                row[i][num] = 1;

                // Check column
                if (col[j][num])
                    return 0;
                col[j][num] = 1;

                // Check 3x3 sub-grid
                int subgridIndex = (i / 3) * 3 + j / 3;
                if (subgrid[subgridIndex][num])
                    return 0;
                subgrid[subgridIndex][num] = 1;
            }
        }
    }

    // Check if the board is completely filled
    if (!isBoardComplete(board))
        return 0;

    return 1;
}
