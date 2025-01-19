//********************************************************************
//
// account.h
// CSCI 241 Assignment 9
//
// Created by Nate Warner z2004109
//
//********************************************************************

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
using std::string;

class Account {

    // Data members
    string account_number = "None";
    string customer_name = "None";
    double balance = 0.0f;

public:

    // Member functions
    Account() = default;
    Account(string&,string&,double&);
    string get_account_number();
    string get_customer_name();
    double get_balance();
    void process_deposit(double&);
    bool process_withdrawal(double&);
    void print();
};

#endif
