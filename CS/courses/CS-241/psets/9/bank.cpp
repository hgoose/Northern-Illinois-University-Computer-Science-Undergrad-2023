//***************************************************************************
//  bank.cpp
//
//  Bank Management
//  BankAccountsA9
//
//  Created by Nate Warner Z2004109
//
//***************************************************************************

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include "bank.h"

using std::cout;
using std::endl;


/**
 * Reads account information from a specified file and stores it in the bank's accounts.
 * Each account's details are separated by colons in the file. This function also sorts
 * the accounts by account number after reading them.
 * 
 * @param file The path to the file containing account information.
 */
void bank::read_accounts(const string& file) {
    string account_number = "";
    string name = "";
    string bal_tmp = "";
    double balance = 0.0f;

    std::ifstream input(file); // Open the file for reading

    // Check if the file was successfully opened
    if (input.fail()) {
        cout << "Error opening file: " << file << endl;
        exit(1); // Exit if file cannot be opened
    }

    // Read the bank's name from the first line of the file
    std::getline(input, this->bank_name);

    // Read each account's details, separated by colons
    while (std::getline(input, account_number, ':')) {
        std::getline(input, name, ':');
        std::getline(input, bal_tmp); // Temporary string for balance
        balance = stod(bal_tmp); // Convert string balance to double

        Account newaccount(account_number, name, balance); // Create a new Account object
        accounts[count] = newaccount; // Add the new account to the array
        ++count; // Increment the count of accounts
    }

    input.close(); // Close the file

    sort_accounts(accounts); // Sort the accounts after reading them
}


/**
 * Sorts the accounts array using the selection sort algorithm based on account numbers.
 * 
 * @param arr[] The array of Account objects to be sorted.
 */
void bank::sort_accounts(Account arr[]) {
    for (int j = 0; j < count - 1; ++j) {
        int min = j; // Start with the current index as the minimum
        for (int k = j + 1; k < count; ++k) {
            // If the current account number is less than the current minimum, update min
            if (arr[k].get_account_number() < arr[min].get_account_number()) {
                min = k;
            }
        }
        // Swap the minimum element found with the current element
        std::swap(arr[j], arr[min]);
    }
}


/**
 * Searches for an account by account number using binary search.
 * 
 * @param account_number The account number to search for.
 * @return The index of the account in the accounts array if found, -1 otherwise.
 */
int bank::account_exists(string& account_number) {
    int low = 0;
    int high = count - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2; // Calculate mid to avoid overflow
        const string& midAccountNumber = accounts[mid].get_account_number();

        // Check if the mid account is the one we're looking for
        if (midAccountNumber == account_number) {
            return mid; // Account found
        } else if (midAccountNumber < account_number) {
            low = mid + 1; // Search in the right half
        } else {
            high = mid - 1; // Search in the left half
        }
    }

    return -1; // Account not found
}


/**
 * Processes transactions from a specified file. Each transaction includes a date,
 * account number, transaction type (deposit or withdrawal), and amount. The function
 * updates account balances accordingly and prints a transaction report.
 * 
 * @param file The path to the file containing transaction information.
 */
void bank::process_transactions(const string& file) {
    string date, account_number;
    char type;
    double amount;

    std::ifstream input(file); // Open the file for reading

    // Check if the file was successfully opened
    if (input.fail()) {
        cout << "Error opening file: " << file << endl;
        exit(1);
    }

    // Print the header for the transaction report
    cout << std::right << std::setw(46) << "Transaction Report" << endl << endl 
         << std::left << std::setw(8) << "Date"
         << std::left << std::setw(22) << "Account" 
         << std::left << std::setw(7) << "Type"
         << std::left << std::setw(11) << "Amount"
         << "New Balance" << endl << endl;

    // Read and process each transaction from the file
    while (input >> date >> account_number >> type >> amount) {
        cout << std::left << std::setw(8) << date
             << std::left << std::setw(22) << account_number
             << std::left << std::setw(8) << type
             << std::right << std::setw(7) << std::fixed << std::setprecision(2) << amount;

        int position = account_exists(account_number); // Check if the account exists

        // Process the transaction if the account exists
        if (position != -1) {
            switch (type) {
                case 'D': // Deposit
                    accounts[position].process_deposit(amount); // Process the deposit
                    cout << std::right << std::setw(11) << accounts[position].get_balance() << endl; // Output the new balance
                    break;
                case 'W': // Withdrawal
                    if (accounts[position].process_withdrawal(amount)) { // Process the deposit if there are sufficient funds
                        cout << std::right << std::setw(11) << accounts[position].get_balance() << endl; // Output the new balance
                    } else {
                        cout << std::right << std::setw(29) << "*** Insufficient funds ***" << endl; // Output insufficient funds
                    }
                    break;
            }
        } else {
            cout << std::right << std::setw(33) << "*** Invalid account number ***" << endl; // Invalid account number
        }
    }
    cout << endl;
    input.close(); // Close the file after processing transactions
}


/**
 * Prints a listing of all accounts in the bank, including account numbers,
 * customer names, and balances.
 */
void bank::print() {

    // Output header
    cout << "Account Listing for First National Bank" << endl << endl;

    // Loop through each account and print its details
    for (int i = 0; i < count; ++i) {
        accounts[i].print(); // Print account details
        cout << endl; // Print a newline after each account for readability
    }
}
