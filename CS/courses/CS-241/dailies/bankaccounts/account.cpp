#include <iostream>
#include <iomanip>
#include "account.h"

using std::cout;
using std::endl;

Account::Account(string number,string name,double balance) :
    account_number(number), 
    customer_name(name), 
    balance(balance) {
}

string Account::get_account_number() {
    return this->account_number;
}


string Account::get_customer_name() {
    return this->customer_name;
}


double Account::get_balance() {
    return this->balance;
}


void Account::process_deposit(double deposit) {
    this->balance += deposit;
}


bool Account::process_withdrawal(double withdrawal) {
    if (this->balance >= withdrawal) {
        this->balance -= withdrawal;
        return true;
    }
    return false;
}


void Account::print() {
    cout << "Account Number: " << std::right << std::setw(10) << std::setfill('0') 
        << this->get_account_number() << std::setfill(' ') << endl 
        << "Name: " << this->get_customer_name() << endl
        << "Balance: $" << std::fixed << std::setprecision(2) << get_balance() << endl; 

}

