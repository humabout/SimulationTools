// matrix.cpp


// Inclusions
#include <cassert>
#include "math_config.h"
#include "matrix.h"
#include "vector.h"


//------------------------------------------------------------------------------
// Name:    Matrix
// Purpose: Default Constructor. Initializes the matrix to a zero matrix.
//------------------------------------------------------------------------------
math::Matrix::Matrix()
{
  this->zeroize();
}


//------------------------------------------------------------------------------
// Name:    Matrix
// Purpose: Copy Constructor.
//------------------------------------------------------------------------------
math::Matrix::Matrix(const Matrix& m_)
{
  this->set(m_);
}


//------------------------------------------------------------------------------
// Name:    Matrix
// Purpose: Constructor Overload. Sets this matrix's elements equal to those 
//          provided in the arguments.
//------------------------------------------------------------------------------
math::Matrix::Matrix(double e11_, double e12_, double e13_,
                     double e21_, double e22_, double e23_,
                     double e31_, double e32_, double e33_)
{
  this->set(e11_, e12_, e13_,
            e21_, e22_, e23_,
            e31_, e32_, e33_);
}


//------------------------------------------------------------------------------
// Name:    ~Matrix
// Purpose: Destructor. This class has nothing to delete and so does nothing.
//------------------------------------------------------------------------------
math::Matrix::~Matrix()
{
  // Does nothing
}


//------------------------------------------------------------------------------
// Name:    operator[]
// Purpose: Returns the row given in the input as indexed from zero.
//------------------------------------------------------------------------------
math::Vector& math::Matrix::operator[](unsigned int row_)
{
  return row[row_];
}


//------------------------------------------------------------------------------
// Name:    operator=
// Purpose: Sets this matrix equal to another matrix.
//------------------------------------------------------------------------------
void math::Matrix::operator=(const Matrix& m_)
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


