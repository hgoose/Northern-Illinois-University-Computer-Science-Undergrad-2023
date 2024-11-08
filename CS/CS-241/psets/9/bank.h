//********************************************************************
//
// bank.h
// CSCI 241 Assignment 9
//
// Created by Nate Warner z2004109
//
//********************************************************************


#ifndef BANK_H
#define BANK_H

#include <string>
#include "account.h"
using std::string;

class bank {

    // Data members
    string bank_name = "None";
    Account accounts[20];
    int count = 0;

public:

    // Member functions
    bank() = default;
    void sort_accounts(Account[]); // auxiliary
    int account_exists(string&); // auxiliary
    void read_accounts(const string&); 
    void process_transactions(const string&);
    void print();

};

#endif
