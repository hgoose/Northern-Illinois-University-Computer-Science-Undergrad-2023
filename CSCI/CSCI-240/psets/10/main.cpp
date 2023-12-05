/***************************************************************
CSCI 240         Program 10     Fall 2023

Programmer: Nathan Warner
 
Section: 001

Date Due: December 8

Purpose: Utilize various tools and algorithms discussed throughout the semester together with class implementation to create and sort reports on powerlifters.
***************************************************************/
#include <iostream> // For input/output tasks
#include <iomanip> // For input/output manipulators
#include <cstdlib> // For random, system, exit, EXIT_SUCCESS, and EXIT_FAILURE
#include <fstream>
// #include <cstdint> // For fixed width data types
#include <unistd.h> // Posix API
#include <typeinfo> // typeid(n).name()
#include <cctype> // For character functions
#include <algorithm> // Defined algorithms
#include <iterator> // Iterator functions and types
#include <string> // String class
#include <cstring> // For c-string functions

// Some macros
#define a_sizeof(x) sizeof(x) / sizeof(x[0])
#define show(a) cout << a << endl;
#define SHOW_AR(a) for (const auto& i : a) cout << i << " "; cout << endl;
#define NOPOS -1
#define LINE_BREAK cout << endl; for (int i = 0; i < 96; i++) cout << "-"; cout << endl;
#define NAME_MAXSIZE 15
#define N_HEAD 8
#define STRING_JUST 18
#define NUMERIC_JUST 10
#define TITLE_JUST 37
#define PROC_COMPLETE(a) cout << "File processing has been complete. We have " << a << " powerlifters recorded." << endl << endl << endl;

// Using
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;

// Symbolic Constant
const char* HEADS[N_HEAD] =  {
    "First Name", "Last Name", "Wilks",
    "Squat", "Bench", "DL", 
    "Total", "W. Score"
};
const char TITLE_DEFAULT[] = "Default List of Powerlifters";
const char TITLE_TOTAL[] = "Powerlifters Ranked by Total";
const char TITLE_WILKS[] = "Powerlifters Ranked by Wilks";
const char TITLE_SQUAT[] = "Powerlifters Ranked by Squat";
const char TITLE_BENCH[] = "Powerlifters Ranked by Bench";
const char TITLE_DEADLIFT[] = "Powerlifters Ranked by Deadlift";

class PowerLifter {
    // Private Members:
    char fname[NAME_MAXSIZE];
    char lname[NAME_MAXSIZE];
    float wilks;
    int maxsquat;
    int maxbench;
    int maxdeadlift;

    // Public method declarations
public:
    PowerLifter(); 
    void setFirst(const char[]);
    void setLast(const char[]);
    void setCoef(float);
    int getSquat();
    void setSquat(int);
    int getBench();
    void setBench(int);
    int getDeadlift();
    void setDeadlift(int);
    int getTotal();
    int wilksScore();
    int compare(PowerLifter&);
    void display();

};

// Function Declarations
void sortBy(PowerLifter[], int, const char[]);
void swap( PowerLifter&, PowerLifter&);
int readFile(PowerLifter[], const char[]);
void printPowerLifters(PowerLifter[], int, const char[]);

// Entry
int main(int argc, const char *argv[]) {

    // Create and build our array
    PowerLifter par[30];
    int count = readFile(par, "lifters.txt");

    // Use the functions and methods
    PROC_COMPLETE(count)
    printPowerLifters(par, count, TITLE_DEFAULT);
    sortBy(par,count,"Total");
    printPowerLifters(par, count, TITLE_TOTAL);
    sortBy(par,count,"Wilks");
    printPowerLifters(par, count, TITLE_WILKS);
    sortBy(par,count,"Squat");
    printPowerLifters(par, count, TITLE_SQUAT);
    sortBy(par,count,"Bench");
    printPowerLifters(par, count, TITLE_BENCH);
    sortBy(par,count,"Deadlift");
    printPowerLifters(par, count, TITLE_DEADLIFT);
    
    // Exit
    return EXIT_SUCCESS;
}

// Function I
/***************************************************************
Function: PowerLifter default constructor

Use: Create powerlifter objects with default values

Arguments: None

Returns: None

Notes: 
***************************************************************/
PowerLifter::PowerLifter() : wilks(1), maxsquat(-1), maxbench(-1), maxdeadlift(-1) {

    // Create two C-Strings for default first and last name
    const char* fnametmp = "no";
    const char* lnametmp = "name";

    // Copy those default values into data members for first and last name
    strncpy(this->fname, fnametmp, NAME_MAXSIZE);
    strncpy(this->lname, lnametmp, NAME_MAXSIZE);
}

