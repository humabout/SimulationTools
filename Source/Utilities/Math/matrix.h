// matrix.h


#ifndef MATRIX_H
#define MATRIX_H


// Inclusions
#include <array>
#include <cassert>
#include <vector>
#include "math_config.h"
#include "vector.h"


//------------------------------------------------------------------------------
// Name:    math
// Purpose: This namespace holds all math objects, functions, and constants.
//------------------------------------------------------------------------------
namespace math
{


  //----------------------------------------------------------------------------
  // Name:    Matrix
  // Purpose: This class holds a 3x3 matrix and all of the operators and methods
  //          that operate on 3x3 matrices.
  //----------------------------------------------------------------------------
  class Matrix
  {
  public:
    // Construtors
    // Destructor
    // Accessors
    Vector& operator[](unsigned int row_)
    {
      return e[row_];
    }


    // Setters
    // Comparison Operators
    // Unary -
    // Addition & Subtraction
    // Scalar Multiplication & Division
    // Vector Multiplication
    // Matrix Multiplication
    // Transpose
    // Inverse
    // Determinant
    // Zeroize
    void zeroize(void)
    {
      this->set(0, 0, 0,
                0, 0, 0,
                0, 0, 0);
    }


    // Identity
    static Matrix identity(void)
    {
      return Matrix(1, 0, 0,
                    0, 1, 0,
                    0, 0, 1);
    }


  private:
    // Row Vectors
    Vector e[3];


  }; // !Matrix



} // !math




#endif // !MATRIX_H
