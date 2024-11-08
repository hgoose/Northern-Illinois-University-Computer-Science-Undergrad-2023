/***************************************************************
CSCI 240         Program 8     Fall 2023

Programmer: Nathan Warner
 
Section: 001

Date Due: November 10

Purpose:  For this assignment, implement a class called Date that will be used to represent a single calendar day, including the day of the week, month, and year.
***************************************************************/

// RESUBMIT: SORRY, FORGOT STRING HEADER 

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>

#ifndef SHOW
#define SHOW(a) cout << a << endl
#endif

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;

#ifndef AR_S
#define AR_S 12
#endif

#ifndef DAYS
#define DAYS 7
#endif

#ifndef NOPOS
#define NOPOS -1
#endif

// Function declarations
int getMonthNumber(string month);
int findLeaps(int year);

// Structure to hold our global variables
struct GlobalState {
    static const string valid_months[AR_S];
    static const int valid_days[AR_S];
    static const string day_names[DAYS];
};

// Main class
class Date {

// Privates 
private:
    int day, year;
    string month;

// Publics
public:
    // Member Function Declarations
    void set_date( int newDay, string newMonth, int newYear );
    string get_day_name() const;
    string get_day() const;
    string get_month() const;
    int get_year() const;
    string get_date() const;


    // Function I
    /***************************************************************
    Function: Default constructor
    
    Use: Used to create objects with default (in this case random) member values
    
    Arguments: none
    
    Returns: none (builds objects)
    
    Notes: 
    ***************************************************************/
    Date() {
        int tmpmonth=0;  //  Useful for indexing our valid_monts array

        // Generate number for year member [1000, 2024]
        this->year = 1000 + (rand() % (2024-1000+1));

        // Generate number for month member [0-11]
        tmpmonth = rand() % 12;
        this->month = GlobalState::valid_months[tmpmonth];

        // Generate number for day member (Dependent on month)
        if ( (this->month=="February") && (findLeaps(this->year) == 1)) {  // Handles case in which we have a leap year (and in the month of feb)
            this->day = 1 + (rand() % 29);
        } else { // No leap year
            this->day = 1 + (rand() % (GlobalState::valid_days[tmpmonth]));
        }
    }

    // Function II
    /***************************************************************
    Function: Dependent constructor

    Use: Used to create objects with custom arguments

    Arguments: Integer for day number, String for month name, and integer for the year

    Returns: None (builds objects)

    Notes: 
    ***************************************************************/ 
    Date(int day, string month, int year) {
        this->day = day;
        this->month = month;
        this->year = year;
    }
};

// Array to hold the names of valid months
const string GlobalState::valid_months[AR_S] = {
    "January", "February", "March", "April",
    "May", "June", "July", "August",
    "September", "October", "November", "December"
};

// Array to hold number of days in each month
const int GlobalState::valid_days[AR_S] = {
    31, 28, 31, 30,
    31, 30, 31, 31,
    30, 31, 30, 31
};

// Array to hold the names of the week
const string GlobalState::day_names[DAYS] = {
    "Monday", "Tuesday", "Wednesday",
    "Thursday", "Friday", "Saturday", "Sunday"
};

int main(int argc, const char *argv[]) {
    /* Entry */

    srand(17);

    // Instantiations
    Date d1, d2;
    Date d3(10, "December", 1815);


    /*                          Tests                                  */
    /* ---------------------------------------------------------------- */

    cout << "Test 1: Constructors and get_date method" << endl << endl
        << "The first date is " << d1.get_date() << endl
        << "The second date is " << d2.get_date() << endl
        << "The third date is " << d3.get_date() << endl << endl;

    
    d1.set_date(9, "December", 1906);
    cout << "Test 2: set_date method" << endl << endl
        << "  Grace Hopper's birthday is "
        << d1.get_date() << endl << endl;

    d2.set_date(29, "February", 2023);
    cout << "Test 3a: set_date method with invalid values." << endl << endl
        << " This should print as Feb. 1st: " 
        << d2.get_date() << endl << endl;

    d2.set_date(29, "February", 2020);
    cout << "Test 3b: set_date method that tests leap year recognition." << endl << endl
        << "  Leap Year! "
        << d2.get_date() << endl << endl;

    d3.set_date(14, "Jupiter", 1011);
    cout << "Test 4: set_date method with a made-up month." << endl << endl
        << "  This should default to January: "
        << d3.get_date() << endl << endl;

    d1.set_date(12, "March", 1999);
    cout << "Test 5a: testing whether '12' comes back as '12th' and not '12nd'." << endl << endl 
        << "   First date == " 
        << d1.get_day() << endl << endl;

    d1.set_date(23, "March", 1999);
    cout << "Test 5b: testing whether '23' comes back as '23rd' and not '23th'." << endl << endl
        << "  First date == " 
        << d1.get_day() << endl << endl;

    d3.set_date(26, "February", 1982);
    cout << "Test 6: testing for mapping the 26th day of the month to a Friday." << endl << endl
        << "  There's a 1 in 7 chance this is the actual day Brian Shaw was born... "
        << d3.get_day_name() << endl;


    return EXIT_SUCCESS;
}


