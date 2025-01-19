//***************************************************************************
//  account.cpp
//
//  Account Management
//  BankAccountsA9
//
//  Created by Nate Warner Z2004109
//
//***************************************************************************

#include <iostream>
#include <iomanip>
#include "account.h"

using std::cout;
using std::endl;

/**
 * Constructs an Account object with an account number, customer name, and balance.
 *
 * @param number The account number as a string.
 * @param name The name of the account holder.
 * @param balance The initial balance of the account as a double.
 */
Account::Account(string& number, string& name, double& balance) :
    account_number(number), 
    customer_name(name), 
    balance(balance) {
}

/**
 * Retrieves the account number.
 *
 * @return The account number as a string.
 */
string Account::get_account_number() {
    return this->account_number;
}

/**
 * Retrieves the customer name associated with the account.
 *
 * @return The customer's name as a string.
 */
string Account::get_customer_name() {
    return this->customer_name;
}

/**
 * Retrieves the current balance of the account.
 *
 * @return The account's balance as a double.
 */
double Account::get_balance() {
    return this->balance;
}

/**
 * Processes a deposit into the account, increasing the balance.
 *
 * @param deposit The amount to be deposited into the account as a double.
 * @return void
 */
void Account::process_deposit(double& deposit) {
    this->balance += deposit;
}

/**
 * Attempts to process a withdrawal from the account, decreasing the balance if sufficient funds exist.
 *
 * @param withdrawal The amount to be withdrawn from the account as a double.
 * @return A boolean value indicating success (true) or failure (false) of the withdrawal.
 */
bool Account::process_withdrawal(double& withdrawal) {
    if (this->balance >= withdrawal) {
        this->balance -= withdrawal;
        return true;
    }
    return false;
}

/**
 * Prints the account details to standard output.
 *
 * This includes the account number, customer name, and current balance,
 * formatted and aligned for readability.
 *
 * @return void
 */
void Account::print() {

    // Output formatted information about the account 
    cout << "Account Number: " << std::right << std::setw(10) << std::setfill('0') 
        << this->get_account_number() << std::setfill(' ') << endl 
        << "Name: " << this->get_customer_name() << endl
        << "Balance: $" << std::fixed << std::setprecision(2) << get_balance() << endl; 
}

