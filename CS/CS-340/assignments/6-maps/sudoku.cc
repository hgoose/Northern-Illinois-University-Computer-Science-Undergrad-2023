//***************************************************************************
//
//  Sudoku.cc
//  CSCI 340 Assignment 6 
//
//  Created by Nate Warner z2004109
//
//***************************************************************************

// Includes
#include "settings.h"
#include "sudoku.h"
#include <algorithm>

// Using
using std::set;


//***************************************************************************
//
//  Function: set_sudoku_cell_known
//
//  Purpose: Sets a Sudoku grid cell to a known value by clearing all
//           other possibilities from the set and inserting the solution.
//
//  Parameters: 
//     grid - Sudoku grid structure.
//     row  - Row index of the cell.
//     col  - Column index of the cell.
//     solution - The known value to set in the cell.
//
//  Returns: None.
//
//***************************************************************************
void set_sudoku_cell_known(SUDOKUGRID &grid, int row, int col, int solution) {
    // Get a reference to the set at grid_{ij}
    set<int>& s = grid.atrc(row,col);

    // Clear the set
    s.clear();
    
    // Insert the solution
    s.insert(solution);
}


//***************************************************************************
//
//  Function: set_sudoku_cell_unknown
//
//  Purpose: Sets a Sudoku grid cell to unknown by initializing it with
//           all possible values (1 through 9).
//
//  Parameters: 
//     grid - Sudoku grid structure.
//     row  - Row index of the cell.
//     col  - Column index of the cell.
//
//  Returns: None.
//
//***************************************************************************
void set_sudoku_cell_unknown(SUDOKUGRID &grid, int row, int col) {
    // Get a reference to the set at grid_{ij}
    set<int>& s = grid.atrc(row,col);

    // Clear the set and initialize with values 1-9
    s.clear();
    for (int i=1; i<10; ++i) {
        s.insert(i);
    }
}



//***************************************************************************
//
//  Function: remove_sudoku_option
//
//  Purpose: Removes a specific value from the possible options in a Sudoku
//           cell.
//
//  Parameters: 
//     grid - Sudoku grid structure.
//     row  - Row index of the cell.
//     col  - Column index of the cell.
//     value - The value to remove from the cell's possible options.
//
//  Returns: None.
//
//***************************************************************************
void remove_sudoku_option(SUDOKUGRID &grid, int row, int col, int value) {
    // Get the set at grid_{ij}, erase the requested value
    set<int>& s = grid.atrc(row,col);
    s.erase(value);
}



//***************************************************************************
//
//  Function: print_sudoku_grid
//
//  Purpose: Prints the current state of the Sudoku grid to the provided
//           output stream, displaying known, unknown, and impossible cells.
//
//  Parameters: 
//     ost       - Output stream to print the grid to.
//     grid      - Sudoku grid structure.
//     unknown   - Character to represent unknown cells.
//     impossible - Character to represent impossible cells.
//
//  Returns: None.
//
//***************************************************************************
void print_sudoku_grid(std::ostream & ost, const SUDOKUGRID &grid, char unknown, char impossible) {

    int count_row_entries = 0, count_col = 0;
    int first = 0, near_pipe=1;

    // For each row
    for (int i=0; i<grid.height(); ++i, ++count_col)  {
        // If we outputted three rows, output separator
        if (count_col == 3) {
            ost << "---------|---------|---------" << endl;
            count_col = 0;
        }
        // Get row iterators
        auto start = grid.rowbegin(i), end = grid.rowend(i);

        // Traverse the row
        while (start != end) {
            // Check if we need a pipe
            if (count_row_entries == 3 || count_row_entries == 6) {
                ost << "| ";
                count_row_entries = (count_row_entries == 6 ? 0 : count_row_entries);
            }
            // Output value, or unknown/impossible indicator, with correct spacing
            if (start->size() == 1) {
                ost << (first++ == 0 ? " " : "") << *start->begin() << (near_pipe == 3 || near_pipe == 6 ? " " : (near_pipe == 9 ? " " :"  "));
                ++near_pipe;
            } else if (start->size() > 1) {
                ost << (first++ == 0 ? " " : "") << unknown << (near_pipe == 3 || near_pipe == 6 ? " " : (near_pipe == 9 ? " " :"  "));
                ++near_pipe;
            } else {
                ost << impossible << ' ';
            }
            ++start, ++count_row_entries;
        }
        // Newline, reset format helper variables for each row
        ost << endl;
        count_row_entries=0;
        near_pipe=1;
        first=0;
    }
    // Final newline
    ost << endl;
}


