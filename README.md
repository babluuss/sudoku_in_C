# Sudoku Game in C (Playable with the keyboard!)

Weo the Sudoku Game repository! This project is a simple yet challenging Sudoku game built entirely in the C programming language. The game offers three difficulty levels, allowing players to choose their preferred level of challenge.


## Sudoku Rules

Sudoku is a logic-based, combinatorial number-placement puzzle. The objective is to fill a 9x9 grid with digits so that each column, each row, and each of the nine 3x3 subgrids (also called "boxes") contain all of the digits from 1 to 9. The puzzle starts with some cells already filled in, and the difficulty of the puzzle depends on the number of cells initially filled and their a
### Basic Rules:
1. Each row must contain the digits 1 to 9 without repetition.
2. Each column must contain the digits 1 to 9 without repetition.
3. Each of the nine 3x3 subgrids must contain the digits 1 to 9 without repetition.

## How to Play

1. **Choose Difficulty**: The game offers three difficulty levels—easy, medium, and hard. The difficulty level determines the number of pre-filled cells and the complexity of the puzzle.
2. **Fill the Grid**: Using the numbers 1 to 9, fill the empty cells on the grid. Ensure that each number appears only once in each row, column, and 3x3 subgrid.
3. **Solve the Puzzle**: Continue filling in numbers until the entire grid is complete. The game will verify if the solution is correct.

## How to Compile and Run

To compile and run the Sudoku game, follow these steps:

1. **Clone the Repository**:
    ```bash
    git clone https://github.com/pinedah/sudoku_in_c.git
    cd sudoku-game
    ```

2. **Compile the Game**:
    ```bash
    gcc -o sudoku sudoku.c
    ```

3. **Run the Game**:
    ```bash
    ./sudoku
    ```

## References for Sudoku Generation Algorithm

The algorithm provided for generating a Sudoku grid involves several well-known concepts and techniques commonly used in Sudoku puzzle generation and solving. Here are the main concepts and some references:

1. **Backtracking Algorithm**:
   - The `fillGrid` function uses a backtracking algorithm to fill the grid with a valid Sudoku solution. Backtracking is a general algorithm for finding all (or some) solutions to computational problems, notably used in constraint satisfaction problems like Sudoku.
   - Reference: ["Backtracking" on Wikipedia](https://en.wikipedia.org/wiki/Backtracking)

2. **Constraint Propagation**:
   - The `isSafe` function checks if placing a number violates any Sudoku rules. This is a form of constraint propagation, ensuring that constraints (rules) are satisfied.
   - Reference: ["Constraint satisfaction problem" on Wikipedia](https://en.wikipedia.org/wiki/Constraint_satisfaction_problem)

3. **Randomization**:
   - The grid is filled with random numbers from 1 to 9, and cells are removed randomly to create the puzzle. Randomization helps in generating different puzzles each time.
   - Reference: ["Sudoku" on Wikipedia, especially the "Construction" section](https://en.wikipedia.org/wiki/Sudoku#Construction)

4. **Sudoku Puzzle Difficulty**:
   - The number of cells removed to set the difficulty level of the puzzle is based on typical practices in Sudoku puzzle creation. More cells removed generally means a higher difficulty level.
   - Reference: ["Sudoku" on Wikipedia, particularly the sections discussing puzzle generation and difficulty](https://en.wikipedia.org/wiki/Sudoku)

These references provide a comprehensive background on the techniques and concepts used in the provided algorithm for generating a Sudoku grid with varying difficulty levels.


## Note

I built this Sudoku game because I saw my girl, playing it once and told her I could build it. This project is dedicated to her and her love for Sudoku.

Enjoy the game!

## License

This project is licensed under the MIT License - see the [LICENSE](./LICENSE) file for details.