//------------------------------------------------------------------------------
// Name:    set
// Purpose: Sets this matrix's elements equal to those provided.
//------------------------------------------------------------------------------
void math::Matrix::set(double e11_, double e12_, double e13_,
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


//------------------------------------------------------------------------------
// Name:    set
// Purpose: Sets this matrix equal to another one.
//------------------------------------------------------------------------------
void math::Matrix::set(const Matrix& m_)
{
  *this = m_;
}


//------------------------------------------------------------------------------
// Name:    setRows
// Purpose: Sets this matrix's rows to those provided in the arguments.
//------------------------------------------------------------------------------
void math::Matrix::setRows(const Vector& row_1_,
                           const Vector& row_2_,
                           const Vector& row_3_)
{
  this->row_1 = row_1_;
  this->row_2 = row_2_;
  this->row_3 = row_3_;
}


//------------------------------------------------------------------------------
// Name:    setColumns
// Purpose: Sets this matrix's columns to those provided in the arguments.
//------------------------------------------------------------------------------
void math::Matrix::setColumns(const Vector& col_1_,
                              const Vector& col_2_,
                              const Vector& col_3_)
{
  this->row_1 = col_1_;
  this->row_2 = col_2_;
  this->row_3 = col_3_;
  this->transpose();
}


//------------------------------------------------------------------------------
// Name:    operator==
// Purpose: Returns true if the two matrices are equal.
//------------------------------------------------------------------------------
bool math::Matrix::operator==(const Matrix& m_) const
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


//------------------------------------------------------------------------------
// Name:    operator!=
// Purpose: Returns true if the two matrices are not equal.
//------------------------------------------------------------------------------
bool math::Matrix::operator!=(const Matrix& m_) const
{
  return !(*this == m_);
}


//------------------------------------------------------------------------------
// Name:    operator-
// Purpose: Returns the negative of the matrix.
//------------------------------------------------------------------------------
math::Matrix math::Matrix::operator-() const
{
  return Matrix(-e11, -e12, -e13,
                -e21, -e22, -e23,
                -e31, -e32, -e33);
}


//------------------------------------------------------------------------------
// Name:    operator+
// Purpose: Returns the sum of two matrices.
//------------------------------------------------------------------------------
math::Matrix math::Matrix::operator+(const Matrix& m_) const
{
  return Matrix(this->e11 + m_.e11, this->e12 + m_.e12, this->e13 + m_.e13,
                this->e21 + m_.e21, this->e22 + m_.e22, this->e23 + m_.e23,
                this->e31 + m_.e31, this->e32 + m_.e32, this->e33 + m_.e33);
}


//------------------------------------------------------------------------------
// Name:    operator+=
// Purpose: Sets this matrix to the sum of itself and another matrix.
//------------------------------------------------------------------------------
void math::Matrix::operator+=(const Matrix& m_)
{
  *this = *this + m_;
}


//------------------------------------------------------------------------------
// Name:    operator-
// Purpose: Returns the difference of two matrices.
//------------------------------------------------------------------------------
math::Matrix math::Matrix::operator-(const Matrix& m_) const
{
  return *this + -m_;
}


//------------------------------------------------------------------------------
// Name:    operator-=
// Purpose: Sets this matrix to the difference of itself and another matrix.
//------------------------------------------------------------------------------
void math::Matrix::operator-=(const Matrix& m_)
{
  *this = *this - m_;
}


//------------------------------------------------------------------------------
// Name:    operator*
// Purpose: Returns the product of this matrix and a scalar.
//------------------------------------------------------------------------------
math::Matrix math::Matrix::operator*(double s_) const
{
  return Matrix(s_ * this->e11, s_ * this->e12, s_ * this->e13,
                s_ * this->e21, s_ * this->e22, s_ * this->e23,
                s_ * this->e31, s_ * this->e32, s_ * this->e33);
}


//------------------------------------------------------------------------------
// Name:    operator*=
// Purpose: Sets this matrix to itself times a scalar.
//------------------------------------------------------------------------------
void math::Matrix::operator*=(double s_)
{
  *this = *this * s_;
}


//------------------------------------------------------------------------------
// Name:    operator/
// Purpose: Returns the quotient of this matrix and a scalar, if it exists. If 
//          not, it crashes the program.
// TODO:    Make this more robust against division by near-zero. Perahps
//          divide by a default value if near zero?
//------------------------------------------------------------------------------
math::Matrix math::Matrix::operator/(double s_) const
{
  // Checking if this quotient exists.
  assert(abs(s_) > math::DIVIDE_BY_ZERO_TOLERANCE);
  return *this * (1 / s_);
}


//------------------------------------------------------------------------------
// Name:    operator/=
// Purpose: Sets this matrix equal to itself divided by a scalar, if it exists. 
//          If not, it crashes the program. This is performed within the / 
//          operator.
// TODO:    Make this more robust against division by near-zero. Perahps
//          divide by a default value if near zero?
//------------------------------------------------------------------------------
void math::Matrix::operator/=(double s_)
{
  *this = *this / s_;
}


//------------------------------------------------------------------------------
// Name:    operator*
// Purpose: Returns the product of a vector premultiplied by this matrix.
//------------------------------------------------------------------------------
math::Vector math::Matrix::operator*(const Vector& v_) const
{
  return Vector(this->e11 * v_.e1 + this->e12 * v_.e2 + this->e13 * v_.e3,
                this->e21 * v_.e1 + this->e22 * v_.e2 + this->e23 * v_.e3,
                this->e31 * v_.e1 + this->e32 * v_.e2 + this->e33 * v_.e3);
}


//------------------------------------------------------------------------------
// Name:    operator*
// Purpose: Returns the product of a matrix premultiplied by this matrix.
//------------------------------------------------------------------------------
math::Matrix math::Matrix::operator*(const Matrix& m_) const
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


//------------------------------------------------------------------------------
// Name:    operator*=
// Purpose: Sets this matrix equal to the product of a matrix premultiplied by 
//          this matrix.
//------------------------------------------------------------------------------
void math::Matrix::operator*=(const Matrix& m_)
{
  *this = *this * m_;
}


//------------------------------------------------------------------------------
// Name:    transpose
// Purpose: Returns the transpose of the matrix.
//------------------------------------------------------------------------------
math::Matrix math::Matrix::transpose(void) const
{
  return Matrix(this->e11, this->e21, this->e31,
                this->e12, this->e22, this->e32,
                this->e13, this->e23, this->e33);
}


//------------------------------------------------------------------------------
// Name:    trace
// Purpose: Returns the trace of the matrix.
//------------------------------------------------------------------------------
double math::Matrix::trace(void) const
{
  return e11 + e22 + e33;
}


//------------------------------------------------------------------------------
// Name:    determinant
// Purpose: Returns the determinant of the matrix.
//------------------------------------------------------------------------------
double math::Matrix::determinant(void) const
{
  return e11 * (e22 * e33 - e23 * e32) +
         e12 * (e31 * e23 - e33 * e21) +
         e13 * (e21 * e32 - e31 * e23);
}


//------------------------------------------------------------------------------
// Name:    inverse
// Purpose: Returns the inverse of this matrix, if it exists. Otherwise, it 
//          crashes the program.
// TODO:    Make this more robust against division by near-zero.
//------------------------------------------------------------------------------
math::Matrix math::Matrix::inverse(void) const
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


//------------------------------------------------------------------------------
// Name:    invert
// Purpose: Sets this matrix to its own inverse, if it exists. If not, it 
//          crashes the program. This is done at the inverser() level.
// TODO:    Make this more robust against division by near-zero.
//------------------------------------------------------------------------------
void math::Matrix::invert(void)
{
  *this = this->inverse();
}


//------------------------------------------------------------------------------
// Name:    identity
// Purpose: Creates and returns an identity matrix.
//------------------------------------------------------------------------------
math::Matrix math::Matrix::identity(void)
{
  return Matrix(1, 0, 0,
                0, 1, 0,
                0, 0, 1);
}


//------------------------------------------------------------------------------
// Name:    operator*
// Purpose: Overload for binary product operator. This premultiplies a matrix by
//          a scalar.
//------------------------------------------------------------------------------
math::Matrix operator*(double              s_, 
                       const math::Matrix& m_)
{
  return m_ * s_;
}


//------------------------------------------------------------------------------
// Name:    zeroize
// Purpose: Sets this matrix to a zero matrix.
//------------------------------------------------------------------------------
void math::Matrix::zeroize(void)
{
  this->set(0, 0, 0, 
            0, 0, 0, 
            0, 0, 0);
}