/***************************************************************
CSCI 240         Program      Fall 2023

Programmer: Nathan Warner
 
Section: 001

Date Due: 

Purpose: 
***************************************************************/
#include <iostream>
#include <iomanip>
#include <cstdlib>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;


int main(int argc, const char *argv[]) {

    double price, total_price;
    int num_items;



    cout << "What is the price for a single item? ";
    cin >> price;

    cout << "How many items were purchased? ";
    cin >> num_items;

    total_price = price * num_items;

    cout << std::fixed << std::setprecision(2);
    cout << endl << std::right << std::setw(5) << num_items
        << " items at $" << price
        << " each will cost "
        << "$" << total_price << endl;




    return EXIT_SUCCESS;
}
