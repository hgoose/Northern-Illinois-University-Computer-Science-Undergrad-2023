#ifndef NIU_CSCI_340_GRID_TESTS_H
#define NIU_CSCI_340_GRID_TESTS_H

#include <iostream>
#include <iomanip>
#include <algorithm>
#include "grids.h"

/*! print_grid_at prints the contents of the given grid using atxy and atrc
 *  
 *  @tparam GRIDLIKE can be any type that works like a grid with height, width, atrc, atxy
 *  @param ost   ostream to send output to
 *  @param label string containing a label to print
 *  @param g     grid to print
 *  @param colw  width of the output data column (used with setw)
 ***/
template <typename GRIDLIKE>
void print_grid_at(std::ostream & ost, const std::string &label, const GRIDLIKE & g, int colw) {
  const int width = g.width();
  const int height = g.height();

  ost << "PRINTING " << label << " WITH atrc\n";
  for(int row = 0; row < height; ++row) {
    ost << "  | ";
    for(int col = 0; col < width; ++col) {
      ost << std::setw(colw) << g.atrc(row, col) << " "; }
    ost << "|\n"; }

  ost << "PRINTING " << label << " WITH atxy\n";
  for(int y = 0; y < height; ++y) {
    ost << "  | ";
    for(int x = 0; x < width; ++x) {
      ost << std::setw(colw) << g.atxy(x, y) << " "; }
    ost << "|\n"; }

  ost << "\n"; }


/*! print_grid_rowiter prints the contents of the given grid using the row iterators
 *  @tparam GRIDLIKE can be any type that works like a grid with height, width, rowbegin, rowend
 *  @param ost   ostream to send output to
 *  @param label string containing a label to print
 *  @param g     grid to print
 *  @param colw  width of the output data column (used with setw)
 ***/
template <typename GRIDLIKE>
void print_grid_rowiter(std::ostream & ost, const std::string &label, const GRIDLIKE & g, int colw) {
  const int height = g.height();

  ost << "GRID (" << label << ") PRINTING WITH ROW ITERATORS\n";
  for(int row = 0; row < height; ++row) {
    ost << "  | ";
    auto end = g.rowend(row); 
    for(auto it = g.rowbegin(row); it != end; ++it) {
      ost << std::setw(colw) << *it << " "; }
    ost << "|\n"; }

  ost << "\n"; }

/*! print_grid_coliter prints the transpose of the given grid using its column iterators
 *  @tparam GRIDLIKE can be any type that works like a grid with height, width, colbegin, colend
 *  @param ost   ostream to send output to
 *  @param label string containing a label to print
 *  @param g     grid to print
 *  @param colw  width of the output data column (used with setw)
 ***/
template <typename GRIDLIKE>
void print_grid_coliter(std::ostream & ost, const std::string &label, GRIDLIKE & g, int colw) {
  const int width = g.width();

  ost << "PRINTING TRANSPOSE OF " << label << " WITH COLUMN ITERATORS\n";
  for(int col = 0; col < width; ++col) {
    ost << "  | ";
    auto end = g.colend(col); 
    for(auto it = g.colbegin(col); it != end; ++it) {
      ost << std::setw(colw) << *it << " "; }
    ost << "|\n"; }

  ost << "\n"; }

/*! print_grid_stats prints info about a grid, and compares that info to expected values 
 *  @tparam GRID   can be any type that works like a grid with height, width, empty
 *  @param ost     ostream to send output to
 *  @param g       grid to print
 *  @param label   string containing a label to print
 *  @param eempty  expected value of g.empty()
 *  @param ewidth  expected value of g.width()
 *  @param eheight expected value of g.height()
 ***/
template <typename GRID>
void print_grid_stats(std::ostream & ost, GRID g, const std::string & label, bool eempty, int ewidth, int eheight) {
  const std::string indent = "  ";
  ost << indent << "CHECKING STATS FOR GRID " << label << "\n";
  ost << indent << indent << "empty? " << (g.empty() ? "yes" : "no ") << " - expected " << (eempty ? "empty" : "not empty") << " - " << ((eempty==g.empty()) ? "GOOD" : "WRONG") << "\n";
  ost << indent << indent << "width  = " << g.width() << " - expected " << ewidth << " - " << ((g.width() == ewidth) ? "GOOD" : "WRONG") << "\n";
  ost << indent << indent << "height = " << g.height() << " - expected " << eheight << " - " << ((g.height() == eheight) ? "GOOD" : "WRONG") << "\n";
  ost << "\n"; }