// Function II
/***************************************************************
Function: SetFirst

Use: Sets the first name of the powerlifter object

Arguments: C-string for first name

Returns: void

Notes: 
***************************************************************/
void PowerLifter::setFirst(const char newFirst[]) {
    // We just copy the passed in c-string to our data member
    strncpy(this->fname, newFirst, NAME_MAXSIZE);
}

// Function III
/***************************************************************
Function: setLast

Use: Sets the last name of the powerlifter object

Arguments: C-string for last name

Returns: void

Notes: 
***************************************************************/
void PowerLifter::setLast(const char newLast[]) {

    // We just copy the passed in c-string to our data member
    strncpy(this->lname, newLast, NAME_MAXSIZE);
}

// Function IV
/***************************************************************
Function: getSquat

Use: Returns the data member for the max squat

Arguments: None

Returns: Integer which holds the value of the squat data member

Notes: 
***************************************************************/
int PowerLifter::getSquat() {
    return this->maxsquat;
}

// Function V
/***************************************************************
Function: setSquat

Use: Sets the data member for max squat

Arguments: integer value for max squat value

Returns: void

Notes: 
***************************************************************/
void PowerLifter::setSquat(int newSquat) {

    // Here we make sure that the new max squat value is valid (at least zero), then we set the data member
    if ( newSquat > -1 ) {
        this->maxsquat = newSquat;
    } 
}

// Function VI
/***************************************************************
Function: getBench

Use: Returns the data member for the max bench

Arguments: None

Returns: Integer which holds the value of the bench data member

Notes: 
***************************************************************/
int PowerLifter::getBench() {
    return this->maxbench;
}

// Function VII
/***************************************************************
Function: setBench

Use: Sets the data member for max bench

Arguments: integer value for max bench value

Returns: void

Notes: 
***************************************************************/
void PowerLifter::setBench(int newBench) {

    // Here we make sure that the new max bench value is valid (at least zero), then we set the data member
    if ( newBench > -1 ) {
        this->maxbench = newBench;
    }
}

// Function VIII
/***************************************************************
Function: getDeadlift

Use: Returns the data member for the max deadlift

Arguments: None

Returns: Integer which holds the value of the deadlift data member

Notes: 
***************************************************************/
int PowerLifter::getDeadlift() {
    return this->maxdeadlift;
}

// Function IX
/***************************************************************
Function: setDeadlift

Use: Sets the data member for max deadlift

Arguments: integer value for max deadlift value

Returns: void

Notes: 
***************************************************************/
void PowerLifter::setDeadlift(int newDeadlift) {
    if ( newDeadlift > -1 ) {
        this->maxdeadlift = newDeadlift;
    }
}

// Function X
/***************************************************************
Function: getTotal

Use: Returns the summation of the three maxes

Arguments: None

Returns: Integer for the sum of the three movements

Notes: 
***************************************************************/
int PowerLifter::getTotal() {
    return this->maxsquat + this->maxbench + this->maxdeadlift;
}


// Function XI
/***************************************************************
Function: setCoef

Use: Sets the data member for the wilks coefficient

Arguments: Float for the new wilks coefficient

Returns: void

Notes: 
***************************************************************/
void PowerLifter::setCoef(float newCoef) {
    if ( newCoef >= 0 && newCoef < 2) {
        this->wilks = newCoef;
    }
}

// Function XII
/***************************************************************
Function: wilksScore

Use: Computes the value of the wilksScore

Arguments: None

Returns: Integer for the wilks score

Notes: 
***************************************************************/
int PowerLifter::wilksScore() {
    
    // Here we just multiply the total by the wilks coefficient then cast the result to an integer
    return static_cast<int>(this->getTotal() * this->wilks);
}

// Function XIII
/***************************************************************
Function: compare

Use: compares the wilks score between two objects

Arguments: Reference to some other object

Returns: Integer: 
        0: If they are the same
        -1: if a < b 
        1: if a > b

Notes: 
***************************************************************/
int PowerLifter::compare(PowerLifter& other) {

    // Simple double ternary to deduce which value to return
    return (this->wilks == other.wilks ? 0 : (this->wilks < other.wilks ? -1 : 1));
}

// Function XIV
/***************************************************************
Function: display

Use: Displays formatted object data members

Arguments: None

Returns: void

Notes: 
***************************************************************/
void PowerLifter::display() {
    cout << std::setw(STRING_JUST) << this->fname 
        << std::setw(STRING_JUST) << this->lname 
        << std::fixed << std::setprecision(4) << std::setw(NUMERIC_JUST) << this->wilks 
        << std::setw(NUMERIC_JUST) << this->maxsquat
        << std::setw(NUMERIC_JUST) << this->maxbench
        << std::setw(NUMERIC_JUST) << this->maxdeadlift
        << std::setw(NUMERIC_JUST) << this->getTotal()
        << std::setw(NUMERIC_JUST) << this->wilksScore() << endl;
}

