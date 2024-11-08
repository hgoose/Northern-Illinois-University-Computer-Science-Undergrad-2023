#ifndef VECTORN_H
#define VECTORN_H

#include <iostream>

class vectorn
{
    friend std::ostream& operator<<(std::ostream&, const vectorn&);
    friend vectorn operator*(double, const vectorn&);

private:

    double* v_array = nullptr;   
    size_t v_capacity = 0;
         
public:

    vectorn() = default;
    vectorn(const double[], size_t);
    vectorn(const vectorn&);
    ~vectorn();
    vectorn& operator=(const vectorn&);

    void clear();
    size_t size() const;

    vectorn operator+(const vectorn&) const;
    vectorn operator-(const vectorn&) const;
    double operator*(const vectorn&) const;
    vectorn operator*(double) const;
      
    double operator[](size_t) const;
    double& operator[](size_t);
      
    bool operator==(const vectorn&) const;
};      

#endif
