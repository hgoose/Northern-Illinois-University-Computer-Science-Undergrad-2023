#ifndef BANK_H
#define BANK_H

#include <string>
#include "account.h"
using std::string;

class bank {
    string bank_name = "None";
    Account accounts[20];
    int count = 0;

public:
    bank() = default;
    void sort_accouts(Account[]);
    int account_exists(string&);
    void read_accounts(string);
    void process_transactions(string);
    void print();

};

#endif
