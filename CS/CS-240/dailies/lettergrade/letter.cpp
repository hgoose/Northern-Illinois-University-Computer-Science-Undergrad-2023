// Letter Grade daily - main

/* 
92 – 100 A
84 – 91 B
76 – 83 C
68 – 75 D
0 – 67 F 
*/

#include <iostream>
#include <iomanip>

using namespace std;

int main() {
  int score;
  char letter_grade = 'X';
  // Get the score from the user
  cout << "What is the test score? ";
  cin >> score;
  // Determine the letter grade (write your code after this line)
  
  if (score >= 92 && score <= 100) letter_grade = 'A';
  else if (score >= 84 ) letter_grade = 'B';
  else if (score >= 76 ) letter_grade = 'C';
  else if (score >= 68 ) letter_grade = 'D';
  else letter_grade = 'F';

  // Display the score and letter grade
  cout << endl << "The score "
      << score << " earns the grade "
      << letter_grade << endl;
  return 0;
}
