/***************************************************************
CSCI 240         Program 10     Fall 2023

Programmer: Nathan Warner
 
Section: 001

Date Due: December 8

Purpose: Utilize various tools and algorithms discussed throughout the semester together with class implementation to create and sort reports on powerlifters.
***************************************************************/
#include <iostream> // For input/output tasks
#include <iomanip> // For input/output manipulators
#include <cstdlib> // For random, system, exit, EXIT_SUCCESS, and EXIT_FAILURE
#include <fstream>
// #include <cstdint> // For fixed width data types
#include <unistd.h> // Posix API
#include <typeinfo> // typeid(n).name()
#include <cctype> // For character functions
#include <algorithm> // Defined algorithms
#include <iterator> // Iterator functions and types
#include <string> // String class
#include <cstring> // For c-string functions

// Some macros
#define a_sizeof(x) sizeof(x) / sizeof(x[0])
#define show(a) cout << a << endl;
#define SHOW_AR(a) for (const auto& i : a) cout << i << " "; cout << endl;
#define NOPOS -1
#define LINE_BREAK cout << endl; for (int i = 0; i < 96; i++) cout << "-"; cout << endl;
#define NAME_MAXSIZE 15
#define N_HEAD 8
#define STRING_JUST 18
#define NUMERIC_JUST 10
#define TITLE_JUST 37
#define PROC_COMPLETE(a) cout << "File processing has been complete. We have " << a << " powerlifters recorded." << endl << endl << endl;

// Using
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;

// Symbolic Constant
const char* HEADS[N_HEAD] =  {
    "First Name", "Last Name", "Wilks",
    "Squat", "Bench", "DL", 
    "Total", "W. Score"
};

const char TITLE_DEFAULT[] = "Default List of Powerlifters";
const char TITLE_TOTAL[] = "Powerlifters Ranked by Total";
const char TITLE_WILKS[] = "Powerlifters Ranked by Wilks";
const char TITLE_SQUAT[] = "Powerlifters Ranked by Squat";
const char TITLE_BENCH[] = "Powerlifters Ranked by Bench";
const char TITLE_DEADLIFT[] = "Powerlifters Ranked by Deadlift";

/*<remark> 
The Wilks coefficient is a method by which the strength of a powerlifter is measured against other powerlifters of a different weight category.
</remark>*/

class PowerLifter {
    char fname[NAME_MAXSIZE];
    char lname[NAME_MAXSIZE];
    float wilks;
    int maxsquat;
    int maxbench;
    int maxdeadlift;

public:
    PowerLifter(); 
    void setFirst(const char[]);
    void setLast(const char[]);
    void setCoef(float);
    int getSquat();
    void setSquat(int);
    int getBench();
    void setBench(int);
    int getDeadlift();
    void setDeadlift(int);
    int getTotal();
    int wilksScore();
    int compare(PowerLifter&);
    void display();

};

void sortBy(PowerLifter[], int, const char[]);
void swap( PowerLifter&, PowerLifter&);
int readFile(PowerLifter[], const char[]);
void printPowerLifters(PowerLifter[], int, const char[]);

int main(int argc, const char *argv[]) {


    PowerLifter par[30];
    int count = readFile(par, "lifters.txt");

    PROC_COMPLETE(count)
    printPowerLifters(par, count, TITLE_DEFAULT);
    sortBy(par,count,"Total");
    printPowerLifters(par, count, TITLE_TOTAL);
    sortBy(par,count,"Wilks");
    printPowerLifters(par, count, TITLE_WILKS);
    sortBy(par,count,"Squat");
    printPowerLifters(par, count, TITLE_SQUAT);
    sortBy(par,count,"Bench");
    printPowerLifters(par, count, TITLE_BENCH);
    sortBy(par,count,"Deadlift");
    printPowerLifters(par, count, TITLE_DEADLIFT);
    

    return EXIT_SUCCESS;
}

PowerLifter::PowerLifter() : wilks(1), maxsquat(-1), maxbench(-1), maxdeadlift(-1) {
    const char* fnametmp = "no";
    const char* lnametmp = "name";
    strncpy(this->fname, fnametmp, NAME_MAXSIZE);
    strncpy(this->lname, lnametmp, NAME_MAXSIZE);
}

void PowerLifter::setFirst(const char newFirst[]) {
    strncpy(this->fname, newFirst, NAME_MAXSIZE);
}

void PowerLifter::setLast(const char newLast[]) {
    strncpy(this->lname, newLast, NAME_MAXSIZE);
}

int PowerLifter::getSquat() {
    return this->maxsquat;
}

void PowerLifter::setSquat(int newSquat) {
    if ( newSquat > -1 ) {
        this->maxsquat = newSquat;
    } 
}

