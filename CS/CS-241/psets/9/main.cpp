//************************************************************
//
// main.cpp
// BankAccountsA9
//
// Created by Nate Warner z2004109
//
//************************************************************

#include <iostream>
#include "bank.h"

using std::cout;
using std::endl;

int main()
{
    bank b;

    b.read_accounts("accounts.txt");

    b.print();

    cout << endl;

    b.process_transactions("transactions.txt");

    cout << endl;

    b.print();

    return 0;
} 

