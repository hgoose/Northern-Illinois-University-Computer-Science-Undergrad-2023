#include <iostream>
#include <iomanip>
#include <cstdlib>

using std::cout;
using std::cin;
using std::endl;


int main(int argc, const char *argv[]) {

    double initial_investment, annual_rate, v_year1, v_year2, v_year3, v_year4;

    cout << "How much is the initial investment amount? ";
    cin >> initial_investment;

    cout << "What is the annual interest rate? ";
    cin >> annual_rate;

    v_year1 = initial_investment + (initial_investment * annual_rate / 100);
    v_year2 = v_year1 + (v_year1 * annual_rate / 100);
    v_year3 = v_year2 + (v_year2 * annual_rate / 100);
    v_year4 = v_year3 + (v_year3 * annual_rate / 100);


    // Formated ouput
    

    cout << endl << endl
        << "Investment Results" << endl << endl
        // << std::left << std::setw(15)
        << "Initial Investment "
        << std::fixed << std::setprecision(2)
        << std::right << std::setw(14)
        << initial_investment << endl
        // << std::left << std::setw(13)
        << "Annual Interest Rate "
        << std::fixed << std::setprecision(1)
        << std::right << std::setw(12)
        << annual_rate << endl << endl
        << std::fixed << std::setprecision(2)
        << "Year 1 account value $" << v_year1 << "  --  increase of $" << (v_year1 - initial_investment) << endl
        << "Year 2 account value $" << v_year2 << "  --  increase of $" << (v_year2 - v_year1) << endl
        << "Year 3 account value $" << v_year3 << "  --  increase of $" << (v_year3 - v_year2) << endl
        << "Year 4 account value $" << v_year4 << "  --  increase of $" << (v_year4 - v_year3) << endl; 


    return EXIT_SUCCESS;

}

