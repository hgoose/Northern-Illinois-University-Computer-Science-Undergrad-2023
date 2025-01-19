#include <cstdlib>
#include <iostream>

#define ROWS 8
#define COLS 8

using std::cout;
using std::endl;

void fill_board(bool arr[][COLS]);
void print_board(bool arr[][COLS]);
bool safe(bool arr[][COLS], int x, int y);
bool place_queens(bool arr[][COLS], int);


int main(int argc, const char *argv[]) {

  bool board[ROWS][COLS] = {};

  fill_board(board);  // Fill the board with zeros (8x8 matrix) 
 
  place_queens(board, 0);

  print_board(board);

  return EXIT_SUCCESS;

}


void fill_board(bool arr[][COLS]) {
  for (int i = 0; i < ROWS; ++i) {
      for (int j=0; j<COLS; ++j) {
          arr[i][j] = 0;
      }
  }
}


void print_board(bool arr[][COLS]) {
  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLS; ++j) {
      cout << arr[i][j] << " ";
    }
    cout << endl;
  }
}


bool safe(bool arr[][COLS], int x, int y) {

    for (int i=x-1, j=y-1, k=y+1; i>=0; --i, --j, ++k) {

        if (arr[i][y]) return false;

        if (j>=0 && arr[i][j]) return false;

        if (k<=7 && arr[i][k]) return false;
    }

    return true;
}


bool place_queens(bool arr[][COLS], int row_n) { 
    // Base case: Placed a queen on all rows
    if (row_n >= ROWS)
        return true;

    // For each column in a row
    for (int j=0; j<=7; ++j) {
        // If the spot is safe
        if (safe(arr, row_n, j)) {
            // Place the queen
            arr[row_n][j] = true;
            // Check the row beneath
            if (place_queens(arr, row_n+1)) {
                return true;
            }
            // If the row beneath cannot place a queen at any column, backtrack one row, place that queen in a different column
            arr[row_n][j] = false;
        }
    }
    // Queen could not be placed at any column
    return false;
}
