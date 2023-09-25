/***************************************************************
CSCI 240         Program 1     Fall 2023

Programmer: Nathan Warner
 
Section: 001

Date Due: September 15, 2023

Purpose:  Write a program to calculate a powerlifter's total and formatting the output into a report.
***************************************************************/
#include <iostream>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;

int main(int argc, char *argv[]) {

    // Init  Needed Numeric Variables
    int max_squat, max_bench, max_deadlift, sum_maxes;
    float wilks_score;

    // Init Constants
    const float wilks_co = 0.5976;
    const int alloc_leftspaces = 20, alloc_rightspaces = 8;

    // Input Stream, storing in initialized variables
    cout << "What is your max squat? ";
    cin >> max_squat;

    cout << "What is your max bench press? ";
    cin >> max_bench;

    cout << "What is your max deadlift? ";
    cin >> max_deadlift;


    // Output for max scores (Formated)
    cout << endl << std::left << std::setw(alloc_leftspaces) << "Max Squat: "
        << std::right << std::setw(alloc_rightspaces)
        << max_squat << endl;

    cout << std::left << std::setw(alloc_leftspaces) << "Max Bench Press: "
        << std::right << std::setw(alloc_rightspaces)
        << max_bench << endl;

    cout << std::left << std::setw(alloc_leftspaces) << "Max Deadlift: "
        << std::right << std::setw(alloc_rightspaces)
        << max_deadlift << endl;


    // Computations for Powerlifting Total and Wilks Score
    sum_maxes = (max_squat + max_bench + max_deadlift);
    wilks_score = (sum_maxes * wilks_co);


    // Output for Powerlifting total and wilks score (Formated)
    cout << endl << std::left << std::setw(alloc_leftspaces) << "Powerlifting Total: "
        << std::right << std::setw(alloc_rightspaces)
        << sum_maxes << endl;

    cout << std::left << std::setw(alloc_leftspaces) << "Wilks Score: "
        << std::right << std::setw(alloc_rightspaces)
        << std::fixed << std::setprecision(3)
        << wilks_score << endl;

    return 0;
}
