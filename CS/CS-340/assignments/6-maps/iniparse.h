/******************************************************************************
 * This file is provided as a part of an NIU CSCI 340 Assignment. IT IS NOT   *
 * TO BE CHANGED. To complete the assignment, please put your code in the     *
 * files detailed in the assignment writeup.     `                            *
 *                                                                            *
 * CHANGES TO THIS FILE WILL RESULT IN A LARGE GRADE PENALTY.                 *
 ******************************************************************************/
#ifndef NIU_CSCI340_INIPARSE_H
#define NIU_CSCI340_INIPARSE_H

/******************************************************************************
 * Including settings.h 
 *
 *   settings.h defines a couple of typedefs that are used below. The defaults
 * in the version provided are:
 *
 *   - include and use the grid_row_major class as the SUDOKUGRID. This is 
 *      likely to be the easiest way, for those who successfully finished
 *      the previous assignment.
 *   - use a map<string, map<string, string>> as the INI_CONFIG used
 *      to hold data read in from INI files. You should leave this for the
 *      assignment, but it may be interesting to test with unordered_map or
 *      your future hash table class on your own time.
 *
 *   If you do not want to use the default settings, you can change them in
 * the settings.h file. Make sure that your changes make sense, as doing
 * something wrong in that file can affect the rest of the code.
 *
 *   IMPORTANT: If you *do* use your grid_row_major, make sure to add/commit/push
 *     the relevant files to *this* assignment's GitHub repo so it won't be 
 *     missing when the grader tries to compile.
 *     
 *     If you *do not* use your grid_row_major, you'll need to implement the
 *     relevant functionality in your settings.h and make sure the typedef
 *     for SUDOKUGRID is changed to reflect whatever you're using to handle
 *     the grid.
 *
 ******************************************************************************/
#include "settings.h"

void        add_ini_section(INI_CONFIG & config, const std::string &section);
int         remove_ini_section(INI_CONFIG & config, const std::string &section);

std::string get_ini_key(const INI_CONFIG &config, const std::string &section, const std::string &key);
void        set_ini_key(INI_CONFIG &config, const std::string &section, const std::string &key, const std::string & value);
int         remove_ini_key(INI_CONFIG &config, const std::string &section, const std::string &key);

INI_CONFIG  read_ini ( std::istream &input, int verbosity=0);
bool        write_ini( std::ostream & ost, const INI_CONFIG & config );
void        print_ini( std::ostream & ost, const INI_CONFIG & config );

#endif

