/***************************************************************
CSCI 240         Program 9     Fall 2023

Programmer: Nathan Warner
 
Section: 001

Date Due: December 1

Purpose: Implement a class representing a 3D vector which will make extensive use of overloading class methods. 
This means there will be multiple versions of methods defined that each take different arguments. This assignment 
rewards one for being "smart but also lazy" when it comes to implementing each of these methods, as they can readily 
use previously defined methods to reduce the amount of code necessary to write to complete the next one.
***************************************************************/
#include <iostream> // For input/output tasks
#include <cstdlib> // For random, system, exit, EXIT_SUCCESS, and EXIT_FAILURE
#include <unistd.h> // Posix API
#include <string> // String class
#include <sstream> // String stream

// Some macros
#define a_sizeof(x) sizeof(x) / sizeof(x[0])
#define show(a) cout << a << endl;
#define SHOW_AR(a) for (const auto& i : a) cout << i << " "; cout << endl;
#define NOPOS -1
#define LINE_BREAK cout << endl; for (int i = 0; i < 75; i++) cout << "-"; cout << endl;

// Using
using std::cout;
using std::endl;
using std::string;

class Vector {
public:
    // Members
    int components[3];

public:
    // Method declarations
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

// Entry
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

// Function I
/***************************************************************
Function: Default constructor

Use: Construct objects when user does not provide args

Arguments: none

Returns: 

Notes: 
***************************************************************/
Vector::Vector() {
    for (int i=0; i<3; ++i) components[i] = 0;
}

// Function II
/***************************************************************
Function: Parameterized Constructor

Use: Construct objects when user does provide args

Arguments: An integer array for components

Returns: 

Notes: 
***************************************************************/
Vector::Vector(int components[]) { this->set(components); } 


// Function III
/***************************************************************
Function: Set

Use: Sets the values of the users integer array to the data member `components`

Arguments: An integer array

Returns: void

Notes: 
***************************************************************/
void Vector::set(int _values[]) {

    // Loop to set values
    for (int i=0; i<3; ++i) {
        this->components[i] = _values[i];
    }
}

// Function IV
/***************************************************************
Function: add

Use: Adds the contents of the components data member and some integer array and returns a new Vector object

Arguments: An array of integers

Returns: A Vector object

Notes: 
***************************************************************/
Vector Vector::add(int _values[]) {

    // Simple loop to add each partner
    int tmp[3] = {0};
    for (int i=0; i<3; ++i) {
        tmp[i] = _values[i] + this->components[i];
    }
    return Vector(tmp);
}

// Function V
/***************************************************************
Function: add

Use: Overload for the add member, takes in Vector& instead of array

Arguments: Vector&

Returns: A Vector object

Notes: 
***************************************************************/
Vector Vector::add(Vector& other) { 

    // Simple loop to add each partner
    int tmp[3] = {0};
    for (int i=0; i<3; ++i) {
        tmp[i] =  this->components[i] + other.components[i];
    }
    return Vector(tmp);
}

// Function VI
/***************************************************************
Function: multiply

Use: Multiply vector componets by some integer scalar

Arguments: An integer scalar

Returns: A Vector object

Notes: 
***************************************************************/
Vector Vector::multiply(int scalar) {

    // Simple loop to scale each element
    int tmp[3] = {0};
    for (int i=0; i<3; ++i) {
        tmp[i] = this->components[i] * scalar;
    }
    return Vector(tmp);
}

// Function VII
/***************************************************************
Function: multiply overload

Use: Find the cross product of vector

Arguments: An integer array

Returns: A Vector object

Notes: 
***************************************************************/
Vector Vector::multiply(int values[]) {
    // Construct a new array using process for cross product
    int tmp[3] = {
        (this->components[1] * values[2]) - (this->components[2] *values[1]),
        (this->components[2] * values[0]) - (this->components[0] *values[2]),
        (this->components[0] * values[1]) - (this->components[1] *values[0])
    };
    return Vector(tmp);
}

// Function VIII
/***************************************************************
Function: Multiply overload 

Use: Find the cross product of vector with some other vector object

Arguments: Vector&

Returns: A Vector object

Notes: 
***************************************************************/
Vector Vector::multiply(Vector& other) {

    // Construct a new array using process for cross product
    int tmp[3] = {
        (this->components[1] * other.components[2]) - (this->components[2] * other.components[1]),
        (this->components[2] * other.components[0]) - (this->components[0] * other.components[2]),
        (this->components[0] * other.components[1]) - (this->components[1] * other.components[0])
    };
    return Vector(tmp);
}

// Function IX
/***************************************************************
Function: Subtract

Use: Subtracts components of Vector and some array of integers

Arguments: An array of integers

Returns: A Vector object

Notes: 
***************************************************************/
Vector Vector::subtract(int _values[]) {

    // Simple loop to subtract all partners
    int tmp[3] = {0};
    for (int i=0; i<3; ++i) {
        tmp[i] = this->components[i] - _values[i];
    }
    return Vector(tmp);
}

// Function X
/***************************************************************
Function: Subtract overload

Use: Overloads subtract method to take in a vector reference

Arguments: Vector&

Returns: A Vector object

Notes: 
***************************************************************/
Vector Vector::subtract(Vector& other) {

    // Simple loop to subtract all partners
    int tmp[3] = {0};
    for (int i=0; i<3; ++i) {
        tmp[i] = this->components[i] - other.components[i];
    }
    return Vector(tmp);
}

// Function XI
/***************************************************************
Function: Isequal

Use: Used to check if vector and some array of integers are the same

Arguments: An array of integers

Returns: bool

Notes: 
***************************************************************/
bool Vector::isEqual(int _values[]) {
    // return std::equal(std::begin(this->components), std::end(this->components), _values, _values+3);

    // Simple loop to make sure all values are the same
    bool flag = 1;
    for (int i=0; i<3; ++i) {
        if (this->components[i] != _values[i]) flag=0; 
    }
    return flag;
}

// Function XII
/***************************************************************
Function: isequal overload

Use: Used to check if two vectors are equal

Arguments: Vector&

Returns: bool

Notes: 
***************************************************************/
bool Vector::isEqual(Vector& other) {
    // return std::equal(std::begin(this->components), std::end(this->components), std::begin(other.components), std::end(other.components));

    // Simple loop to make sure all values are the same
    bool flag = 1;
    for (int i=0; i<3; ++i) {
        if (this->components[i] != other.components[i]) flag=0; 
    }
    return flag;
}

// Function XIII
/***************************************************************
Function: isSimilar 

Use: Used to see if a = n*b where n in Z, a is a vector and b is some integer array

Arguments: An array of integers

Returns: bool

Notes: 
***************************************************************/
bool Vector::isSimilar(int _values[]) {
     // This will hold the quotient of one set of componetss (other / this).
     // If the other columns (besides the zero-rows) have the same quotient, 
     // the condition a = n*b where n in Z holds and we have similarity
    double interest = 0.0;
    bool found = 0;
    bool flag = 1; // This flag is the decider for whether we proved similarity
    int count = 0; // used to hold the count of 2-zero columns 
    const double tolerance = 1e-6; // Useful to solve for floating point issues

    /* If any component is zero while its partner is non-zero, we return false. This automatically disrupts similarity
     We can also track any partners that are both zero in this step. Partners both being zero can be valid but disrupts the rest of the algorithm */ 
    for (int i=0; i<3; ++i) {
        if ((this->components[i] == 0 && _values[i] != 0) || (_values[i] == 0 && this->components[i] != 0)) { return false; } 
        else if (this->components[i] == 0 && _values[i] == 0) {
            ++count;
            continue; 
        }
    }

    // Csases where we have two or three columns of zeros
    if (count == 2 || count == 3) { 
        for (int i=0; i<3; ++i) { // Want to loop through and find the place that holds non zero terms
            if (this->components[i] !=0) { 
                return (_values[i] % this->components[i] == 0 ? 1 : 0); // Here we check for similarity with moudar arithmetic
            } 
        }
        return true; // If we reach this point, we know we have all zeros
    } else { // If we have either zero or one set of partners with values of zero
        double check = 0.0;
        for (int i=0; i<3; ++i) { // We loop through to find the non-zero positions
            interest = static_cast<double>(_values[i]) / this->components[i];
            if (this->components[i] != 0 && !found) {
                check = interest; // This is the quotient we check against the others
                found=1; // We can stop our search
            }
            if (found && ((std::abs(interest-check)) > tolerance)) flag=0;  // Note: \abs{x} < a \implies -a < x < a
        }
    } return flag;

}

// Function XIV
/***************************************************************
Function: isSimilar overload

Use: Used to see if a = n*b where n in Z, and a,b are both vectors

Arguments: Reference to a vector

Returns: bool

Notes: My solution assuming neither vector has zeros was alot cleaner, but things got messy once I considered that this may not always hold
***************************************************************/
bool Vector::isSimilar(Vector& other) {

     // This will hold the quotient of one set of componetss (other / this).
     // If the other columns (besides the zero-rows) have the same quotient, 
     // the condition a = n*b where n in Z holds and we have similarity
    double interest = 0.0;
    double check = 0.0;
    bool found = 0;
    bool flag = 1; // This flag is the decider for whether we proved similarity
    int count = 0; // used to hold the count of 2-zero columns 
    const double tolerance = 1e-6; // Useful to solve for floating point issues

    /* If any component is zero while its partner is non-zero, we return false. This automatically disrupts similarity
     We can also track any partners that are both zero in this step. Partners both being zero can be valid but disrupts the rest of the algorithm */ 
    for (int i=0; i<3; ++i) {
        if ((this->components[i] == 0 && other.components[i] != 0) || (other.components[i] == 0 && this->components[i] != 0)) { return false; } 
        else if (this->components[i] == 0 && other.components[i] == 0) {
            ++count;
            continue; 
        }

    }
    // Csases where we have two or three columns of zeros
    if (count == 2 || count == 3) { 
        for (int i=0; i<3; ++i) { // Want to loop through and find the place that holds non zero terms
            if (this->components[i] !=0) { 
                return (other.components[i] % this->components[i] == 0 ? 1 : 0); // Here we check for similarity with moudar arithmetic
            } 
        }
        return true; // If we reach this point, we know we have all zeros
    } else { // If we have either zero or one set of partners with values of zero
        for (int i=0; i<3; ++i) { // We loop through to find the non-zero positions
            interest = static_cast<double>(other.components[i]) / this->components[i];
            if (this->components[i] != 0 && !found) {
                check = interest; // This is the quotient we check against the others
                found=1; // We can stop our search
            }
            if (found && ((std::abs(interest - check)) > tolerance)) flag=0;  // Note: \abs{x} < a \implies -a < x < a
        }
    } return flag;
}

// Function XV
/***************************************************************
Function: To string

Use: Build Vector repr

Arguments: None

Returns: C++-String

Notes: <3 stringstream
***************************************************************/
string Vector::to_string() {
    // Here we use a stringstream to build the string we need
    std::ostringstream oss;
    oss << "<" << this->components[0] << "," << this->components[1] << "," << this->components[2] << ">"; 
    return oss.str();



}

