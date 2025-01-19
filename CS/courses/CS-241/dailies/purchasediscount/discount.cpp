#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::fixed;
using std::setprecision;

double discount(double amount);

int main()
{
    cout << fixed << setprecision(2);
    
    double amount = 27.99;
    
    cout << "Purchase amount: " << amount << ", discounted amount: "
         << discount(amount) << endl;

    amount = 50.00;
    
    cout << "Purchase amount: " << amount << ", discounted amount: "
         << discount(amount) << endl;

    amount = 67.99;
    
    cout << "Purchase amount: " << amount << ", discounted amount: "
         << discount(amount) << endl;

    amount = 100.00;
    
    cout << "Purchase amount: " << amount << ", discounted amount: "
         << discount(amount) << endl;

    amount = 184.27;
    
    cout << "Purchase amount: " << amount << ", discounted amount: "
         << discount(amount) << endl;

    return 0;
}
