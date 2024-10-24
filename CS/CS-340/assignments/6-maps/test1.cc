
/******************************************************************************
 * This file is provided as a part of an NIU CSCI 340 Assignment. IT IS NOT   *
 * TO BE CHANGED. To complete the assignment, please put your code in the     *
 * files detailed in the assignment writeup.     `                            *
 *                                                                            *
 * CHANGES TO THIS FILE WILL RESULT IN A LARGE GRADE PENALTY.                 *
 ******************************************************************************/
// test1 - interactive testing for INI config tools
#include "settings.h"
#include "iniparse.h"
#include <fstream>

void prompt_and_do(INI_CONFIG & config) {
  using namespace std;
  int promptno = 1; // keep track of prompt number to help reference

  while(1) { // keep looping, will return when done
    int option;
    string sec, key, val, filename;

    cout << "\n";
    cout << "  1) add a new section         4) set the value of a key       7) save to a file\n";
    cout << "  2) remove a section          5) remove a key\n";
    cout << "  3) get the value of a key    6) print current config\n\n";
    cout << "[" << promptno++ << "] What to do? (0 when done): "; 
    cin >> option; 
    cout << "Got: " << option <<"\n";

    if(cin.eof()) return;

    switch(option) {
      case 0: // quit
        return;
      case 1: // add section
        cout << "  Section to add? "; 
        cin >> sec;
        cout << "\nAdding section \"" << sec << "\"\n";
        add_ini_section(config, sec);
        break;
      case 2: // remove section
        cout << "  Section to remove? "; 
        cin >> sec;
        cout << "\nRemoving section \"" << sec << "\"\n";
        remove_ini_section(config, sec);
        break;
      case 3: // look up key value
        cout << "  Section to look in? "; cin >> sec;
        cout << "  Key to look up? "; cin >> key;
        cout << "\n  Value of key \"" << key << "\" in section \"" << sec << "\": \"" << get_ini_key(config, sec, key) << "\"\n"; 
        break;
      case 4: // set key value
        cout << "  Section to look in? "; cin >> sec;
        cout << "  Key to change? "; cin >> key;
        cout << "  Value? "; cin >> val;
        cout << "\nSetting value of key \"" << key << "\" in section \"" << sec << "\" to \"" << val << "\"\n";
        set_ini_key(config, sec, key, val); 
        break;
      case 5: // remove key from section
        cout << "  Section? "; cin >> sec;
        cout << "  Key? "; cin >> key;
        cout << "\nRemoving key \"" << key << "\" from section \"" << sec << "\"\n";
        remove_ini_key(config, sec, key);
        break;
      case 6: // print
        cout << "\nPrinting current configuration:\n";
        print_ini(std::cout, config); 
        break;
      case 7: // save to file
        cout << "  Output filename? "; 
        cin >> filename;
        {
          cout << "Saving to file \"" << filename << "\":\n";
          ofstream file(filename);
          if(write_ini(file, config)) {
            cout << "Wrote file \"" << filename << "\" successfully.\n";
          }
          else {
            cout << "Nothing written to the file.\n";
          }
        }
      default:
        continue;
    }
  }
}

int main(int argc, char *argv[]) {
  std::cout << "*** TEST 1 - TEST YOUR INI CONFIG FUNCTIONS\n";
  std::cout << "***   Made reference output with:\n";
  std::cout << "***     ./test1 < input/test1.stdin\n";
  INI_CONFIG config; // start off empty
 
  std::cout << "*** STARTING STATE OF CONFIG\n";
  print_ini(std::cout, config);

  prompt_and_do(config); // prompt the user for what to do
                        
  std::cout << "*** FINAL STATE OF CONFIG\n";
  print_ini(std::cout, config);
}
