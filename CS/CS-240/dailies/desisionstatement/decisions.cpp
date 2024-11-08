//Decision Statements main.cpp

#include <iostream>
#include <iomanip>

using namespace std;


int main() {
  int x, y;
  char single_letter;
  string word;

  //get two integers, a character, and a string from the user

  cout << "Enter a number (NO decimal point): ";
  cin >> x;

  cout << "Enter another number (NO decimal point): ";
  cin >> y;

  cout << "Enter a single character: ";
  cin >> single_letter;

  cout << "Enter a word: ";
  cin >> word;

  cout << endl << endl;

  if (x > y) {
    cout << x << " is greater than " << y << endl;


  } 
  if (x < y) {
      cout << x << " is less than " << y << endl;
  }  
  if (x >= y) {
      cout << x << " is greater than or equal to " << y << endl;
  } 
  if (x <= y) {
      cout << x << " is less than or equal to " << y << endl;

    }
  if (x==y) {
    cout << x << " is equal to " << y << endl;
    } 

  if (x != y) {
      cout << x << " is not equal to " << y << endl;
  }

  if (single_letter == 'P') {
      cout << "PINEAPPLE" << endl;
  }

  if (word == "C++") {
      cout << "C PLUS PLUS" << endl;
  }

    cout << endl;
  


  return 0;
  }


