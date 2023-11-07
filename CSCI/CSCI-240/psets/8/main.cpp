/***************************************************************
CSCI 240         Program 8     Fall 2023

Programmer: Nathan Warner
 
Section: 001

Date Due: November 10

Purpose:  For this assignment, implement a class called Date that will be used to represent a single calendar day, including the day of the week, month, and year.
***************************************************************/

// TODO: Add documentation

#include <iostream>
#include <iomanip>
#include <cstdlib>

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


struct GlobalState {
    static const string valid_months[AR_S];
    static const int valid_days[AR_S];
    static const string day_names[DAYS];
};

class Date {
private:
    int day, year;
    string month;
public:
    // Member Function Declarations
    void set_date( int newDay, string newMonth, int newYear );
    string get_day_name() const;
    string get_day() const;
    string get_month() const;
    int get_year() const;
    string get_date() const;


    // Base Constructor
    Date() {
        int tmpmonth=0;

        this->year = 1000 + (rand() % (2024-1000+1));

        tmpmonth = rand() % 12;
        this->month = GlobalState::valid_months[tmpmonth];

        if ( (this->month=="February") && (findLeaps(this->year) == 1)) {
            this->day = 1 + (rand() % 29);
        } else {
            this->day = 1 + (rand() % (GlobalState::valid_days[tmpmonth]));
        }
    }

    // Alt constructor
    Date(int day, string month, int year) {
        this->day = day;
        this->month = month;
        this->year = year;
    }
};

const string GlobalState::valid_months[AR_S] = {
    "January", "February", "March", "April",
    "May", "June", "July", "August",
    "September", "October", "November", "December"
};

const int GlobalState::valid_days[AR_S] = {
    31, 28, 31, 30,
    31, 30, 31, 31,
    30, 31, 30, 31
};

const string GlobalState::day_names[DAYS] = {
    "Monday", "Tuesday", "Wednesday",
    "Thursday", "Friday", "Saturday", "Sunday"
};



int main(int argc, const char *argv[]) {

    srand(17);

    Date d1, d2;
    Date d3(10, "December", 1815);

    cout << "Test 1: Constructors and get_date method" << endl << endl
        << "The first date is " << d1.get_date() << endl
        << "The second date is " << d2.get_date() << endl
        << "The third date is " << d3.get_date() << endl << endl;

    
    d1.set_date(9, "December", 1906);
    cout << "Test 2: set_date method" << endl << endl
        << "  Grace Hopper's birthday is"
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

int getMonthNumber(string month) {

    for (int i=0; i< AR_S; ++i) {
            if (month == GlobalState::valid_months[i]) return i;
    }
    return NOPOS;
     
}

int findLeaps(int year) {
    
    if ( year % 400 == 0) {
            return 1;
    } else if ( year % 4 == 0) {
            if (year % 100 == 0) {
                    return NOPOS;
            } else {
                    return 1;
            }
    } else {
            return NOPOS;
    }

}

void Date::set_date( int newDay, string newMonth, int newYear ){ 
    int idx = 0;
    bool found = false;
    for (int& i=idx; i<AR_S; ++i) {
            if (newMonth == GlobalState::valid_months[i]) {
                    this->Date::month = newMonth;
                    found=true;
            } 
    }
    if (!found) this->Date::month = GlobalState::valid_months[0];  // Jan

    if (!(newYear < 1000 || newYear > 2024)){
            this->Date::year = newYear;
    } else {
            this->Date::year = 1999;
    }
    
    if ( newMonth == "February" && findLeaps(this->Date::year) == 1 ) {
            if ( !(newDay < 1 || newDay > 29) ) {
                    this->Date::day = newDay;
            } else {
                    this->Date::day = 1;
            }
    } else if ( !(newDay < 1 || newDay > GlobalState::valid_days[getMonthNumber(this->Date::month)]) ) {
            this->Date::day = newDay;
    } else {
            this->Date::day = 1;
    }
}
string Date::get_day_name() const { 
    return this->day % 7 ? GlobalState::day_names[((this->day)%7)-1] : "Sunday"; // Modular arithemtic is such a beautiful concept
}
string Date::get_day() const { 
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
string Date::get_month() const { 
    return this->month;
}
int Date::get_year() const {
    return this->year;
         
}
string Date::get_date() const { 
    return this->get_day_name() 
        + " "
        + this->get_month() 
        + " "
        + this->get_day() 
        + ", "
        + std::to_string(this->get_year());
}