// first unit test, tests constructors and basic stats, doesn't do anything complicated with contents
template <typename T, typename GRIDCONT>
void test_grid_construct_and_stats(std::ostream & ost, int width, int height, int colw, const std::string & label) {

  ost << "TESTING CONSTRUCTOR AND BASIC STATISTIC METHODS FOR " << label << "\n";

  // make a grid that takes its data from another container's data, row major order
  grid_row_major<T, GRIDCONT> g1(width, height);

  // make a grid that starts out empty
  grid_row_major<T, GRIDCONT> g2;

  // make a grid that starts out with the same data that was put into g1
  grid_row_major<T, GRIDCONT> g3(g1);

  print_grid_stats(ost, g1, "g1", false, width, height);
  print_grid_stats(ost, g2, "g2 before assignment", true, 0, 0);

  ost << "ASSIGNING g1 TO g2\n";
  g2 = g1;
  print_grid_stats(ost, g2, "g2 after assignment", false, width, height);

  print_grid_stats(ost, g3, "g3 (copy constructed from g1)", false, width, height);

  ost << "CALLING g1.clear()\n";
  g1.clear();
  print_grid_stats(ost, g1, "g1 after clear", true, 0, 0);
}

// second unit test
template <typename T, typename GRIDCONT, typename SRCCONT>
void test_printing_with_at(std::ostream & ost, int width, int height, int colw, const std::string & label) {
  // make a grid that takes its data from another container's data, row major order
  SRCCONT src(width * height);
  int i = 0;
  for(int y=0; y<height; ++y) {
    for(int x=0; x<width; ++x) {
      src[i++] = (y+1)*100 + x + 1; } }

  grid_row_major<T, GRIDCONT> g1(width, height, src.begin(), src.end());

  print_grid_stats(ost, g1, "g1", false, width, height);

  ost << "  PRINTING GRID USING YOUR atxy AND atrc\n";
  ost << "    EXPECT:\n";
  ost << "      | 101 102 103 ... |\n";
  ost << "      | 201 202 203 ... |\n";
  ost << "      | 301 302 303 ... |\n";
  ost << "      | ...             |\n\n";

  print_grid_at(ost, "g1", g1, colw); 
}


// third unit test -- test row iterators for printing
template <typename T, typename GRIDCONT, typename SRCCONT>
void test_printing_with_rowiter(std::ostream & ost, int width, int height, int colw, const std::string & label) {
  // make a grid that takes its data from another container's data, row major order
  SRCCONT src(width * height);
  int i = 0;
  for(int y=0; y<height; ++y) {
    for(int x=0; x<width; ++x) {
      src[i++] = (y+1)*100 + x + 1; } }

  grid_row_major<T, GRIDCONT> g1(width, height, src.begin(), src.end());

  print_grid_stats(ost, g1, label, false, width, height);

  ost << "WILL PRINT (" << label << ") USING YOUR ROW ITERATORS\n";
  ost << "  EXPECT:\n";
  ost << "    | 101 102 103 ... |\n";
  ost << "    | 201 202 203 ... |\n";
  ost << "    | 301 302 303 ... |\n";
  ost << "    | ...             |\n\n";

  print_grid_rowiter(ost, "label", g1, colw); }


