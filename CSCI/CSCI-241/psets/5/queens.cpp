//***************************************************************************
//
//  queens.cpp
//  CSCI 241 Assignment 5
//
//  Created by Nate Warner z2004109
//
//***************************************************************************
#include <cstdlib>
#include <iostream>

// Constants
#define ROWS 8 
#define COLS 8

// Using from the standard namespace
using std::cout;
using std::endl;

// Function declarations
void fill_board(bool arr[][COLS]);
void print_board(bool arr[][COLS]);
bool safe(bool arr[][COLS], int, int);
bool place_queens(bool arr[][COLS], int);


// Entry
int main(int argc, const char *argv[]) {

    // Initialize the board
    bool board[ROWS][COLS] = {};

    // Fill the board with zeros
    fill_board(board);  

    // Place the queens
    place_queens(board, 0);

    // Print the board
    print_board(board);

    // Exit
    return EXIT_SUCCESS;

}


/**
 * Function to fill the chess board with zeros (to symbolize empty positions)
 *
 * @logic
 * Step through the matrix, one row at a time, and fill all positions 
 * with zeros. This will give us an empty chess board.
 *
 * @param arr the 8x8 matrix that will represent the chess board (boolean array)
 *
 * @return void
 *
 */
void fill_board(bool arr[][COLS]) {
  for (int i = 0; i < ROWS; ++i) {
      for (int j=0; j<COLS; ++j) {
          arr[i][j] = 0;
      }
  }
}


/**
 * Function to print the contents of the chess board
 * to stdout
 *
 * @logic
 * Step through the matrix, one row at a time, and print the contents. 
 * Each row of the matrix is outputed per line
 *
 * @param arr the 8x8 matrix that will represent the chess board (boolean array)
 *
 * @return void
 *
 */
void print_board(bool arr[][COLS]) {
  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLS; ++j) {
      cout << arr[i][j] << " ";
    }
    cout << endl;
  }
}


/**
 * Function to determine if a position on the board is safe
 *
 *  @logic 
 *  Given a position on the board, we must check that there are no queens
 *  on any vertical tile above or below, horizontal tile left or right, and 
 *  diagonal tiles northeast or northwest.
 *
 * @param arr the 8x8 matrix that will represent the chess board (boolean array)
 * @param x is the integer to represent the vertical distance from the orgin. 
 * Where the top left corner of the board is the orgin (0,0)
 * @param y is the integer to represent the horizontal distance from the orgin. 

 * @return boolean representing if the position of interest is safe
 * from all other queens on the board
 *
 */
bool safe(bool arr[][COLS], int x, int y) {

    // Given a position (x,y), we declare 3 variables. i for the vertical change in x,
    // j for the negative change in y, and k for the positive change in y. At each step we first
    // check that the position above the given x is safe, then we check the left diagnoal (if possible), then
    // finally we check the right diagonal. If any queens are found, we return false. 
    // Otherwise we know the position is safe and true will get returned
    for (int i=x-1, j=y-1, k=y+1; i>=0; --i, --j, ++k) {

        if (arr[i][y]) return false; // Check the position above x

        if (j>=0 && arr[i][j]) return false; // Check the left diagonal
 
        if (k<=7 && arr[i][k]) return false; // Check the right diagonal
    }

    // If we made it to here, we can return true. The position is safe.
    return true;
}


/**
 * Function to place 8 queens on the chess board s.t none 
 * of the queens are attacking each other
 *
 * @logic recursive function, each insertion to the call stack
 * attempts to place one queen. We start at the top and work our way down.
 * We begin at the leftmost column of the row, if the position is safe, we place the queen.
 * If it is not safe, we move one column to the right. After we place the queen, we recursively call  
 * the function, testing the return value, if this test returns true, we know that we have placed all of
 * the queens successfully, and we return true ourselfs. For each row, we place a queen, 
 * then test all rows beneath, if we cant place all subsequent queens, we backtrack and try a column to the right.
 *
 * @param arr the 8x8 matrix that will represent the chess board (boolean array)
 * @param n an integer for the row number we want to place the current queen on 
 *
 * @return boolean
 *
 */
bool place_queens(bool arr[][COLS], int row_n) { 

    // Base case, we run out of rows to check
    if (row_n >= ROWS) {
        return true;
    } 

    // Loop for each tile in a given row
    for (int j=0; j<=7; ++j) {

        // Check if the current position is safe
        if (safe(arr, row_n, j)) {

            // Place the queen
            arr[row_n][j] = true;

            // Try the row beneath
            if (place_queens(arr, row_n+1)) {
                return true; // We have placed all queens
            }

            arr[row_n][j] = false; // All rows beneath current didnt succeed, we backtrack.
                                   // the next iteration will take effect.
        }
    }

    return false; // Queen could not be placed on the given row.
}
