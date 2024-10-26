#include "filetree.h"

#include <iostream>
#include <fstream>
#include <string>

using std::cout;
using std::endl;
using std::istream;
using std::ifstream;
using std::string;

void rewindStream(istream & is)
{
    is.seekg(0, is.beg);
    is.clear();
}

int main() {
    // each function is called "from scratch" so we rewind the stream
    auto input = ifstream("input.txt");

    printTree(input);
    rewindStream(input);

    cout << "Size of /a/f/: " << computeSize(input, "/a/f/") << endl;
    rewindStream(input);

    cout << "Smallest dir for 650000: " << smallestDir(input, 650000) << endl;
    rewindStream(input);

    cout << "Smallest dir for 616000 and .jpg: " << smallestDir(input, 616000, ".jpg") << endl;
    rewindStream(input);

    cout << "Deleted files for 650000:" << endl;
    listDeleted(input, 650000);
    rewindStream(input);

    return 0;
}