// fourth unit test - writing with row iter
template <typename T, typename GRIDCONT, typename SRCCONT>
void test_row_iter(std::ostream & ost, const SRCCONT & src, int width, int height, int colw, const std::string & label) {
  // make a grid that takes its data from another container's data, row major order
  grid_row_major<T, GRIDCONT> g1(width, height);
  for(int y=0; y<height; ++y) {
    for(int x=0; x<width; ++x) {
      g1.atxy(x,y) = (y+1)*100 + x;
    }
  }

  // make a grid that starts out empty
  grid_row_major<T, GRIDCONT> g2;

  // make a grid that starts out with the same data that was put into g1
  grid_row_major<T, GRIDCONT> g3(g1);

  print_grid_stats(ost, g1, "g1", false, width, height);
  print_grid_stats(ost, g2, "g2 before assignment", true, 0, 0);

  ost << "ASSIGNING g1 TO g2\n";
  g2 = g1;
  print_grid_stats(ost, g2, "g2 after assignment", false, width, height);

  print_grid_stats(ost, g3, "g3 (copy constructed from g1)", false, width, height);


  print_grid_rowiter(ost, "g1 before starting", g1, colw);

  std::copy(src.begin(), src.end(), g1.rowbegin(2)); 
  print_grid_rowiter(ost, "g1 with row 2 overwritten", g1, colw);
  
  std::copy(src.begin(), src.end(), g1.rowbegin(0)); 
  print_grid_rowiter(ost, "g1 with rows 2 and 0 overwritten", g1, colw);

}


// fifth unit test -- using column iterators
template <typename T, typename GRIDCONT, typename SRCCONT>
void test_printing_with_coliter(std::ostream & ost, int width, int height, int colw, const std::string & label) {
  // make a grid that takes its data from another container's data, row major order
  SRCCONT src(width * height);
  int i = 0;
  for(int y=0; y<height; ++y) {
    for(int x=0; x<width; ++x) {
      src[i++] = (y+1)*100 + x + 1; } }
  
  grid_row_major<T, GRIDCONT> g1(width, height, src.begin(), src.end());


  print_grid_stats(ost, g1, "g1", false, width, height);
 
  ost << "PRINTING NORMAL CONTENTS OF GRID (" << label << ") USING ROW ITERATORS\n";
  print_grid_rowiter(ost, "g1", g1, colw); 

  ost << "PRINTING TRANSPOSE OF GRID USING YOUR COLUMN ITERATORS\n";
  ost << "  EXPECT:\n";
  ost << "    | 101 201 301 ... |\n";
  ost << "    | 102 202 302 ... |\n";
  ost << "    | 103 203 303 ... |\n";
  ost << "    | ...             |\n\n";

  print_grid_coliter(ost, "g1", g1, colw); }


// sixth unit test - writing with row iter
template <typename T, typename GRIDCONT, typename SRCCONT>
void test_col_iter(std::ostream & ost, const SRCCONT & src, int width, int height, int colw, const std::string & label) {
  // make a grid that takes its data from another container's data, row major order
  grid_row_major<T, GRIDCONT> g1(width, height);
  for(int y=0; y<height; ++y) {
    for(int x=0; x<width; ++x) {
      g1.atxy(x,y) = (y+1)*100 + x;
    }
  }

  // make a grid that starts out empty
  grid_row_major<T, GRIDCONT> g2;

  // make a grid that starts out with the same data that was put into g1
  grid_row_major<T, GRIDCONT> g3(g1);

  print_grid_stats(ost, g1, "g1", false, width, height);
  print_grid_stats(ost, g2, "g2 before assignment", true, 0, 0);

  ost << "ASSIGNING g1 TO g2\n";
  g2 = g1;
  print_grid_stats(ost, g2, "g2 after assignment", false, width, height);

  print_grid_stats(ost, g3, "g3 (copy constructed from g1)", false, width, height);


  print_grid_rowiter(ost, "g1 before starting", g1, colw);

  std::copy_n(src.begin(), width, g1.rowbegin(2)); 
  print_grid_rowiter(ost, "g1 with row 2 altered", g1, colw);
  
  std::copy_n(src.begin(), height, g1.colbegin(2)); 
  print_grid_rowiter(ost, "g1, row 2, column 2 altered", g1, colw);

}


template <int width, int height, typename CONTAINER>
void test_construct_grid(std::ostream & ost, int colw, const std::string &label) {
  grid_row_major<int, CONTAINER> g(width, height);

  for(int y = 0; y < height; ++y) {
    for(int x = 0; x < width; ++x) {
      g.atxy(x, y) = y*10+x; } }
 
  print_grid_at(ost, label, g, colw); } 



#endif