// Function XV
/***************************************************************
Function: sortBy

Use: Sorts the objects in our object array based on each attribute (selection sort)

Arguments: obj array, size of array, type to sort by

Returns: void

Notes: 
***************************************************************/
void sortBy(PowerLifter array[], int size, const char type[]) {

    // Logic for each sort is the same, only difference is the attribute to sort by
    int max;
    if (!strcmp(type, "Squat")) { // Strcmp to make sure we are sorting by the correct attribute
    // Logic: Double for loop to check item at index j against the rest of the array, if we find a value smallar than the one at idx j, we take note with the max variable
    for (int j=0; j<size; ++j) {
        max = j; // Assume the value at position j is the max
        for (int k=j+1; k<size; ++k) {
            if (array[k].getSquat() > array[max].getSquat()) { // Comparison
                max = k;
            }
        }
        swap(array[j], array[max]); // After the outer loop has completed its iteration and found the lesser value, we perform the swap
    }
    } else if (!strcmp(type, "Bench")) {
        for (int j=0; j<size; ++j) {
            max = j;
            for (int k=j+1; k<size; ++k) {
                if (array[k].getBench() > array[max].getBench()) {
                    max = k;
                }
            }
            swap(array[j], array[max]);
        }
    } else if (!strcmp(type, "Deadlift")) {
        for (int j=0; j<size; ++j) {
            max = j;
            for (int k=j+1; k<size; ++k) {
                if (array[k].getDeadlift() > array[max].getDeadlift()) {
                    max = k;
                }
            }
            swap(array[j], array[max]);
        }
    } else if (!strcmp(type, "Total")) {
        for (int j=0; j<size; ++j) {
            max = j;
            for (int k=j+1; k<size; ++k) {
                if (array[k].getTotal() > array[max].getTotal()) {
                    max = k;
                }
            }
            swap(array[j], array[max]);
        }
    } else if (!strcmp(type, "Wilks")) {
        for (int j=0; j<size; ++j) {
            max = j;
            for (int k=j+1; k<size; ++k) {
                if (array[k].wilksScore() > array[max].wilksScore()) {
                    max = k;
                }
            }
            swap(array[j], array[max]);
        }
    }
}

// Function XVI
/***************************************************************
Function: Swap

Use: Helper function to facilitate the swap in the function above

Arguments: two references to powerlifter objects

Returns: void

Notes: 
***************************************************************/
void swap(PowerLifter& val1, PowerLifter& val2) {
    PowerLifter tmp = val1;
    val1=val2;
    val2=tmp;
}

// Function XVII
/***************************************************************
Function: readFile

Use: Used to read the lifters.txt data sheet, and build our powerlifter array.

Arguments: obj array and filename

Returns: Integer for the count of insertertions

Notes: 
***************************************************************/
int readFile( PowerLifter array[], const char fileName[] ) {

    // Create our file object and open the file
    std::ifstream file(fileName);

    // Variables to house the file contents
    char fname[NAME_MAXSIZE];
    char lname[NAME_MAXSIZE];
    float wilks;
    int squat, bench, deadlift, count=0;


    // While we have data to read...
    while (file >> fname >> lname >> wilks >> squat >> bench >> deadlift) {
        // Create a powerlifter object
        PowerLifter pn;

        // Set the values for the object, get the total and wilks score, etc...
        pn.setFirst(fname);
        pn.setLast(lname);
        pn.setCoef(wilks);
        pn.setSquat(squat);
        pn.setBench(bench);
        pn.setDeadlift(deadlift);
        pn.getTotal();
        pn.wilksScore();

        // Append the object to the arary
        array[count] = pn;

        // Update the count
        ++count;
    }

    return count;
}

// Function XVIII
/***************************************************************
Function: printPowerLifters

Use: Prints the message that displays how many objects we created from the file contents, prints the header and column names, 
then displays the values for each object

Arguments: Powerlifter array, size of array, title for output

Returns: void

Notes: 
***************************************************************/
void printPowerLifters( PowerLifter array[], int size, const char title[] ) {

    // Display the formatted title
    cout << std::setw(TITLE_JUST + strlen(title)) << title << endl;

    // Simple loop to display each column name
    for (int i=0; i<N_HEAD; ++i) {
        if ( i < 2 ) {
            cout << std::right << std::setw(STRING_JUST) << HEADS[i];
        } else {
            cout << std::setw(NUMERIC_JUST) << HEADS[i];
        }
    }
    LINE_BREAK

    // Display the contents
    for (int i=0; i<size; ++i) {
        array[i].display();
    }
    cout << endl << endl;
}
