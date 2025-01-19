/***************************************************************
CSCI 240         Program 3     Fall 2023

Programmer: Nathan Warner
 
Section: 001

Date Due: 9-22

Purpose: write a program that will demonstrate how income tax is applied towards various 
levels of income, i.e. what are tax brackets and why making $1 enough into a higher tax bracket doesn't
immediately see you paying substantially more in income tax.
***************************************************************/

// Includes
#include <iostream>
#include <iomanip>
#include <cstdlib>

// STD Members
using std::cout;
using std::cin;
using std::endl;

// Entry
int main(int argc, const char *argv[]) {
    // Init needed doubles
    double gross_income, income_tax;

    // Declare and Init Symbolic Constants
    const float B1_RATE = .1,
          B2_RATE = .12,
          B3_RATE = .22,
          B4_RATE = .24;

    const int B1_MAX = 1100,
        B2_MAX = 4047,
        B3_MAX = 11143;

    // Input Stream to collect gross income
    cout << "What is your gross income? " << endl;
    cin >> gross_income;

    // Handle Negative Inputs
    if (gross_income < 0) {
        std::cerr << "Invalid Input" << endl; return EXIT_FAILURE;
    }

    // Main logic for computing income tax
    if (gross_income >= 95375) {
        income_tax = (gross_income - 95375) * B4_RATE + B3_MAX + B2_MAX + B1_MAX;

    } else if (gross_income >= 44725) {
        income_tax = (gross_income - 44725) * B3_RATE + B2_MAX + B1_MAX;

    } else if (gross_income >= 11000){
        income_tax = (gross_income - 11000) * B2_RATE + B1_MAX;

    } else {
        income_tax = gross_income * B1_RATE;
    }

    // Set rounding
    cout << std::fixed << std::setprecision(2); 

    // Output Table (Formatted)
    cout << endl << std::left << std::setw(20) << "Gross Income: " 
        << "$" << gross_income << endl;

    cout << std::left << std::setw(20) << "Income Tax: " 
        << "$" << income_tax << endl;

    // SYS EXIT
    return EXIT_SUCCESS;
}
