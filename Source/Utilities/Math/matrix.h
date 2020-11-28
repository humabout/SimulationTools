// matrix.h


#ifndef MATRIX_H
#define MATRIX_H


// Inclusions
#include <cassert>
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
    // Data
    union
    {
      double e[9];
      Vector row[3];
      struct
      {
        Vector row_1;
        Vector row_2;
        Vector row_3;
      };
      struct
      {
        double e11;
        double e12;
        double e13;
        double e21;
        double e22;
        double e23;
        double e31;
        double e32;
        double e33;
      };
    };

    // Construtors
    Matrix();
    Matrix(double e11_, double e12_, double e13_,
           double e21_, double e22_, double e23_,
           double e31_, double e32_, double e33_);
    Matrix(const Matrix& m_);


    // Destructor
    ~Matrix();


    // Accessors
    Vector& operator[](unsigned int row_);


    // Setters
    void operator=(const Matrix& m_);
    void set(double e11_, double e12_, double e13_,
             double e21_, double e22_, double e23_,
             double e31_, double e32_, double e33_);
    void set(const Matrix& m_);
    void setRows(const Vector& row_1_,
                 const Vector& row_2_,
                 const Vector& row_3_);
    void setColumns(const Vector& col_1_,
                    const Vector& col_2_,
                    const Vector& col_3_);

    // Comparison Operators
    bool operator==(const Matrix& m_) const;
    bool operator!=(const Matrix& m_) const;


    // Unary -
    Matrix operator-() const;


    // Addition & Subtraction
    Matrix operator+(const Matrix& m_) const;
    void operator+=(const Matrix& m_);
    Matrix operator-(const Matrix& m_) const;
    void operator-=(const Matrix& m_);


    // Scalar Multiplication & Division
    // NOTE: Scalar right-multiplication is defined in an override for doubles.
    Matrix operator*(double s_) const;
    void operator*=(double s_);
    Matrix operator/(double s_) const;
    void operator/=(double s_);


    // Vector Multiplication
    Vector operator*(const Vector& v_) const;


    // Matrix Multiplication
    Matrix operator*(const Matrix& m_) const;
    void operator*=(const Matrix& m_);


    // Transpose
    Matrix transpose(void) const;


    // Trace
    double trace(void) const;


    // Determinant
    double determinant(void) const;

    
    // Inverse
    Matrix inverse(void) const;
    void invert(void);


    // Zeroize
    void zeroize(void);


    // Identity
    static Matrix identity(void);


  private:


  }; // !Matrix


} // !math


// Right-Multiplication of Matrices by Doubles
math::Matrix operator*(double              s_, 
                       const math::Matrix& m_);




#endif // !MATRIX_H
