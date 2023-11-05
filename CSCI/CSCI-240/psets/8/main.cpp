/***************************************************************
CSCI 240         Program 8     Fall 2023

Programmer: Nathan Warner
 
Section: 001

Date Due: November 10

Purpose:  For this assignment, implement a class called Date that will be used to represent a single calendar day, including the day of the week, month, and year.
***************************************************************/
#include <iostream>
#include <iomanip>
#include <cstdlib>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;

const string valid_months[] = {"January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December"
    }

const string valid_days[] = {"31",
        "28",
        "31",
        "30",
        "31",
        "30",
        "31",
        "31",
        "30",
        "31",
        "30",
        "31"
    }
class Date {

private:
    int day, year;
    string month;


};

int main(int argc, const char *argv[]) {

    return EXIT_SUCCESS;
}
