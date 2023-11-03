/***************************************************************
CSCI 240         Program 7     Fall 2023

Programmer: Nathan Warner
 
Section: 001

Date Due: 11-3-23

<Purpose>
Write a program that will process information regarding the profits to be earned from 
planting, nurturing, and selling crops such as is commonly done in farming simulation games such 
as Stardew Valley. Each crop will be described by the season in which they can be grown (Spring, 
Summer, and Fall), their name, the cost of their seed, the expected gold from the mature crops 
sale, and the number of days required for the crops to mature.
</Purpose>
***************************************************************/
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>

// PARALLEL ARRAY SIZE
#ifndef PA_S
#define PA_S 30
#endif

// COLUMN LENGTH
#ifndef COL_L
#define COL_L 16
#endif

// ROW WIDTH
#ifndef ROW_W
#define ROW_W 6
#endif

// ERROR OPENING FILE ERR MESSAGE
#ifndef FILE_ERR
#define FILE_ERR cerr << "Program terminated with exit code 1: Error opening file, no file named crops.txt" << endl 
#endif

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;

// FUNCTION PROTOTYPES
int build(string[], string[], int[], int[], int[]);
void print(string[], string[], int[], int[], int[], const int&);
float computeProfit(int, int, int);
void swap(string&, string&);
void swap(int&, int&);  // Swap needs an overload...
void sort(string[], string[], int[], int[], int[], const int&);

// Entry
int main(int argc, const char *argv[]) {
    // Arrays: Reference [PA_S -> 30]
    string season[PA_S], name[PA_S];
    int seed_cost[PA_S], sell_value[PA_S], harvest_time[PA_S];

    // Function calls
    const int entrys = build(season, name, seed_cost, sell_value, harvest_time);
    sort(season, name, seed_cost, sell_value, harvest_time, entrys);
    print(season, name, seed_cost, sell_value, harvest_time, entrys);

    // EXIT
    return EXIT_SUCCESS;
}

// Function I
/***************************************************************
Function: build

Use: Used to build the parrell arrays from file data [crops.txt]

Arguments: 5 Arrays: season names, crop names, seed costs, sell values, harvest times.

Returns: An integer representing the number of items in each array

Notes: 
***************************************************************/
int build(string season[], string name[], int seed_cost[], int sell_value[], int harvest_time[]) {
    /* <task> ARRAY BULIDER </task> */
    string s, n;
    int sc, sv, ht;


    std::ifstream infile("crops.txt");

    if ( infile.fail() ) {
        FILE_ERR;
        exit(1);
    } 

    int entrys{0};
    /*<remark> 
    Get that data
    </remark>*/
    while (infile >> s >> n >> sc >> sv >> ht) {
        season[entrys] = s;
        name[entrys] = n;
        seed_cost[entrys] = sc;
        sell_value[entrys] = sv;
        harvest_time[entrys] = ht;
        ++entrys;
    }

    return entrys;
}

// Function II
/***************************************************************
Function: Print

Use: Used to print (with formatting) the data from the parallel arrays.

Arguments: 5 Arrays: season names, crop names, seed costs, sell values, harvest times.

Returns: void

Notes: 
***************************************************************/
void print( string season[], string name[], int seed_cost[], int sell_value[], int harvest_time[], const int& num_of_crops ) {

    // Required constants
    const string HEAD = "Gold Profit Per Day Report for All Crops";
    const string ROW_LABELS[ROW_W] = {"Season", "Crop Name", "Seed Cost", "Sell Value", "Harvest Time", "Gold Profit/Day"};
    const int SZ_HEAD = HEAD.size(); 

    // Output the header
    cout << std::right << std::setw(SZ_HEAD + 30) <<  HEAD << endl << endl;

    // Output the row labels
    for (int i(0); i<ROW_W; ++i) {
        cout << std::right << std::setw(16) << ROW_LABELS[i];
    }
    // Output the delimeter
    cout << endl;
    for (int i(0); i<96; ++i) cout << '-';
    cout << endl;

    // Outputting the data from the arrays
    for (int i(0); i< num_of_crops; ++i) {
        cout << std::fixed << std::setprecision(2) << std::right << std::setw(16) << season[i] 
        << std::right << std::setw(16) << name[i]
        << std::right << std::setw(16) << seed_cost[i]
        << std::right << std::setw(16) << sell_value[i]
        << std::right << std::setw(16) << harvest_time[i]
        << std::right << std::setw(16) << computeProfit(sell_value[i], seed_cost[i], harvest_time[i]);
        cout << endl;
    }
    cout << endl;


}
// Function III
/***************************************************************
Function:  Swap

Use: Swap function for integer array values

Arguments: two integers

Returns: void

Notes: 
***************************************************************/
void swap(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}

// Function IV
/***************************************************************
Function: Swap

Use: Swap function for string array values

Arguments: two strings

Returns: void

Notes: 
***************************************************************/
void swap(string& a, string& b) {
    string tmp = a;
    a = b;
    b = tmp;
}

// Function V 
/***************************************************************
Function: computeProfit

Use: Used to compute the profit for each line of data

Arguments: Sell price, buy price and harvest time

Returns: Float, represting the gold profit 

Notes: 
***************************************************************/
float computeProfit(int sell_price, int buy_price, int harvest_time) {

    return static_cast<float>((sell_price - buy_price)) / static_cast<float>(harvest_time);
}


// Function VI
/***************************************************************
Function: sort

Use: Used to sort the arrays based on their expected gold profit per day

Arguments: Our 5 parallel arrays and the number of elements in each array

Returns: void

Notes: 
***************************************************************/
void sort( string season[], string name[], int seed_cost[], int sell_value[], int harvest_time[], const int& num_of_crops ) {

    // Selection sort
    for (int j=0; j<num_of_crops; ++j) {
        float lowest = computeProfit(sell_value[j], seed_cost[j], harvest_time[j]);
        for (int k=j+1; k<num_of_crops; ++k) {
            float profit = computeProfit(sell_value[k], seed_cost[k], harvest_time[k]);
            if (profit > lowest) {
                swap(seed_cost[j], seed_cost[k]);
                swap(sell_value[j], sell_value[k]);
                swap(harvest_time[j], harvest_time[k]);
                swap(season[j], season[k]);
                swap(name[j], name[k]);
                lowest = profit;
            }
        }
    }
}

