/***************************************************************
CSCI 240         Program 1     Fall 2023

Programmer: Nathan Warner

Section: 0001

Date Due: Sep 8, 2023

Purpose: This program calculates and displays the profit per value
  of harvested crops as done in farming simulation video games.
***************************************************************/
#include <iostream>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;

int main() {
    // Declare variables needed for the program
    int seed_cost;
    int mature_time;
    int resale_value;

    // Recieve input for seed cost and store in var
    cout << "How much does this seed cost to buy? ";
    cin >> seed_cost;

    // Recieve input for mature_time cost and store in var
    cout << "How long does this crop take to mature? ";
    cin >> mature_time;

    // Recieve input for resale_value and store in var
    cout << "What is the expected resale value of the mature crop? ";
    cin >> resale_value;


    // Init profit var and compute profit
    float profit;
    profit = resale_value - seed_cost;


    // Init profit per day var and compute expected profit per day
    float profit_per_day;
    profit_per_day = profit / mature_time;

    // output stream for result
    cout << "The projected profit per day value of this crop is: " << profit_per_day << endl;

    // Exit Success
    return 0;
}
