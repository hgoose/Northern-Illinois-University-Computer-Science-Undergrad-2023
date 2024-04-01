//***************************************************************************
//  matrix.cpp
//
//  Matrix Operations
//  MatrixOperationsA10
//
//  Created by Nate Warner z2004109
//
//***************************************************************************

#include "matrix.h"


/**
 * Constructs a matrix object from a 2x2 integer array. It copies the elements
 * of the provided array into the matrix data member
 * 
 * @param arr A 2x2 integer array containing the initial values for the matrix.
 */
matrix::matrix(int arr[][2]) {

    // Loop through entries
    for (int i=0; i<2; ++i) {
        for (int j=0; j<2; ++j) {
            // Assign array elements to matrix member
            this->m_matrix[i][j] = arr[i][j];
        }
    }
}


/**
 * Calculates and returns the determinant of the matrix.
 * 
 * @return The determinant of the matrix as an integer.
 */
int matrix::determinant() const {
    // Computation for determinant
    return this->m_matrix[0][0] * this->m_matrix[1][1] - (this->m_matrix[0][1] * this->m_matrix[1][0]);
}


/**
 * Overloads the addition operator to add two matrices. The operation is
 * performed element-wise.
 * 
 * @param other The matrix to be added to this matrix.
 * @return A new matrix that is the result of the addition.
 */
matrix matrix::operator+(const matrix& other) const {

    // Array to store sums
    int arr[2][2] = {{0}};

    // Loop through entries
    for (int i=0; i<2; ++i) {
        for (int j=0; j<2; ++j) {
            // Sum the entries, store in array
            arr[i][j] = this->m_matrix[i][j] + other.m_matrix[i][j];
        }
    }

    // Return new object
    return matrix{arr};
}


/**
 * Overloads the multiplication operator to multiply the matrix by a scalar.
 * 
 * @param scalar The scalar value to multiply the matrix by.
 * @return A new matrix that is the result of the multiplication.
 */
matrix matrix::operator*(const int& scalar) const {

    // Array to store scalar products
    int arr[2][2];

    // Loop through entries
    for (int i=0; i<2; ++i) {
        for (int j=0; j<2; ++j) {
            // Multiply entry by scalar, store in new array
            arr[i][j] = this->m_matrix[i][j] * scalar;
        }
    }

    // Return new object
    return matrix{arr};
}


/**
 * Overloads the multiplication operator to multiply this matrix by another matrix.
 * The multiplication is done according to matrix multiplication rules.
 * 
 * @param other The matrix to multiply this matrix by.
 * @return A new matrix that is the result of the multiplication.
 */
matrix matrix::operator*(const matrix& other) const {

    // Build a new array based on multiplication rules
    int arr[2][2] = {
        {
            this->m_matrix[0][0] * other.m_matrix[0][0] + this->m_matrix[0][1] * other.m_matrix[1][0], 
            this->m_matrix[0][0] * other.m_matrix[0][1] + this->m_matrix[0][1] * other.m_matrix[1][1]
        },
        {
            this->m_matrix[1][0] * other.m_matrix[0][0] + this->m_matrix[1][1] * other.m_matrix[1][0], 
            this->m_matrix[1][0] * other.m_matrix[0][1] + this->m_matrix[1][1] * other.m_matrix[1][1]
        } 
    };

    // Return new object
    return matrix{arr};
}


/**
 * Overloads the equality operator to compare this matrix with another matrix.
 * 
 * @param other The matrix to compare this matrix to.
 * @return True if the matrices are equal, false otherwise.
 */
bool matrix::operator==(const matrix& other) const {

    // Loop through the entries
    for (int i=0; i<2; ++i) {
        for (int j=0; j<2; ++j) {
            // Check if the entries do not match
            if (this->m_matrix[i][j] != other.m_matrix[i][j]) {
                return false;
            }
        }
    }

    // All entries match
    return true;
}


/**
 * Overloads the inequality operator to compare this matrix with another matrix.
 * 
 * @param other The matrix to compare this matrix to.
 * @return True if the matrices are not equal, false otherwise.
 */
bool matrix::operator!=(const matrix& other) const {

    // Loop through the entries
    for (int i=0; i<2; ++i) {
        for (int j=0; j<2; ++j) {
            // Check if the elements do not match
            if (this->m_matrix[i][j] == other.m_matrix[i][j]) {
                return false;
            }
        }
    }
    // Elements do not match
    return true;
}


/**
 * Overloads the insertion operator to output the matrix to an output stream.
 * 
 * @param os The output stream to write to.
 * @param obj The matrix object to output.
 * @return The output stream.
 */
std::ostream& operator<<(std::ostream& os, const matrix& obj) {

    os << "["; // Output the initial bracket
    for (int i=0; i<2; ++i) {
        os << "["; // Inner bracket
        for (int j=0; j<2; ++j) {
            // Ternary to see if we need a comma after the element
            j == 0 ? os << obj.m_matrix[i][j] << ", " : os << obj.m_matrix[i][j];
        }
        // Ternary to see if the ending bracket should have a comma
        i == 0 ? os << "], " : os << "]"; 
    }
    os << "]";  // Output the terminal bracket

    return os;
}


/**
 * Overloads the multiplication operator to multiply a scalar by a matrix.
 * This allows for the scalar to be the left-hand operand.
 * 
 * @param scalar The scalar value to multiply the matrix by.
 * @param obj The matrix to be multiplied.
 * @return A new matrix that is the result of the multiplication.
 */
matrix operator*(const int& scalar, const matrix& obj) {
    return obj * scalar; // Make use of the member function for scalar multiplication
}
