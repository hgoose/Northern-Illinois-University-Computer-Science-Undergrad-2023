#include <iostream>
using std::cout;
using std::endl;

void tail(int i) {
    if (i>0) {
        tail(i-1);
        cout << i << endl;
    }
}

void nontail(int i) {
    for (; i>0; --i)  {
        cout << i << endl;
    }
}

int main(int argc, char** argv) {

    tail(5);
    cout << endl;
    nontail(5);

}