// Function III
/***************************************************************
Function: getMonthNumber

Use: Gets the corresponding month number given a month name

Arguments: String for month name

Returns: an integer representing the month number

Notes: 
***************************************************************/
int getMonthNumber(string month) {

    // Gets the number of month from month name
    for (int i=0; i< AR_S; ++i) {
            if (month == GlobalState::valid_months[i]) return i;
    }
    // IF we didnt find a match
    return NOPOS;
     
}

// Function  IV
/***************************************************************
Function: Findleaps

Use: Use to determine if a year is a leap year

Arguments: Integer for the year number

Returns: Unsigned integral ? 1 : NOPOS 

Notes: 
***************************************************************/
int findLeaps(int year) {
    
    // Algorithm to find the leap years given a specific year [1000-2024]
    
    /*<summary> 
        <li> If the year is divisible by 400, it is automatically a leap year, we check this first
        <li> If the year is divisible by 4 but not by 100, it is a leap year 
        <li> rv: 1 -> leap year
        <li> rv: NPOS -> no leap year
    </summary>*/
    if ( year % 400 == 0) { // Heres the check for 400
            return 1;
    } else if ( year % 4 == 0) { // We check for 4
            if (year % 100 == 0) { // Make sure its not also 100
                    return NOPOS;
            } else {
                    return 1;
            }
    } else {
            return NOPOS;
    }

}

// Function VI
/***************************************************************
Function: set_date

Use: Used to set the values of the class members

Arguments: Integer for day, string for month, and integer for year

Returns: void

Notes: 
***************************************************************/
void Date::set_date( int newDay, string newMonth, int newYear ){ 
    bool found = false; // Useful flag
    // Step through our global month array, so that we can find matches
    for (int i=0; i<AR_S; ++i) {
        // If we find a match, set the class member
        if (newMonth == GlobalState::valid_months[i]) {
                this->Date::month = newMonth;
                found=true; // Update flag
        } 
    }
    // If we dont have a valid month... Default to Jan
    if (!found) this->Date::month = GlobalState::valid_months[0];  

    // Check if argument year is within the valid range, if so we update the class member
    if (!(newYear < 1000 || newYear > 2024)){
            this->Date::year = newYear;
    
    // If its not valid... We default to 1999
    } else {
            this->Date::year = 1999;
    }
    
    // If we have a leap year, make sure we have the range be [1,29]
    if ( newMonth == "February" && findLeaps(this->Date::year) == 1 ) {
        // Make sure we are within the required range
        if ( !(newDay < 1 || newDay > 29) ) {
                this->Date::day = newDay; // Update member
        } else {
                this->Date::day = 1; // Not within the range
        }
    // Not worried about leap year, just need range for the month we have
    } else if ( !(newDay < 1 || newDay > GlobalState::valid_days[getMonthNumber(this->Date::month)]) ) { // This makes sure we are within the bounds for the given month
            this->Date::day = newDay;
    } else {
            this->Date::day = 1; // Not within the range
    }
}

// Function VII
/***************************************************************
Function: get_day_name

Use: Gets the name of the day 

Arguments: none

Returns: string for the name of the day

Notes: 
***************************************************************/
string Date::get_day_name() const { 
    // Ternary and modular arithmetic to get the name of the day 
    /*<remark>  
        The modular arithemtic logic essentially turns some less than ideal number to the corresponding 
        position in the first week, so we can just focus on numbers [0-6] (to index our day name array)
    </remark>*/
    return this->day % 7 ? GlobalState::day_names[((this->day)%7)-1] : "Sunday";  // This last part returns "sunday" if the day number is a multiple of 7
}

// Function VIII
/***************************************************************
Function: get_day

Use: Sets the suffix for the day number

Arguments: none

Returns: string for the built day number

Notes: 
***************************************************************/
string Date::get_day() const { 

    /*<summary> 
        The only days that do not have the suffix "th" are the days 1,2,3,21,22,23
        so we check for those. Otherwise, we can add "th"
    </summary>*/
    if (
        this->day == 1 ||
        this->day == 21 
    ) { return std::to_string(this->day) + "st";
    } else if (
            this->day == 2 || 
            this->day == 22
    ) { return std::to_string(this->day)  + "nd";
    } else if (
            this->day == 3 ||
            this->day == 23
    ) { return std::to_string(this->day) + "rd"; 
    } else {
        return std::to_string(this->day)  + "th";
    }
}

// Function IX
/***************************************************************
Function: get_month

Use: Gets the month member

Arguments: none

Returns: string for the month member

Notes: 
***************************************************************/
string Date::get_month() const { 
    return this->month;
}

// Function X
/***************************************************************
Function: get_year

Use: Gets the year 

Arguments: none

Returns: integer for year number

Notes: 
***************************************************************/
int Date::get_year() const {
    return this->year;
}

// Function 
/***************************************************************
Function: XI

Use: Used to build the repr

Arguments: none

Returns: Repr string

Notes: 
***************************************************************/
string Date::get_date() const { 
    return this->get_day_name() 
        + " "
        + this->get_month() 
        + " "
        + this->get_day() 
        + ", "
        + std::to_string(this->get_year());
}
