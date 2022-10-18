/* 
    * This program solves a sudoku puzzle using a recursive backtracking algorithm.
    * The puzzle will be assumed to be of dimension 9x9 and be represented as an
    * array of integers. 0 will be used to represent an empty sudoku cell. Solution
    * to the puzzle will be printed to the console.
*/

#include <iostream>

// N will define the size of the sudoku grid NxN
#define N 9

using namespace std;

/*  
    * Define the initial unsolved sudoku grid.
    * Current: Break the Code 2.0 Sudoku Cypher
    * 
    * For ease of changing:
    * 
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0}
*/

int startGrid[N][N] = {
    {0, 0, 7, 2, 5, 4, 9, 0, 0},
    {1, 0, 4, 8, 9, 0, 7, 5, 6},
    {9, 5, 8, 6, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 8, 1, 0, 0, 3},
    {5, 4, 3, 0, 0, 0, 1, 9, 8},
    {7, 0, 1, 9, 3, 5, 0, 2, 4},
    {4, 0, 5, 3, 0, 9, 8, 1, 7},
    {0, 7, 0, 1, 4, 8, 2, 0, 5},
    {8, 1, 2, 5, 7, 6, 3, 4, 0}
};

/* 
    * We require methods to check whether a number exists in a given row or 
    * column. We also need to check if a number appears in any 3x3 sub-grid. 
*/

/*
    * Check if a number is present in a given row.
    * @param row: The row we are checking.
    * @param num: The number we are checking for.
    * @return true if the number is present in the row, false otherwise.
*/
bool checkRow(int row, int num){
    for (int col = 0; col < N; col++){
        if (startGrid[row][col] == num){
            return true;
        }
    }
    return false;
}

/*
    * Check if a number is present in a given column.
    * @param col: The column we are checking.
    * @param num: The number we are checking for.
    * @return true if the number is present in the column, false otherwise.
*/
bool checkCol(int col, int num){
    for (int row = 0; row < N; row++){
        if (startGrid[row][col] == num){
            return true;
        }
    }
    return false;
}

/*
    * Check if a number is present in a given 3x3 sub-grid.
    * @param row: The 'first' row in the 3x3 sub-grid.
    * @param col: The 'first' column in the 3x3 sub-grid.
    * @param num: The number we are checking for.
    * @return true if the number is present in the sub-grid, false otherwise.
    * 
    * Note: The 'first' row and column are taken from the top left corner of the
    *       sub grid.
*/
bool checkSubGrid(int firstRow, int firstCol, int num){
    for (int row = 0; row < 3; row ++){
        for (int col = 0; col < 3; col ++){
            if (startGrid[row + firstRow][col + firstCol] == num){
                return true;
            }
        }
    }
    return false;
}

/*
    * Method to check for empty cells within the grid.
    * @param row: The row of the empty cell.
    * @param col: The column of the empty cell.
    * @return true if an empty cell is found, false otherwise.
*/
bool findEmptyCells(int &row, int &col){
    for (row = 0; row < N; row++){
        for (col = 0; col < N; col++){
            if (startGrid[row][col] == 0){
                return true;
            }
        }
    }
    return false;
}

/*
    * Method that checks is a given number can be placed in a given cell.
    * ie. Checks if the number is present in the row, column or 3x3 sub-grid.
    * @param row: The row of the cell.
    * @param col: The column of the cell.
    * @param num: The number we are checking.
    * @return true if the number can be placed in the cell, false otherwise.
*/
bool checkCellValid(int row, int col, int num){
    return !checkRow(row, num) && !checkCol(col, num) && !checkSubGrid(row - row % 3, col - col % 3, num);
}
/*
    * Method to print out the sudoku grid to the console after solving.
*/
void printGrid(){
    for (int row = 0; row < N; row++){
        for (int col = 0; col < N; col ++){
            if (col == 3 || col == 6){
                cout << " | ";
            }
            cout << startGrid[row][col] << " ";
        }
        if (row == 2 || row == 5){
            cout << endl;
            for (int i = 0; i < N; i++){
                cout << "---";
            }
        }
        cout << endl;
    }
}

/*
    * Method that implements the recursive backtracking algorithm to solve the
    * sudoku puzzle.
    * @return true if the puzzle is solved, false otherwise.
*/
bool solveSudoku(){
    int row, col;
    // If there are no longer any empty cells, the puzzle has been solved.
    if (!findEmptyCells(row, col)){
        return true;
    }
    // Try placing the numbers 1-9 in each empty cell
    for (int num = 1; num < 10; num ++){
        // Check the validity of the number in the cell. If true place the number
        // in the cell and recursively call the method to continue solving.
        if (checkCellValid(row, col, num)){
            startGrid[row][col] = num;
            if (solveSudoku()){
                return true;
            }
            // If the number cannot be placed in the cell, reset the cell to 0.
            startGrid[row][col] = 0;
        }
    }
    return false;
}

/*
    * Main method that runs the program. Will print the solution to the console
    * if a solution is found.
*/
int main()
{
    if (solveSudoku() == true){
        printGrid();
    }
    else{
        cout << "This sudoku is not solvable." << endl;
    }
}