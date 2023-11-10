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
#include <string>

#define ll endl

// PARALLEL ARRAY SIZE
#define PA_S 30

// COLUMN LENGTH
#define COL_L 16

// ROW WIDTH
#define ROW_W 6

// ERROR OPENING FILE MESSAGE
#define FILE_ERR cerr << "Program terminated with exit code 1: Error opening file, no file named crops.txt" << endl

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
void SelectionCalculator(const string&,
                int&,
                const int&,
                int&,
                const int&,
                string[],
                string[],
                int[],
                int[],
                int[]);

// Entry
int main(int argc, const char *argv[]) {
    // Arrays: Reference [PA_S -> 30]
    string season[PA_S], name[PA_S];
    int seed_cost[PA_S], sell_value[PA_S], harvest_time[PA_S];

    // Function calls
    const int entrys = build(season, name, seed_cost, sell_value, harvest_time);
    print(season, name, seed_cost, sell_value, harvest_time, entrys);
    sort(season, name, seed_cost, sell_value, harvest_time, entrys);
    print(season, name, seed_cost, sell_value, harvest_time, entrys);


    // Extra credit

    // Needed vars for function call
    int choice, investment, days_left, available_land;
    string userSeason;

    // Selection display
    cout << "Seasons" << endl << endl
        << "1)    Spring" << endl
        << "2)    Summer" << endl
        << "3)    Fall" << endl << endl;
    cout << "Enter your choice:  (1 - 3): ";
    cin >> choice;

    // Error checking for users input
    while (choice < 1 || choice > 3) {
        cout << "Invalid season: ";
        cin >> choice;
    }

    // Convert users input to string rep
    switch ( choice ) {
        case 1:
            userSeason = "Spring";
            break;
        case 2:
            userSeason = "Summer";
            break;
        default:
            userSeason = "Fall";
    }

    // Get user input: investment amount
    cout << "How much gold are you investing? (0 - 100000): ";
    cin >> investment;
    while (investment < 0 || investment > 100000) {
        cout << "Invalid investment amount: ";
        cin >> investment;
    }

    // Get user input: days left in season
    cout << "How many days are left in this season for crops to mature? (1 - 27): ";
    cin >> days_left;
    while (days_left < 1 || days_left > 27) {
        cout << "Invalid: ";
        cin >> days_left;
    }

    // Get user input: available land
    cout << "How much tilled farmland is available to use? (0 - 128): ";
    cin >> available_land;
    while (available_land < 0 || available_land > 128) {
        cout << "Invalid: ";
        cin >> available_land;
    }
    cout << endl;

    // Call the extracredit function
    SelectionCalculator(userSeason,
            investment,
            days_left,
            available_land,
            entrys,
            season,
            name,
            seed_cost,
            sell_value,
            harvest_time);

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

    // Needed for grabbing file data
    string s, n;
    int sc, sv, ht;

    // Create the file [ input ]
    std::ifstream infile("crops.txt");

    // Check if the file failed to open
    if ( infile.fail() ) {
        FILE_ERR;
        exit(1);
    } 

    int entrys = 0;
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

    // Computes the expected profit for each data entry
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

        // We assume the first row holds the max profit
        float highest = computeProfit(sell_value[j], seed_cost[j], harvest_time[j]);
        int maxIndex = j;

        // Second loop: Offset=1
        for (int k=j+1; k<num_of_crops; ++k) {
            // Compute the profit of the kth elements
            float profit = computeProfit(sell_value[k], seed_cost[k], harvest_time[k]);
            if (profit > highest) {
                highest=profit; // Update the highest profit so far
                maxIndex = k; // So we know which index position has the highest profit
            }
        }

        // Preform the swaps
        swap(season[j], season[maxIndex]);
        swap(name[j], name[maxIndex]);
        swap(seed_cost[j], seed_cost[maxIndex]);
        swap(sell_value[j], sell_value[maxIndex]);
        swap(harvest_time[j], harvest_time[maxIndex]);
    }
}

// Function VII
/***************************************************************
Function:  SelectionCalculator

Use: Allows the user to enter a desired season, investment amount, days left in season, and available land. This function will
then calculate what type of seeds to buy, how many they can buy and how much profit they will recieve at the end of the season.
Purpose is to find the most profitable path.

Arguments: All 5 of our parrell arrays, the number of elements that we care about in each array, an investment amount, 
the number of days left in the season, and the available land

Returns: void 

Notes:
***************************************************************/
void SelectionCalculator(const string& choice,
        int& investment,
        const int& days_left,
        int& available_land,
        const int& num_of_crops,
        string season[],
        string name[],
        int seed_cost[], 
        int sell_value[],
        int harvest_time[]) {

    // Subset of our main parallel arrays, the represent the only data entrys we care about based on the users choice for the season
    string options[PA_S];
    int options_prices[PA_S];
    int options_harvest_time[PA_S];
    float options_profit[PA_S];

    // Other needed variables
    int num_seeds = 0, num_price = 0;
    float yield;

    // This will build our subset arrays based on which data entrys we can actually use
    int counter = 0; // same concept as "entrys" variable in build function
    for ( int i=0; i < num_of_crops; ++i ) {
        // Only want options that are the correct season, and furthermore follow the "days left in season" constraint
        if (season[i] == choice && harvest_time[i] < days_left) {
            options[counter] = name[i];
            options_prices[counter] = seed_cost[i];
            options_harvest_time[counter] = harvest_time[i];
            options_profit[counter] = computeProfit(sell_value[i], seed_cost[i], harvest_time[i]);
            ++counter;
        }
    }

    /*<summary> 
    Main logic 
    </summary>*/
    for (int i=0; i<counter; ++i) {
        // If we can't afford the option, we can just jump to the next iteration
        if ( investment < options_prices[i]) {
            continue;
        // We can afford the option
        } else {
            num_seeds = investment / options_prices[i]; // Calculate the number of seeds we can buy
            // If the number of seeds we can buy is greater than the available land, we consider the available land number as our seed count
            if ( num_seeds > available_land ) {
                num_seeds = available_land;
            }
            num_price = num_seeds * options_prices[i]; // Calculate what we spent
            investment-=num_price; // Update our investment amount
            available_land-=num_seeds; // Update the amount of land we have left
            yield = (options_harvest_time[i] * options_profit[i]) * num_seeds; // Calculate the profit

        }
        // To make sure we arn't displaying garbage
        if (!num_seeds) {
            break;
        }
        // Output our calculations
        cout << "Purchase " << num_seeds << " " << options[i] << " seeds, at the cost of " << num_price << " gold, which will yield " << yield << " gold in profit after " << options_harvest_time[i] <<  " days" << endl;
    }
}