int PowerLifter::getBench() {
    return this->maxbench;
}

void PowerLifter::setBench(int newBench) {
    if ( newBench > -1 ) {
        this->maxbench = newBench;
    }
}

int PowerLifter::getDeadlift() {
    return this->maxdeadlift;
}

void PowerLifter::setDeadlift(int newDeadlift) {
    if ( newDeadlift > -1 ) {
        this->maxdeadlift = newDeadlift;
    }
}

int PowerLifter::getTotal() {
    return this->maxsquat + this->maxbench + this->maxdeadlift;
}

void PowerLifter::setCoef(float newCoef) {
    if ( newCoef >= 0 && newCoef < 2) {
        this->wilks = newCoef;
    }

}

int PowerLifter::wilksScore() {
    return static_cast<int>(this->getTotal() * this->wilks);
}

int PowerLifter::compare(PowerLifter& other) {
    return (this->wilks == other.wilks ? 0 : (this->wilks < other.wilks ? -1 : 1));
}

void PowerLifter::display() {
    cout << std::setw(STRING_JUST) << this->fname 
        << std::setw(STRING_JUST) << this->lname 
        << std::fixed << std::setprecision(4) << std::setw(NUMERIC_JUST) << this->wilks 
        << std::setw(NUMERIC_JUST) << this->maxsquat
        << std::setw(NUMERIC_JUST) << this->maxbench
        << std::setw(NUMERIC_JUST) << this->maxdeadlift
        << std::setw(NUMERIC_JUST) << this->getTotal()
        << std::setw(NUMERIC_JUST) << this->wilksScore() << endl;
}


void sortBy(PowerLifter array[], int size, const char type[]) {
    // Valid types 

    /*
    Squat
    Bench
    Deadlift
    Total
    Wilks 
    */

    int min;
    if (!strcmp(type, "Squat")) {
    for (int j=0; j<size; ++j) {
        min = j;
        for (int k=j+1; k<size; ++k) {
            if (array[k].getSquat() > array[min].getSquat()) {
                min = k;
            }
        }
        swap(array[j], array[min]);
    }
    } else if (!strcmp(type, "Bench")) {
        for (int j=0; j<size; ++j) {
            min = j;
            for (int k=j+1; k<size; ++k) {
                if (array[k].getBench() > array[min].getBench()) {
                    min = k;
                }
            }
            swap(array[j], array[min]);
        }
    } else if (!strcmp(type, "Deadlift")) {
        for (int j=0; j<size; ++j) {
            min = j;
            for (int k=j+1; k<size; ++k) {
                if (array[k].getDeadlift() > array[min].getDeadlift()) {
                    min = k;
                }
            }
            swap(array[j], array[min]);
        }
    } else if (!strcmp(type, "Total")) {
        for (int j=0; j<size; ++j) {
            min = j;
            for (int k=j+1; k<size; ++k) {
                if (array[k].getTotal() > array[min].getTotal()) {
                    min = k;
                }
            }
            swap(array[j], array[min]);
        }
    } else if (!strcmp(type, "Wilks")) {
        for (int j=0; j<size; ++j) {
            min = j;
            for (int k=j+1; k<size; ++k) {
                if (array[k].wilksScore() > array[min].wilksScore()) {
                    min = k;
                }
            }
            swap(array[j], array[min]);
        }
    }

}

void swap(PowerLifter& val1, PowerLifter& val2) {
    PowerLifter tmp = val1;
    val1=val2;
    val2=tmp;
}

int readFile( PowerLifter array[], const char fileName[] ) {

    std::ifstream file(fileName);

    char fname[NAME_MAXSIZE];
    char lname[NAME_MAXSIZE];
    float wilks;
    int squat, bench, deadlift, count=0;


    while (file >> fname >> lname >> wilks >> squat >> bench >> deadlift) {
        PowerLifter pn;

        pn.setFirst(fname);
        pn.setLast(lname);
        pn.setCoef(wilks);
        pn.setSquat(squat);
        pn.setBench(bench);
        pn.setDeadlift(deadlift);
        pn.getTotal();
        pn.wilksScore();

        array[count] = pn;

        ++count;

    }

    return count;
}

void printPowerLifters( PowerLifter array[], int size, const char title[] ) {

    cout << std::setw(TITLE_JUST + strlen(title)) << title << endl;

    for (int i=0; i<N_HEAD; ++i) {
        if ( i < 2 ) {
            cout << std::right << std::setw(STRING_JUST) << HEADS[i];
        } else {
            cout << std::setw(NUMERIC_JUST) << HEADS[i];
        }
    }
    LINE_BREAK

    for (int i=0; i<size; ++i) {
        array[i].display();
    }

    cout << endl << endl;


}


