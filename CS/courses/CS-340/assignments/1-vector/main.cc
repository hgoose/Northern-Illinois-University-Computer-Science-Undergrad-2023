
/**
# 340 Spring 2024 Assigment 1
# Generate random numbers in one vector, and copy it into another vector in reservse order
#
#  Then print out the two vectors with certain format using setw.
#
#  This is the main function provided for student's testing.
**/

#include <vector>
#include <cstdlib> 
#include <iostream>
#include <iomanip> 
using namespace std; 

//generate random numnber using provided seed and put in a vector
//do not assume there is pre-allocated space
void gen_rnd_nums ( vector < int >& v , int seed, int range_limit, int vec_size);

//reverse copy contents of v1 into v2
int reverse_copy(vector<int>& v1, vector<int>& v2);

//print the contents of a vector to stdout
void print_vec( const vector <int>& v, int items_per_row, int item_width);
           
int main() {

    //some parameters
    int rand_up_limit = 1000;
    int size = 99;
    int seed = 7;
    int items_per_row = 10;
    int width = 8;

    vector<int> v1, v2;
    gen_rnd_nums(v1, seed, rand_up_limit, size);

    //make v2 the same size as v1
    v2.resize(v1.size());
    if (reverse_copy(v1, v2) == -1)
    {
      cout << "reverse copy failed" << endl;
      return -1;
    }
    
    cout << endl << "first vector: " << endl;
    print_vec(v1, items_per_row, width);
    cout << endl << "second vector: " << endl;
    print_vec(v2, items_per_row, width);

    return 0;
}

