#include <iostream>
#include <string>

using std::istream;
using std::string;

void printTree(istream & is);

int computeSize(istream & is, string path);

string smallestDir(istream & is, int targetSize, string ext="");

void listDeleted(istream & is, int targetSize, string ext="");
