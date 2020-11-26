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
    // Data
    union
    {
      double e[9];
      Vector row[3];
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
    Matrix()
    {
      zeroize();
    }

    Matrix(double e11_, double e12_, double e13_,
           double e21_, double e22_, double e23_,
           double e31_, double e32_, double e33_)
    {
      set(e11_, e12_, e13_,
          e21_, e22_, e23_,
          e31_, e32_, e33_);
    }

    Matrix(const Matrix& m_)
    {
      set(m_);
    }


    // Destructor
    ~Matrix()
    {
      // Nothing to delete.
    }


    // Accessors
    Vector& operator[](unsigned int row_)
    {
      return row[row_];
    }

    Vector& row(unsigned int row_)
    {
      // Indexed from zero
      return row[row_];
    }

    Vector& column(unsigned int col_)
    {
      // Indexed from zero
      Vector(e[col_],
             e[col_ + 3],
             e[col_ + 6]);

    }


    // Setters
    void operator=(const Matrix& m_)
    {
      this->e11 = m_.e11;
      this->e12 = m_.e12;
      this->e13 = m_.e13;
      this->e21 = m_.e21;
      this->e22 = m_.e22;
      this->e23 = m_.e23;
      this->e31 = m_.e31;
      this->e32 = m_.e32;
      this->e33 = m_.e33;
    }

    void set(double e11_, double e12_, double e13_,
             double e21_, double e22_, double e23_,
             double e31_, double e32_, double e33_)
    {
      this->e11 = e11_;
      this->e12 = e12_;
      this->e13 = e13_;
      this->e21 = e21_;
      this->e22 = e22_;
      this->e23 = e23_;
      this->e31 = e31_;
      this->e32 = e32_;
      this->e33 = e33_;
    }

    void set(const Matrix& m_)
    {
      (*this) = m_;
    }

    // Comparison Operators
    bool operator==(const Matrix& m_)
    {
      for (unsigned int i = 0; i < 9; i++)
      {
        if (this->e[i] != m_.e[i])
        {
          return false;
        }
      }
      return true;
    }

    bool operator!=(const Matrix& m_)
    {
      return !(*this == m_);
    }


    // Unary -
    Matrix operator-()
    {
      return Matrix(-e11, -e12, -e13,
                    -e21, -e22, -e23,
                    -e31, -e32, -e33);
    }


    // Addition & Subtraction
    Matrix operator+(const Matrix& m_)
    {
      return Matrix(this->e11 + m_.e11, this->e12 + m_.e12, this->e13 + m_.e13,
                    this->e21 + m_.e21, this->e22 + m_.e22, this->e23 + m_.e23,
                    this->e31 + m_.e31, this->e32 + m_.e32, this->e33 + m_.e33);
    }

    void operator+=(const Matrix& m_)
    {
      *this = *this + m_;
    }

    Matrix operator-(const Matrix& m_)
    {
      return Matrix(this->e11 - m_.e11, this->e12 - m_.e12, this->e13 - m_.e13,
                    this->e21 - m_.e21, this->e22 - m_.e22, this->e23 - m_.e23,
                    this->e31 - m_.e31, this->e32 - m_.e32, this->e33 - m_.e33);
    }

    void operator-=(const Matrix& m_)
    {
      *this = *this - m_;
    }


    // Scalar Multiplication & Division
    // NOTE: Scalar right-multiplication is defined in an override for doubles.
    Matrix operator*(double s_)
    {
      return Matrix(this->e11 * s_, this->e12 * s_, this->e13 * s_,
                    this->e21 * s_, this->e22 * s_, this->e23 * s_,
                    this->e31 * s_, this->e32 * s_, this->e33 * s_);
    }

    void operator*=(double s_)
    {
      *this = *this * s_;
    }

    Matrix operator/(double s_)
    {
      // TODO: Make this more robust against division by near-zero. Perahps
      //       divide by a default value if near zero?
      assert(abs(s_) < math::DIVIDE_BY_ZERO_TOLERANCE);
      return (*this) * (1 / s_);
    }

    void operator/=(double s_)
    {
      *this = *this / s_;
    }


    // Vector Multiplication
    Vector operator*(const Vector& v_)
    {
      return Vector(this->e11 * v_.e1 + this->e12 * v_.e2 + this->e13 * v_.e3,
                    this->e21 * v_.e1 + this->e22 * v_.e2 + this->e23 * v_.e3,
                    this->e31 * v_.e1 + this->e32 * v_.e2 + this->e33 * v_.e3);
    }

    // Matrix Multiplication
    Matrix operator*(const Matrix& m_)
    {
      return Matrix(this->e11 * m_.e11 + this->e12 * m_.e21 + this->e13 * m_.e31,
                    this->e11 * m_.e12 + this->e12 * m_.e22 + this->e13 * m_.e32,
                    this->e11 * m_.e13 + this->e12 * m_.e23 + this->e13 * m_.e33,

                    this->e21 * m_.e11 + this->e22 * m_.e21 + this->e23 * m_.e31,
                    this->e21 * m_.e12 + this->e22 * m_.e22 + this->e23 * m_.e32,
                    this->e21 * m_.e13 + this->e22 * m_.e23 + this->e23 * m_.e33,

                    this->e31 * m_.e11 + this->e32 * m_.e21 + this->e33 * m_.e31,
                    this->e31 * m_.e12 + this->e32 * m_.e22 + this->e33 * m_.e32,
                    this->e31 * m_.e13 + this->e32 * m_.e23 + this->e33 * m_.e33);
    }

    // Transpose
    Matrix transpose(void)
    {
      return Matrix(this->e11, this->e21, this->e31,
                    this->e12, this->e22, this->e32,
                    this->e13, this->e23, this->e33);
    }

    // Determinant
    double determinant(void)
    {
      return e11 * (e22 * e33 - e23 * e32) +
             e12 * (e31 * e23 - e33 * e21) +
             e13 * (e21 * e32 - e31 * e23);
    }

    
    // Inverse
    virtual Matrix inverse(void)
    {
      //Calculating Determinant
      double det = this->determinant();

      // Verifying the matrix is invertible
      assert(abs(det) > math::DIVIDE_BY_ZERO_TOLERANCE);

      // Calculating Adjoint Matrix
      Matrix adjoint(e22 * e33 - e21 * e12,
                     e13 * e31 - e12 * e22,
                     e12 * e23 - e13 * e22,

                     e23 * e31 - e21 * e33,
                     e11 * e33 - e13 * e31,
                     e21 * e13 - e11 * e23,

                     e21 * e32 - e31 * e22,
                     e31 * e12 - e11 * e32,
                     e11 * e22 - e21 * e12);
      return adjoint / det;
    }

    virtual void invert(void)
    {
      *this = this->inverse();
    }


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


  }; // !Matrix


  // Right-Multiplication of Matrices by Doubles
  Matrix operator*(double s_, const Matrix& m_)
  {
    return Matrix(m_.e11 * s_, m_.e12 * s_, m_.e13 * s_,
                  m_.e21 * s_, m_.e22 * s_, m_.e23 * s_,
                  m_.e31 * s_, m_.e32 * s_, m_.e33 * s_);
  }


} // !math




#endif // !MATRIX_H
