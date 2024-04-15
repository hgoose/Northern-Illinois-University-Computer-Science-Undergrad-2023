#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;
using std::to_string;

bool wc(const string& file_name, int& lines, int& words, int& characters);

int main()
{
    int l, w, c;
    string name;

    for (int i = 1; i <= 8; i++)
    {
        l = w = c = -1;
        name = "in" + to_string(i) + ".txt";
        
        if (wc(name, l, w, c))
        {
            cout << "in" << i << ".txt: lines = " << l
                 << ", words = " << w
                 << ", characters = " << c << endl;
        }
        else
            cout << "Unable to open in" << i << ".txt\n";
    }
    
    return 0;
}

