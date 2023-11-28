/***************************************************************
CSCI 240         Program 9     Fall 2023

Programmer: Nathan Warner
 
Section: 001

Date Due: December 1

Purpose: implement a class representing a 3D vector which will make extensive use of overloading class methods. 
This means there will be multiple versions of methods defined that each take different arguments. This assignment 
rewards one for being "smart but also lazy" when it comes to implementing each of these methods, as they can readily 
use previously defined methods to reduce the amount of code necessary to write to complete the next one.
***************************************************************/
#include <iostream> // For input/output tasks
#include <iomanip> // For input/output manipulators
#include <cstdlib> // For random, system, exit, EXIT_SUCCESS, and EXIT_FAILURE
#include <cstdint> // For fixed width data types
#include <unistd.h> // Posix API
#include <typeinfo> // typeid(n).name()
#include <cctype> // For character functions
#include <algorithm> // Defined algorithms
#include <iterator> // Iterator functions and types
#include <string> // String class
#include <sstream>

// Some macros
#define a_sizeof(x) sizeof(x) / sizeof(x[0])
#define show(a) cout << a << endl;
#define SHOW_AR(a) for (const auto& i : a) cout << i << " "; cout << endl;
#define NOPOS -1
#define LINE_BREAK cout << endl; for (int i = 0; i < 75; i++) cout << "-"; cout << endl;

// Using
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;

class Vector {
public:
    int components[3] = {0};

public:
    Vector();
    Vector(int components[]);
    void set(int _values[]);
    Vector add(int _values[]);
    Vector add(Vector& _other);
    Vector multiply(int scalar);
    Vector multiply(int _values[]);
    Vector multiply(Vector& _other);
    Vector subtract(int _values[]);
    Vector subtract(Vector& _other);
    bool isEqual(int _values[]);
    bool isEqual(Vector& _other);
    bool isSimilar(int _values[]);
    bool isSimilar(Vector& _other);
    string to_string();

};




/************

Make sure to fill this in with your name, etc...

************/


int main()
  {
  //Test the both constructors and the to_string method
  Vector alpha;

  cout << "Test #1: Testing default constructor and to_string(): alpha == " << alpha.to_string() << endl;

  int slacker[3] = {1, 2, 3};

  Vector beta(slacker);

  cout << "\nTest #2: Testing alternate constructor: beta == " << beta.to_string() << endl;

  LINE_BREAK


  //Test the add method
  cout << "\nTest #3: Testing add functionality." << endl;
  cout << alpha.to_string() << " + " << beta.to_string() << " == " << alpha.add(beta).to_string() << endl;

  slacker[0] = 14;
  slacker[1] = 2;
  slacker[2] = -9;


  //Test the set and subtract methods
  cout << "\nTest #4: Testing set and subtract functionality." << endl;
  alpha.set(slacker);
  cout << alpha.to_string() << " - " << beta.to_string() << " == " << alpha.subtract(beta).to_string() << endl;

  LINE_BREAK


  //Test the multiply methods
  cout << "\nTest #5: Testing scalar multiplication." << endl;
  cout << alpha.to_string() << " * 4 == " << alpha.multiply(4).to_string() << endl;

  cout << "\nTest #6a: Testing cross-product multiplication with a Vector argument." << endl;
  cout << alpha.to_string() << " X " << beta.to_string() << " == " << alpha.multiply(beta).to_string() << endl;

  for (int i = 0; i < 3; i++)
    slacker[i] = (i + 1);

  cout << "\nTest #6b: Testing cross-product multiplication with an integer-array argument." << endl;
  cout << alpha.to_string() << " X <1, 2, 3> == " << alpha.multiply(slacker).to_string() << endl;

  for (int i = 0; i < 3; i++)
    slacker[i] = (i * i);

  alpha.set(slacker);

  LINE_BREAK


  //Test the isEqual method
  cout << "\nTest #7a: Testing for equality (failure)." << endl;
  cout << "Is " << alpha.to_string() << " equal to " << beta.to_string() << "?" << endl;
  if (alpha.isEqual(beta))
    cout << "Yes (this is wrong)." << endl;
  else
    cout << "No (this is correct)." << endl;

  for (int i = 0; i < 3; i++)
    slacker[i] = (i + 1);

  alpha.set(slacker);

  cout << "\nTest #7b: Testing for equality (success)." << endl;
  cout << "Is " << alpha.to_string() << " equal to " << beta.to_string() << "?" << endl;
  if (alpha.isEqual(beta))
    cout << "Yes (this is correct)." << endl;
  else
    cout << "No (this is wrong)." << endl;

  LINE_BREAK


  //Test the isSimilar methods
  cout << "\nTest #8a: Testing for similarity (equal vectors)." << endl;
  cout << "Is " << alpha.to_string() << " similar to " << beta.to_string() << "?" << endl;

  if (alpha.isSimilar(beta))
    cout << "Yes (this is correct)." << endl;
  else
    cout << "No (this is wrong)." << endl;

  for (int i = 0; i < 3; i++)
    slacker[i] = (i + 1) * 6;

  beta.set(slacker);

  cout << "\nTest #8b: Testing for similarity (scalar vectors)." << endl;
  cout << "Is " << alpha.to_string() << " similar to " << beta.to_string() << "?" << endl;

  if (alpha.isSimilar(beta))
    cout << "Yes (this is correct)." << endl;
  else
    cout << "No (this is wrong)." << endl;

  cout << "\nTest #8c: Testing for similarity (scalar vectors)." << endl;
  cout << "Is " << beta.to_string() << " similar to " << alpha.to_string() << "?" << endl;

  if (beta.isSimilar(alpha))
    cout << "Yes (this is correct)." << endl;
  else
    cout << "No (this is wrong)." << endl;

  for (int i = 0; i < 3; i++)
    slacker[i] = (i * i * i) + (10 - i);

  beta.set(slacker);

  cout << "\nTest #8d: Testing for similarity (failure)." << endl;
  cout << "Is " << alpha.to_string() << " similar to " << beta.to_string() << "?" << endl;

  if (alpha.isSimilar(beta))
    cout << "Yes (this is wrong)." << endl;
  else
    cout << "No (this is correct)." << endl;

  return 0;
}

