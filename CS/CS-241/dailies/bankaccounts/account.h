#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
using std::string;

class Account {
    string account_number = "None";
    string customer_name = "None";
    double balance = 0.0f;

public:
    Account() = default;
    Account(string,string,double);
    string get_account_number();
    string get_customer_name();
    double get_balance();
    void process_deposit(double);
    bool process_withdrawal(double);
    void print();
};

#endif
