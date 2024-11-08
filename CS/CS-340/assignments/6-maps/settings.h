#ifndef NIU_CSCI340_ASSIGN_ASSOC_SETTINGS_H
#define NIU_CSCI340_ASSIGN_ASSOC_SETTINGS_H

////////////////////////////////////////////////////////////////////////////////
//  This file is used to configure a few settings that may be necessary.
// This is the only one of the supplied header files that you are allowed to
// change, so if you need to include or declare something to make your
// program work, then do it in here.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Settings available for the INI parsing part.
////////////////////////////////////////////////////////////////////////////////
// The map_of_maps typedef is used in the declarations of several functions.
// It starts as a map with string keys to elements which are themselves maps
// with string keys to key elements.
//
// Leave this setting alone for the assignment, but you could try using an
// unordered map or (later) your hash table to see how the performance differs.
////////////////////////////////////////////////////////////////////////////////
#include <map>
#include <string>

// You should leave these alone for the purposes of the assignment
typedef std::map< std::string, std::string> INI_KEYS;
typedef std::map< std::string, INI_KEYS> INI_CONFIG;

////////////////////////////////////////////////////////////////////////////////
// Settings available for the Sudoku part
////////////////////////////////////////////////////////////////////////////////
//   SET_TYPE is the type used to implement the set functionality. It should 
//     stay as std::set<int> for submission, but you could try out other classes
//     that do the same thing (such as the unordered version, or a homebrew
//     version of set you could write as an exercise.)
//   SUDOKUGRID is the type that will be used to hold the grid used for the
//     Sudoku solver functions. The default is to use the grid_row_major you
//     implemented for the last assignment, but if you do not wish to or are
//     not able to use that, then you'll be able to configure the type you
//     choose to use by changing that typedef.
////////////////////////////////////////////////////////////////////////////////

// SET_TYPE is a typedef defining the type used for sets within the SUDOKUGRID
//   The default will just be SET_TYPE, and you should leave it for submission.
#include <set>
typedef std::set<int> SET_TYPE;

// This is done as a typedef so you can experiment with different classes
// that implement the set functionality, such as:
//typedef std::unordered_set<int> SET_TYPE;

////////////////////////////////////////////////////////////////////////////////
// IMPORTANT: If you would like to reuse your grid class from the previous
//   assignment,  USE_PREVIOUS_GRID_IMPL to 1
////////////////////////////////////////////////////////////////////////////////

//#undef USE_PREVIOUS_GRID_IMPL /* do not try to use the previous grid */
#define USE_PREVIOUS_GRID_IMPL /* Use the grid from the previous assignment*/

#ifdef USE_PREVIOUS_GRID_IMPL
#include "grids.h"
#endif

// If you're not planning to use the grid_row_major class from your previous 
// assignment, then you'll need to change this typedef to the type you will
// be using to handle the Sudoku solution grid.
// It will need to be able to store a 9x9 grid of sets of integers.
typedef grid_row_major< SET_TYPE > SUDOKUGRID;

#endif

