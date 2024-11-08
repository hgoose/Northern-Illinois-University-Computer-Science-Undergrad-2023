#ifndef VECTOR3_H
#define VECTOR3_H

#include <iostream>
using std::ostream;

class vector3
{
    friend std::ostream& operator<<(std::ostream&, const vector3&);
    friend vector3 operator*(double, const vector3&);

private:

    double x = 0.0,
           y = 0.0,
           z = 0.0;
         
public:

    vector3() = default;
    vector3(double, double, double);

    vector3 operator+(const vector3&) const;
    vector3 operator-(const vector3&) const;
    double operator*(const vector3&) const;
    vector3 operator*(double) const;
      
    double operator[](size_t) const;
    double& operator[](size_t);
      
    bool operator==(const vector3&) const;

    friend ostream& operator<<(ostream& os, const vector3& obj);
    friend vector3 operator*(double, const vector3&);

};      

#endif
