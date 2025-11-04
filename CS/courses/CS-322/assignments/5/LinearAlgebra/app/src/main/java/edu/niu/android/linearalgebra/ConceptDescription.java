/************************************************************************
 * *
 * CSCI 322/522 Assignment 4 fall 25 *
 * *
 * App Name: Linear Algebra
 * *
 * Class Name: ConceptDescription.java *
 * *
 * Developer(s): Nate Warner *
 * *
 * Due Date: 11/03/2025 *
 * *
 * Purpose: Model to store descriptions of concepts
 * *
 ************************************************************************/
package edu.niu.android.linearalgebra;

public class ConceptDescription {
    // Singular description
    private String desc;

    // All possible concept descriptions
    public static String[] descriptions = {
            "A matrix is a rectangular array of numbers representing a linear transformation.",
            "A vector is an ordered list of numbers in ℝⁿ.",
            "Ax = b represents a system of linear equations.",
            "A can be decomposed into L and U (or PA = LU) for solving systems efficiently.",
            "A is invertible if and only if det(A) ≠ 0.",
            "This represents an elementary matrix used for Gaussian elimination.",
            "A is diagonalizable if A = PDP⁻¹, where D has eigenvalues.",
            "A symmetric positive definite matrix can be written as A = RᵀR.",
            "A is positive definite if xᵀAx > 0 for all nonzero x."
    };

    // Default constructor
    public ConceptDescription() {
        desc = "";
    }

    // Parameterized constructor
    public ConceptDescription(String desc) {
        this.desc = desc;
    }

    // Getter
    public String getDesc() {
        return desc;
    }

    // setter
    public void setDesc(String desc) {
        this.desc = desc;
    }
}
