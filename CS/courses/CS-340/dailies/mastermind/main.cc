#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

int mm_score(string k, string g, int &b, int &w);

int main(int argc, const char* argv[]) {

    int black = 0, white = 0;

    string key = "abc";
    string guess = "axb";

    string k="xxxyy",  g="xyzbx";

    // mm_score(key,guess, black, white);
    // cout << "Black: " << black << endl << "White: " << white << endl;

    mm_score(k,g, black, white);
    cout << "Black: " << black << endl << "White: " << white << endl;



    return 0;
}
