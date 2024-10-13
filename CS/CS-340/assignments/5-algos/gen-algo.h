#ifndef NIU_CSCI340_GEN_ALGO_IMPL_H
#define NIU_CSCI340_GEN_ALGO_IMPL_H

#include "gen-algo.decl.h"

#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <string>
using std::string;

template <typename FN>
size_t read_lines(std::istream &instream, FN linecb) {
    string get; size_t count{0};
    while (getline(instream, get)) {
        linecb(get);
        ++count;
    }
    return count;
}

template <typename FN>
size_t split_string_strict(const std::string&instring, FN tokencb, char delim) {

    string::const_iterator start = instring.begin(), end = instring.end();

    size_t count{0};
    while (start != end) {
        string::const_iterator t = std::find(start,end, delim);
        if (t != end) {
            string stmp(start,t);
            tokencb(stmp);
            start = t+1;
            ++count;
        } else {
            string stmp(start, t);
            tokencb(stmp); 
            ++count;
            break;
        }
    }
    return count;
}


template <typename FN>
size_t split_string_greedy(const std::string &instring, FN tokencb, char delim) {

    string::const_iterator start = instring.begin(), end = instring.end();

    size_t count{0};
    while (start != end) {
        string::const_iterator t = std::find(start,end, delim);
        if (t != end) {
            string snew(start, t);
            if ( !(all_of(snew.begin(), snew.end(), [] (char c) { return c == ' '; }))) {
                tokencb(snew);
                start = t + 1;
                ++count;
            } else {++start;}
        } else {
            string snew(start,t);
            tokencb(snew);
            ++count;
            break;
        }
    }
    return count;
}

template <typename TABLE, typename ARRLIKE>
void print_table(std::ostream & ost, 
                 const TABLE & table, 
                 const ARRLIKE & widths, 
                 unsigned int maxcol, 
                 const std::string &pre, 
                 const std::string &sep,
                 const std::string &post,
                 bool leftalign) 
{

    unsigned colcount{0}, widthidx = 0;
    for (auto it = table.begin(); it!=table.end(); ++it) {
        colcount=0;
        widthidx = 0;
        ost << pre;
        std::for_each(it->begin(), it->end(), [&] (const auto& s) {
                if (colcount != maxcol) {
                    ost << (leftalign ? std::left : std::right) << std::setw(widths[widthidx++]) << s << (colcount == (maxcol - 1) ? "" : sep);
                    ++colcount;
                }

        });
        ost << post << '\n';
    }

}

// NOTE: This is not a template, and typically you should not put non-templated
// function definitions in header files. I'm leaving it anyway to keep things
// simpler for the assignment, but it could cause problem if multiple files
// were separately compiled after including this header. This is not happening
// for this assignment.
int table_min_cols(const STR_TABLE &table) {
    int min = table[0].size();

    std::for_each(table.begin() + 1, table.end(), [&] (const auto& row) {
            if ((int) row.size() < min) min = row.size();
    });
    return min;
}


template <typename STR_TABLE>
std::vector<int> calc_widths(const STR_TABLE & table) {

    std::vector<int> biggest_widths;
    int cols = table[0].size();
    int biggest{0};
    for (int i=0; i<cols; ++i) {
        biggest = table[0][i].size();
        for_each(table.begin(), table.end(), [&](const auto& row) {
                int tmp = row[i].size();
                if (tmp > biggest) {
                    biggest = tmp;
                }
        });
        biggest_widths.push_back(biggest);
    }
    return biggest_widths;
}

// NOTE: This is not a template, and typically you should not put non-templated
// function definitions in header files. I'm leaving it anyway to keep things
// simpler for the assignment, but it could cause problem if multiple files
// were separately compiled after including this header. This is not happening
// for this assignment.
STR_TABLE load_tsv(const std::string & filename) {
    STR_TABLE table;
    std::ifstream input(filename);

    read_lines(input, [&] (const string& s) {
            std::vector<string> tmp;
            split_string_strict(s,[&] (const string& substr) {
                    tmp.push_back(substr);

            },'\t');
            table.push_back(tmp);
    });

    return table;
}

// NOTE: This is not a template, and typically you should not put non-templated
// function definitions in header files. I'm leaving it anyway to keep things
// simpler for the assignment, but it could cause problem if multiple files
// were separately compiled after including this header. This is not happening
// for this assignment.
void table_sort_alpha(STR_TABLE & table, unsigned int col) {
    std::sort(table.begin(), table.end(), [&col] (const auto& a, const auto& b) -> bool {
            return a[col] < b[col];
    });
}

// NOTE: This is not a template, and typically you should not put non-templated
// function definitions in header files. I'm leaving it anyway to keep things
// simpler for the assignment, but it could cause problem if multiple files
// were separately compiled after including this header. This is not happening
// for this assignment.
void table_sort_numer(STR_TABLE & table, unsigned int col) {
    std::sort(table.begin(), table.end(), [&col] (const auto& a, const auto& b) -> bool {
            try {
                return stod(a[col]) < stod(b[col]);
            } catch (std::invalid_argument) {
                return a[col] < b[col];

            }
    });
}
#endif
