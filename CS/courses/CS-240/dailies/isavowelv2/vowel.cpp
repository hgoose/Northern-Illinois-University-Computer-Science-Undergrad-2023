// Is a Vowel daily

#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

// array of possible lowercase vowel values
const char vowels[5] = {'a', 'e', 'i', 'o', 'u'};

// function prototype
bool isVowel(const char&);

int main() {
  char input1, input2, input3;

  cout << "Let\'s test whether some characters are vowels or not." << endl << endl;

  // get 3 characters from the user
  cout << "Enter three characters separated by spaces: ";
  cin >> input1 >> input2 >> input3;

  // test user input
  cout << endl << endl << "Test 1a: Checking if \'" << input1 << "\' is a vowel..." << endl << endl;
  cout << "The function determined that \'" << input1 << "\' " << ((isVowel(input1)? "is": "is not")) << " a vowel." << endl;

  cout << endl << endl << "Test 2: Checking if \'" << input2 << "\' is a vowel..." << endl << endl;
  cout << "The function determined that \'" << input2 << "\' " << ((isVowel(input2)? "is": "is not")) << " a vowel." << endl;

  cout << endl << endl << "Test 3: Checking if \'" << input3 << "\' is a vowel..." << endl << endl;
  cout << "The function determined that \'" << input3 << "\' " << ((isVowel(input3)? "is": "is not")) << " a vowel." << endl;


  return 0;
}

bool isVowel(const char& c) {
  
  for (const auto& i : vowels) {
    if (std::tolower(c) == i) {
      return true;
    }
  }
  return false;
}