//***************************************************************************
//
//  Function: handle_row_for_cell
//
//  Purpose: Removes the value from the other cells in the same row as the
//           specified cell.
//
//  Parameters: 
//     grid - Sudoku grid structure.
//     row  - Row index of the cell.
//     col  - Column index of the cell.
//
//  Returns: The number of erasures performed.
//
//***************************************************************************
////////////////////////////////////////////////////////////////////////////////
// This one is provided. You do not need to change it.
////////////////////////////////////////////////////////////////////////////////
int handle_sudoku_cell(SUDOKUGRID &grid, int row, int col) {
  int count = 0;

  count += handle_row_for_cell(grid, row, col); 
  count += handle_col_for_cell(grid, row, col); 
  count += handle_subgrid_for_cell(grid, row, col); 

  return count; 
}



//***************************************************************************
//
//  Function: handle_row_for_cell
//
//  Purpose: Removes the value from the other cells in the same row as the
//           specified cell.
//
//  Parameters: 
//     grid - Sudoku grid structure.
//     row  - Row index of the cell.
//     col  - Column index of the cell.
//
//  Returns: The number of erasures performed.
//
//***************************************************************************
int handle_row_for_cell(SUDOKUGRID &grid, int row, int col) {
    // Get the set at row col
    set<int>& s = grid.atrc(row,col);
    if (s.size() != 1) {
        return 0;
    }
    // Get the element that we need to remove from the other entries on the row
    int el = *s.begin();

    int numErases = 0;
    int curr_col = 0;
    // For each position in row
    std::for_each(grid.rowbegin(row), grid.rowend(row), [&](set<int>& entry) {
        // Make sure its not the position we grabbed the element from
        if (curr_col != col) {
            int n = entry.erase(el); // Erase
            numErases+=n;
        }
        ++curr_col; // Advance
    });
    return numErases;
}


//***************************************************************************
//
//  Function: handle_col_for_cell
//
//  Purpose: Removes the value from the other cells in the same column as the
//           specified cell.
//
//  Parameters: 
//     grid - Sudoku grid structure.
//     row  - Row index of the cell.
//     col  - Column index of the cell.
//
//  Returns: The number of erasures performed.
//
//***************************************************************************
int handle_col_for_cell(SUDOKUGRID &grid, int row, int col) {
    
    // Mirror of handle_row, but for columns
    set<int>& s = grid.atrc(row,col);
    if (s.size() != 1) {
        return 0;
    }
    int el = *s.begin();

    int numErases = 0;
    int curr_row = 0;
    std::for_each(grid.colbegin(col), grid.colend(col), [&](set<int>& entry) {
        if (curr_row != row) {
            int n = entry.erase(el);
            numErases+=n;
        }
        ++curr_row;
    });
    return numErases;
}


//***************************************************************************
//
//  Function: handle_subgrid_for_cell
//
//  Purpose: Removes the value from the other cells in the same 3x3 subgrid
//           as the specified cell.
//
//  Parameters: 
//     grid - Sudoku grid structure.
//     row  - Row index of the cell.
//     col  - Column index of the cell.
//
//  Returns: The number of erasures performed.
//
//***************************************************************************
int handle_subgrid_for_cell(SUDOKUGRID &grid, int row, int col) {
    // Helper lambda to advance the column iterator
    auto advance = [&](auto& colit, int n) {
        for (int i=0; i<n; ++i) {
            ++colit;
        }
    };

    // Get the set
    set<int>& s = grid.atrc(row,col);

    // Noop if the set has more than one element
    if (s.size() != 1) {
        return 0;
    }
    // Get the element
    int el = *s.begin();

    // Compute the starting index for the subgrid
    int r_gridstart = (row/3)*3, c_gridstart = (col/3) * 3;

    int count=0, numErases=0;

    // For all three columns
    while (count < 3) {

        // Get the column iterator to the start of each column
        auto col_it_start = grid.colbegin(c_gridstart + count); 

        // Advance it if needed (down the rows)
        advance(col_it_start, r_gridstart);

        // For all three rows
        for (int i=0; i<3; ++i, ++col_it_start) {
            // Get the set
            set<int>& entry = *col_it_start;
            
            // Make sure we are not removing from the set we grabbed the element from.
            if ((count == (col % 3)) && (i == (row % 3)) ) {
                continue;
            }

            // Erase from set
            int n = entry.erase(el);
            numErases+=n;
        }
        ++count; // Increment column number
    }
    return numErases;
}


//***************************************************************************
//
//  Function: load_sudoku_grid
//
//  Purpose: Loads the Sudoku grid from a file and populates the grid
//           structure.
//
//  Parameters: 
//     filename - The name of the file to load the grid from.
//     grid     - Sudoku grid structure.
//
//  Returns: Boolean indicating success or failure.
//
//***************************************************************************
bool load_sudoku_grid(const std::string &filename, SUDOKUGRID &grid) {
    return grid.load_from_file(filename); // Use modified load_from_file method

}

//***************************************************************************
//
//  Function: initialize_grid
//
//  Purpose: Initializes the Sudoku grid to the correct dimensions (9x9).
//
//  Parameters: 
//     grid - Sudoku grid structure.
//
//  Returns: None.
//
//***************************************************************************
void initialize_grid(SUDOKUGRID &grid) {
  grid.resize(9,9); // Init grid
}

