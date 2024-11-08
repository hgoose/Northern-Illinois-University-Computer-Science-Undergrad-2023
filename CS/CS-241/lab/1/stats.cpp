#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::fixed;
using std::setprecision;

int minimum(int array[], int n);
int maximum(int array[], int n);
int range(int array[], int n);
double average(int array[], int n);
double median(int array[], int n);
double stddev(int array[], int n);

int main()
{
    int a1[10] = {66, 68, 70, 72, 75, 84, 86, 86, 89, 92};
    int a2[9] = {59, 66, 68, 70, 72, 75, 86, 89, 92};
    int a3[20] = {47, 49, 51, 52, 60, 65, 67, 68, 71, 72, 77, 78, 79, 80, 83, 84, 85, 86, 89, 100};
    int n;
    
    cout << fixed << setprecision(2);
    
    n = 10;
    
    cout << "Count:              " << n << '\n';
    cout << "Minimum Value:      " << minimum(a1, n) << '\n';
    cout << "Maximum Value:      " << maximum(a1, n) << '\n';
    cout << "Range:              " << range(a1, n) << '\n';
    cout << "Average:            " << average(a1, n) << '\n';
    cout << "Median:             " << median(a1, n) << '\n';
    cout << "Standard Deviation: " << stddev(a1, n) << '\n';
    cout << endl;
    
    n = 9;

    cout << "Count:              " << n << '\n';
    cout << "Minimum Value:      " << minimum(a2, n) << '\n';
    cout << "Maximum Value:      " << maximum(a2, n) << '\n';
    cout << "Range:              " << range(a2, n) << '\n';
    cout << "Average:            " << average(a2, n) << '\n';
    cout << "Median:             " << median(a2, n) << '\n';
    cout << "Standard Deviation: " << stddev(a2, n) << '\n';
    cout << endl;

    n = 20;
    
    cout << "Count:              " << n << '\n';
    cout << "Minimum Value:      " << minimum(a3, n) << '\n';
    cout << "Maximum Value:      " << maximum(a3, n) << '\n';
    cout << "Range:              " << range(a3, n) << '\n';
    cout << "Average:            " << average(a3, n) << '\n';
    cout << "Median:             " << median(a3, n) << '\n';
    cout << "Standard Deviation: " << stddev(a3, n) << '\n';
    cout << endl;

    return 0;
}
