#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include "bank.h"

using std::cout;
using std::cin;
using std::endl;



void bank::read_accounts(string file) {

    string account_number = "";
    string name = "";
    string bal_tmp = "";
    double balance = 0.0f;

    std::ifstream input(file);

    if (input.fail()) {
        cout << "Error opening file: " << file << endl;
        exit(1);
    }

    std::getline(input, this->bank_name);

    while (std::getline(input, account_number, ':')) {
        std::getline(input, name, ':');
        std::getline(input, bal_tmp);
        balance = stod(bal_tmp);

        Account newaccount(account_number, name, balance);

        accounts[count] = newaccount;
        ++count;
    }

    input.close();

    sort_accouts(accounts);


}

void bank::sort_accouts(Account arr[]) {

    for (int j=0; j<count-1; ++j) {
        int min = j;
        for (int k=j+1; k<count; ++k) {
            if (arr[k].get_account_number() < arr[min].get_account_number()) {
                min = k;
            }
        }
        std::swap(arr[j], arr[min]);
    }
}

int bank::account_exists(string& account_number) {

    int low = 0;
    int high = count - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2; // To avoid potential overflow
        const string& midAccountNumber = accounts[mid].get_account_number();

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


void bank::process_transactions(string file) {

    string date, account_number;
    char type;
    double amount;


    std::ifstream input(file);

    if (input.fail()) {
        cout << "Error opening file: " << file << endl;
        exit(1);
    }

    cout << std::right << std::setw(46) << "Transaction Report" << endl << endl 
        << std::left << std::setw(8) << "Date"
        << std::left << std::setw(22) << "Account" 
        << std::left << std::setw(7) << "Type"
        << std::left << std::setw(11) << "Amount"
        << "New Balance" << endl << endl;

    while (input >> date >> account_number >> type >> amount) {

        cout << std::left << std::setw(8) << date
            << std::left << std::setw(22) << account_number
            << std::left << std::setw(8) << type
            << std::right << std::setw(7) << amount; 

        int position = account_exists(account_number);

        if (position != -1) {

            switch (type) {
                case 'D':
                    accounts[position].process_deposit(amount);
                    cout << std::right << std::setw(11) << accounts[position].get_balance() << endl; 
                    break;
                case 'W':
                    if (accounts[position].process_withdrawal(amount)) {
                        cout << std::right << std::setw(11) << accounts[position].get_balance() << endl;
                    } else {
                        cout << std::right << std::setw(29) << "*** Insufficient funds ***" << endl;
                    }
                    break;
            }

        }  else {
            cout << std::right << std::setw(33) << "*** Invalid account number ***" << endl;
        }
    }
    cout << endl;
    input.close();
}


void bank::print() {

    cout << "Account Listing for First National Bank" << endl << endl;

    for (int i=0; i<count; ++i) {
        accounts[i].print();
        cout << endl;
    }
}