Vector::Vector() : components{0,0,0} {}
Vector::Vector(int components[]) { this->set(components); } 

void Vector::set(int _values[]) {
    for (int i=0; i<3; ++i) {
        this->components[i] = _values[i];
    }
}

Vector Vector::add(int _values[]) {
    int tmp[3] = {0};
    for (int i=0; i<3; ++i) {
        tmp[i] = _values[i] + this->components[i];
    }
    return Vector(tmp);
}

Vector Vector::add(Vector& other) { 
    int tmp[3] = {0};
    for (int i=0; i<3; ++i) {
        tmp[i] =  this->components[i] + other.components[i];
    }
    return Vector(tmp);
}

Vector Vector::multiply(int scalar) {
    int tmp[3] = {0};
    for (int i=0; i<3; ++i) {
        tmp[i] = this->components[i] * scalar;
    }
    return Vector(tmp);
}

Vector Vector::multiply(int values[]) {
    int tmp[3] = {
        (this->components[1] * values[2]) - (this->components[2] *values[1]),
        (this->components[2] * values[0]) - (this->components[0] *values[2]),
        (this->components[0] * values[1]) - (this->components[1] *values[0])
    };
    return Vector(tmp);
}

Vector Vector::multiply(Vector& other) {
    int tmp[3] = {
        (this->components[1] * other.components[2]) - (this->components[2] * other.components[1]),
        (this->components[2] * other.components[0]) - (this->components[0] * other.components[2]),
        (this->components[0] * other.components[1]) - (this->components[1] * other.components[0])
    };
    return Vector(tmp);
}

Vector Vector::subtract(int _values[]) {
    int tmp[3] = {0};
    for (int i=0; i<3; ++i) {
        tmp[i] = this->components[i] - _values[i];
    }
    return Vector(tmp);
}

Vector Vector::subtract(Vector& other) {
    int tmp[3] = {0};
    for (int i=0; i<3; ++i) {
        tmp[i] = this->components[i] - other.components[i];
    }
    return Vector(tmp);
}

bool Vector::isEqual(int _values[]) {
    bool flag = 1;
    for (int i=0; i<3; ++i) {
        if (this->components[i] != _values[i]) flag=0; 
    }
    return flag;
}

bool Vector::isEqual(Vector& other) {
    bool flag = 1;
    for (int i=0; i<3; ++i) {
        if (this->components[i] != other.components[i]) flag=0; 
    }
    return flag;
}

bool Vector::isSimilar(int _values[]) {
    /*<note> I did write this, wanted to do one of this methods a lil different (i like lambdas) </note>*/
    const double check = static_cast<double>(_values[0]) / this->components[0];
    const double tolerance = 1e-6; // had to define a tolerance, floating point comparsion can get weird.
    auto lambda = [&](int& x, int& y) -> bool {
        return std::abs(static_cast<double>(y)/x - check) < tolerance;
    };
    return std::equal(
        std::begin(this->components), // Starting range for data membber
        std::end(this->components), // Ending range for data member
        _values, // Starting range for _values array
        _values+3, // Ending range for _values array
        lambda // Custom policy defined above
    );

    /*<note> This would be a typical solution you are probably looking for </note>*/
    // int check = _values[0] / this->components[0];
    // bool flag = 1;
    // for (int i=1; i<3; ++i) {
    //     if (static_cast<double>(_values[i]) / this->components[i] != check) flag=0;
    // }
    // return flag;
    // return 0;
}

 bool Vector::isSimilar(Vector& other) {

     /*<note>  Things got a bit messy when I realized the case of potential zeros, I might clean it up </note>*/

    double check;
    bool flag = 1;
    int count = 0;
    const double tolerance = 1e-6;
    for (int i=0; i<3; ++i) {
        if ((this->components[i] == 0 && other.components[i] != 0) || (other.components[i] == 0 && this->components[i] != 0)) {
            return false;
        } else if (this->components[i] == 0 && other.components[i] == 0) {
            ++count;
            continue;
        }
    }
    if (count == 2) {
        for (int i=0; i<3; ++i) {
            if (this->components[i] !=0) {
                return (other.components[i] % this->components[i] == 0 ? 1 : 0);
            }
        }
    } else if ( count == 3 ){
        return true;
    } else {
        for (int i=0; i<3; ++i) {
            if (this->components[i] != 0) {
                check = static_cast<double>(other.components[i]) / this->components[i];
                break;
            }
        }
    }
    for (int i=0; i<3; ++i) { 
        if (this->components[i] != 0) {
            if (std::abs(static_cast<double>(other.components[i]) / this->components[i] - check) > tolerance) flag = 0;
        }
    } return flag;
}

string Vector::to_string() {
    std::ostringstream oss;
    oss << "<" << this->components[0] << "," << this->components[1] << "," << this->components[2] << ">"; 
    return oss.str();
}

