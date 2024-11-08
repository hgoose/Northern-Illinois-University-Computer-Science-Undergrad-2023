#include <iomanip>
#include <iostream>
#include "vectorn.h"

using std::ostream;

/**
 * Constructs a vectorn with the contents of an array.
 *
 * @param ar An array whose contents are copied.
 * @param n Size of the array.
 */
vectorn::vectorn(const double ar[], size_t n)
{
    v_array = new double[n];
    v_capacity = n;
   
    for (size_t i = 0; i < n; i++)
        v_array[i] = ar[i];
}

/**
 * Constructs a vectorn with a copy of the elements of another vectorn.
 *
 * @param x Another vectorn object whose contents are copied.
 */
vectorn::vectorn(const vectorn& x)
{
    v_capacity = x.v_capacity;
    v_array = new double[v_capacity];
   
    for (size_t i = 0; i < v_capacity; i++)
        v_array[i] = x.v_array[i];
}

/**
 * Destroys the vectorn object.
 */
vectorn::~vectorn()
{
   clear();
}

/**
 * Assigns new contents to a vectorn.
 *
 * @param x A vectorn object whose contents are copied.
 *
 * @return The value of the modified left operand. 
 */
vectorn& vectorn::operator=(const vectorn& x)
{
    if (this != &x)
    {
        if (v_capacity != x.v_capacity)
        {
            delete[] v_array;
            v_capacity = x.v_capacity;
            v_array = new double[v_capacity];
        }
         
        for (size_t i = 0; i < v_capacity; i++)
            v_array[i] = x.v_array[i];
    }
   
    return *this;
}

/**
 * Sets a vectorn back to empty, deleting its dynamic storage.
 */
void vectorn::clear()
{
    delete[] v_array;
   
    v_capacity = 0;
    v_array = nullptr;   
}

/**
 * Returns the number of elements in the vectorn.
 *
 * @return The number of elements in the vectorn.
 */
size_t vectorn::size() const
{
    return v_capacity;
}
   
/**
 * Adds two vectorn objects to produce a vectorn result.
 *
 * @param rhs A vectorn on the right-hand side of the operator.
 *
 * @return A vectorn that contains the result of adding the elements
 *         of the arrays of the two vectorn objects.
 */
vectorn vectorn::operator+(const vectorn& rhs) const {

    const size_t size = (this->v_capacity <= rhs.v_capacity ? this->v_capacity : rhs.v_capacity);

    double* sums = new double[size];

    for (size_t i=0; i<size; ++i)  {

        sums[i] = this->v_array[i] + rhs.v_array[i];

    }
    return vectorn(sums,size);

    delete[] sums;
}

/**
 * Subtracts two vectorn objects to produce a vectorn result.
 *
 * @param rhs A vectorn on the right-hand side of the operator.
 *
 * @return A vectorn that contains the result of subrtracting the 
 *         elements of the arrays of the two vectorn objects.
 */
vectorn vectorn::operator-(const vectorn& rhs) const   
{

    const size_t size = (this->v_capacity <= rhs.v_capacity ? this->v_capacity : rhs.v_capacity);

    double* sums = new double[size];

    for (size_t i=0; i<size; ++i)  {

        sums[i] = this->v_array[i] - rhs.v_array[i];

    }
    return vectorn(sums,size);

    delete[] sums;

}

/**
 * Computes the scalar product of two vectorn objects by individually 
 * multiplying the elements of the arrays of the two vectorn objects
 * and then adding the results.
 *
 * @param rhs A vectorn on the right-hand side of the operator.
 *
 * @return A double that contains the scalar product.
 */
double vectorn::operator*(const vectorn& rhs) const   
{

    size_t size = (this->v_capacity <= rhs.v_capacity ? this->v_capacity : rhs.v_capacity);

    double ret = 0.0f;

    for (size_t i = 0; i<size; ++i) {
        ret+= this->v_array[i] * rhs.v_array[i];
    }

    return ret;
}
   
/**
 * Multiplies the elements of a vectorn's array by a double, producing
 * a vectorn result.
 *
 * @param rhs A double on the right-hand side of the operator.
 *
 * @return A vectorn containing the results of the multiplication.
 */
vectorn vectorn::operator*(double rhs) const   
{

    double* ret = new double[this->v_capacity];
    for (size_t i=0; i<this->v_capacity; ++i) {
        ret[i] = this->v_array[i] * rhs;

    }
    return vectorn(ret,this->v_capacity);

    delete[] ret;
}

/**
 * Returns a copy of the element at the position n in a constant 
 * vectorn.
 *
 * @param n Position of an element in the vectorn.
 *
 * @return The element at the specified position in the vectorn.
 */
double vectorn::operator[](size_t n) const
{

    return this->v_array[n];

}
   
/**
 * Returns a reference to the element at the position n in e vectorn.
 *
 * @param n Position of an element in the vectorn.
 *
 * @return The element at the specified position in the vectorn.
 */
double& vectorn::operator[](size_t n)
{
    return this->v_array[n];

}

/**
 * Compares two vectorn objects for equality.
 *
 * @param rhs The vectorn on the right-hand side of the operator.
 *
 * @return true if the vectorn objects are equal, false otherwise.
 *
 * @note Two vectorn objects are equal if (1) they have the same
 *       v_capacity and (2) all of the elements of their respective
 *       arrays match.
 */
bool vectorn::operator==(const vectorn & rhs) const
{
    if (this->v_capacity != rhs.v_capacity) return false;

    for (size_t i = 0; i<this->v_capacity; ++i) {
        if (this->v_array[i] != rhs.v_array[i]) return false;
    }
    return true;
}

/**
 * Insets the elements of the vectorn into an output stream.
 *
 * @param os The output stream.
 * @param obj A vectorn object to insert into the stream.
 *
 * @return The output stream.
 */
ostream& operator<<(ostream& os, const vectorn& obj)
{
    int i;
   
    os << "(";
    for (i = 0; i < (int) obj.v_capacity - 1; i++)
        os << obj.v_array[i] << ", ";
      
    if (i < (int) obj.v_capacity)
        os << obj.v_array[i];
      
    os << ")";
   
    return os; 
}

/**
 * Multiplies a double by the elements of a vectorn's array, producing
 * a vectorn result.
 *
 * @param lhs A double on the left-hand side of the operator.
 * @param rhs A vectorn on the right-hand side of the operator.
 *
 * @return A vectorn containing the results of the multiplication.
 */
vectorn operator*(double lhs, const vectorn& rhs) {

    return rhs * lhs;
}
