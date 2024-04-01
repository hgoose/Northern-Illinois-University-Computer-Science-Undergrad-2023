/***************************************************************
CSCI 240         Program 6     Fall 2023

Programmer: Nathan Warner
 
Section: 001

Date Due: 10-20-23

Purpose: Write VI functions for VI computational exercises
***************************************************************/
#include <iostream>
#include <iomanip>
#include <cstdlib>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;

// Function Prototypes
int Menu();
int getValue( string prompt, int lowerBound, int upperBound );
int sumOfSquares( int limit );
double averageOfCubes( int limit );
int sumOfASCII( int limit );
void NIUchant(int iterations);

// Entry
int main(int argc, const char *argv[]) {
    // flag approach for the loop, this way we dont require duplicated code
    bool flag{0};

    do {
        // Call the menu function, saving the users choice
        int opt = Menu();

        // Check if the user quits
        if (opt == 5) { flag = 1; }
        // Circumvent non existent choices
        else if (opt < 0 || opt > 4) { cout << "Invalid Option: " << endl; } 

        // Valid choice
        else {

            // Variables needed for function args
            int limit{0}, int_result{0};
            double double_result{0};

            // Cases for the users option, calling the correct function
            switch ( opt ) {

                // If the user wants to do sumOfSquares
                case 1:
                    cout << "How many squares will we summate? (2-20): "; 
                    cin >> limit;
                    while (limit < 2 || limit > 20) {
                        cout << limit << " is an invalid value. Try again: ";
                        cin >> limit;
                    }
                    int_result = sumOfSquares(limit);
                    cout << "The sum of the first " << limit << " positive numbers squared is " << int_result << endl << endl;
                    break;

                // If the user wants to do averageOfCubes
                case 2:
                    cout << "How many cubes will we average? (2-20): ";
                    cin >> limit;
                    while (limit < 2 || limit > 20) {
                        cout << limit << " is an invalid value. Try again: ";
                            cin >> limit;
                    }
                    double_result = averageOfCubes(limit);
                    cout << "The average of the first " << limit << " positive numbers cubes is " << double_result << endl << endl;
                    break;

                // If the user wants to do sumOfASCII
                case 3:
                    cout << "How many ASCII values will we summate? (1 - 26): ";
                    cin >> limit;
                    while (limit < 1 || limit > 26) {
                        cout << limit << " is an invalid value. Try again: ";
                        cin >> limit;
                    }
                    int_result = sumOfASCII(limit);
                    cout << "The sum of the first " << limit << " ASCII character values is " << int_result << endl << endl; 
                    break; 

                // If the user wants to do NIUchant
                case 4:
                    cout << "How many words will be iterated from the NIU Chant? (3 - 50): ";
                    cin >> limit;
                    while (limit < 3 || limit > 50) {
                        cout << limit << " is an invalid value. Try again: ";
                        cin >> limit;
                    }
                    NIUchant(limit);
                    break;
            }
        }
        } while (!flag);

    return EXIT_SUCCESS;
}

int Menu() {

    // Variable for users input
    int choice{0};


    // Select
    cout << "Objectives" << endl << endl 
        << "1) Calculate the sum of the first N squared numbers." << endl
        << "2) Calculate the average of the first N cubed numbers." << endl
        << "3) Calculate the sum of the ASCII value of the first N characters." << endl
        << "4) Word iterations from the NIU school chant." << endl << endl
        << "5) Quit" << endl << endl
        << "Enter your choice: ";
    cin >> choice;

    return choice;

}

// Function II
/***************************************************************
Function: Get value

Use: Lets the user enter a prompt and some bounds, 
the prompt is then displayed and we check to make sure 
the input is within the bonuds 

Arguments: A string for the users prompt, and two integers for the bounds

Returns: an integer representing the users value

Notes:
***************************************************************/
int getValue( string prompt, int lowerBound, int upperBound ) {

    int value;

    // Gather user value
    cout << prompt << " " << lowerBound << " - " << upperBound << ": ";
    cin >> value;

    // Prevent invalid choices
    while (value < lowerBound || value > upperBound) {
        cout << "Invalid value" << endl;
        cout << prompt << " " << lowerBound << " - " << upperBound << ":";
        cin >> value;
    }
    return value;
}

// Function III
/***************************************************************
Function: Sum of squares

Use: Compute the sum of the squares from n - provided limit

Arguments: an integer representing the upper bound

Returns: an integer representing the sum of the squares

Notes:
***************************************************************/
int sumOfSquares( int limit ) {

    // Variable that will house our result
    int res{0};

    // Loop from i=1 to users limit, squaring the terms
    for (int i=1; i <= limit; ++i) res+=(i*i);

    // Return the result
    return res;

}


// Function IV
/***************************************************************
Function: Average of cubes

Use: compute the average of the cubes of n - provided limit

Arguments: an integer representing the uppper bound

Returns: an integer representing the average of all the cubes

Notes:
***************************************************************/
double averageOfCubes( int limit ) {

    double res{0};

    // Sigma_{0}^{limit} i^{3}
    for (int i{0}; i < limit; ++i) {
        res+=(i*i*i);
    }

    return res / limit;
}

// Function V
/***************************************************************
Function: Sum of Ascii 

Use: Summation of characters ascii numbers

Arguments: An integer, when added to the ascii value of either a or A, we get the character to stop at 

Returns: an integer, representing the sum of ascii codes form a-(char) lim

Notes: 
***************************************************************/
int sumOfASCII( int limit ) {

    int res{0};
    char userin{' '};

    // Get option from the user
    cout << "Would you like to summate (L)owercase or (U)ppercase characters? ";
    cin >> userin;

    // These loop from a to whatever character our limit is with super cool person syntax
    if (userin == 'L') {
        for (char i{'a'}; i < 'a' + (char) limit; ++i) { res+= (int) i; } 

    } else if (userin == 'U') {
        for (char i{'A'}; i < 'A' + (char) limit; ++i) { res+= (int) i; }
    } 
    return res;
}

// Function VI
/***************************************************************
Function: NIU Chant Displayer

Use: Display the NIU chant n times

Arguments: An integer representing the number of words to display

Returns: nihil

Notes: Use a technique that involves indexing a array (word list), 
if the list is exhausted, we reset the index position back to zero.
Once the counter reaches the specified bound, we stop the loop.
Created an extra special if statement to prevent an extra space 
being displayed after the very last word
***************************************************************/
void NIUchant(int iterations) {
    
    // Control variables
    int index{0}, counter{0};

    // Word list
    const int SIZE = 3;
    string words[3] = {"Forward!", "Together,", "Forward!"};

    // Handle our outputs
    while (counter < iterations) {
        // Handle potential bounds error
        if (index == SIZE) { index = 0; }

        // Handle extra space for the last word
        if ( counter == iterations -1) { cout << words[index]; }

        // If its not the last iteration, we can add a space
        else { cout << words[index] << " "; }

        // Increment
        ++index;
        ++counter;
    }
    cout << endl << endl;

}
