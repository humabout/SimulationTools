// mat.h


#ifndef NEMESIS_MAT_H
#define NEMESIS_MAT_H


// Inclusions
#include <algorithm>
#include <memory>
#include <stdexcept>
#include "math_config.h"
#include "typedefs.h"
#include "vec.h"


//------------------------------------------------------------------------------
// Name:    nemesis
// Purpose: This namespace holds all aspects of the Nemesis Simulation Toolkit.
//------------------------------------------------------------------------------
namespace nemesis
{


  //----------------------------------------------------------------------------
  // Name:    Mat
  // Purpose: This class template represents an MxN-matrix. It stores the 
  //          matrix's elements. It also defines common operations on matrices.
  //          Finally, it provides specific implementations for square, 2x2- and
  //          3x3-matrices, with hard-coded solutions to accelerate their use.
  // Inputs:  Type
  //          Number of Rows
  //          Number of Columns
  //----------------------------------------------------------------------------
  template<class T, dim_size Rows, dim_size Cols>
  class Mat
  {
  public:
    // Typedefs
    typedef Mat<T, Rows, Cols>                    mat;
    typedef Vec<T, Cols>                          row_vec;
    typedef Vec<T, Rows>                          col_vec;
    typedef std::shared_ptr< Mat<T, Rows, Cols> > pointer;

    // Constructors
    Mat()
    {
      this->zeroize();
    }
    Mat(const T(& m)[Cols * Rows])
    {
      this->set(m);
    }
    Mat(const row_vec(& m)[Rows])
    {
      this->set(m);
    }
    Mat(const mat& m)
    {
      this->set(m);
    }

    // Destructor
    ~Mat()
    {
      // Does Nothing.
    }


    // Setters
    void set(const T(& m)[Cols * Rows])
    {
      // This assumed that the elements of each row are contiguous, and that the
      // first row appears first in the array each successive row appears in 
      // ascending order, with the last row at the end of the array.
      // For example:
      // [ 1, 2, 3,
      //   4, 5, 6,  = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }
      //   7, 8, 9]
      for (element row = 0; row < Rows; row++)
      {
        for (element col = 0; col < Cols; col++)
        {
          this->E[row][col] = m[(row * Cols) + col];
        }
      }
    }
    void set(const row_vec(& m)[Rows])
    {
      for (element row = 0; row < Rows; row++)
      {
        this->E[row] = m[row];
      }
    }
    void set(const mat& m)
    {
      for (element row = 0; row < Rows; row++)
      {
        for (element col = 0; col < Cols; col++)
        {
          this->E[row][col] = m.E[row][col];
        }
      }
    }


    // Accessors
    T& e(element row, element col)
    {
      return this->E[row][col];
    }
    row_vec& operator[](element r)
    {
      return this->E[r];
    }
    const row_vec& operator[](const element& r) const
    {
      return this->E[r];
    }
    row_vec row(element r)
    {
      return this->E[r];
    }
    col_vec column(element c)
    {
      col_vec output;
      for (element row = 0; row < Rows; row++)
      {
        output[row] = this->E[row][c];
      }
      return output;
    }

    // Return various measures of size
    dim_size length(void) const
    {
      // Returns the largest dimension of the matrix
      return std::max(Rows, Cols);
    }
    dim_size size(void) const
    {
      // Returns the total number of elements in the matrix
      return Rows * Cols;
    }
    dimension dim(void) const
    {
      // Returns the number of rows and columsn in a dimension object
      // NOTE:  This is not the true dimensionality of the matrix in the 
      //        mathematical sense.
      return dimension(Rows, Cols);
    }


    // Assignment Operator
    void operator=(const T(& m)[Cols * Rows])
    {
      this->set(m);
    }
    void operator=(const row_vec(& m)[Rows])
    {
      this->set(m);
    }
    void operator=(const mat& m)
    {
      this->set(m);
    }


    // Comparison Operators
    template<dim_size M, dim_size N>
    bool operator==(const Mat<T, M, N>& m) const
    {
      // Check if sizes are the same
      if (this->dim() != m.dim())
      {
        return false;
      }

      // Check if the elements are the same
      for (element row = 0; row < Rows; row++)
      {
        for (element col = 0; col < Cols; col++)
        {
          if (this->E[row][col] != m[row][col])
          {
            return false;
          }
          else
          {
            // Continue Checking
          }
        }
      }
      return true;
    }
    template<dim_size M, dim_size N>
    bool operator!=(const Mat<T, M, N>& m) const
    {
      return !(*this == m);
    }


    // Unary Negative
    mat operator-() const
    {
      mat output;
      for (element row = 0; row < Rows; row++)
      {
        for (element col = 0; col < Cols; col++)
        {
          output.E[row][col] = -(this->E[row][col]);
        }
      }
      return output;
    }


    // Addition Operators
    mat operator+(const mat& m) const
    {
      mat output;
      for (element row = 0; row < Rows; row++)
      {
        for (element col = 0; col < Cols; col++)
        {
          output.E[row][col] = this->E[row][col] + m.E[row][col];
        }
      }
      return output;
    }
    void operator+=(const mat& m)
    {
      *this = *this + m;
    }


    // Subtraction Operators
    mat operator-(const mat& m) const
    {
      return *this + (-m);
    }
    void operator-=(const mat& m)
    {
      *this = *this - m;
    }


    // Scalar Multiplication Operators
    mat operator*(const T& s) const
    {
      mat output;
      for (element row = 0; row < Rows; row++)
      {
        for (element col = 0; col < Cols; col++)
        {
          output.E[row][col] = s * this->E[row][col];
        }
      }
      return output;
    }
    void operator*=(const T& s)
    {
      *this = *this * s;
    }


    // Scalar Division Operators
    mat operator/ (const T& s) const
    {
      T den = s;
      if (abs(s) < math::DIVIDE_BY_ZERO_TOLERANCE)
      {
        den = 1 / math::DIVIDE_BY_ZERO_TOLERANCE;
        throw std::runtime_error("Warning: Division by near-zero. Dividing by tolerance, instead.");
      }
      else
      {
        den = 1 / s;
      }
      return *this * den;
    }
    void operator/=(const T& s)
    {
      *this = *this / s;
    }


    // Vector Multiplication Operator
    col_vec operator*(const row_vec& v) const
    {
      col_vec output;
      for (element row = 0; row < Rows; row++)
      {
        for (element col = 0; col < Cols; col++)
        {
          output[row] += this->E[row][col] * v[col];
        }
      }
      return output;
    }


    // Matix Mulitplication Operators
    template<dim_size P>
    Mat<T, Rows, P> operator*(const Mat<T, Cols, P>& m) const
    {
      dim_size M = Rows;
      dim_size N = Cols;  
      Mat<T, Rows, P> output;
      for (element i = 0; i < M; i++)
      {
        for (element j = 0; j < P; j++)
        {
          for (element k = 0; k < N; k++)
          {
            output[i][j] += this->E[i][k] * m[k][j];
          }
        }
      }
      return output;
    }


    // Transposes
    // TODO:  Find a better syntax for this mess. Transpose is the verb and the
    //        noun. This makes it difficult.
    Mat<T, Cols, Rows> trans(void) const
    {
      Mat<T, Cols, Rows> output;
      for (element row = 0; row < Rows; row++)
      {
        for (element col = 0; col < Cols; col++)
        {
          output.E[row][col] = this->E[col][row];
        }
      }
      return output;
    }
    void transpose(void)
    {
      *this = this->trans();
    }


    // Zeroize
    void zeroize(void)
    {
      for (element row = 0; row < Rows; row++)
      {
        for (element col = 0; col < Cols; col++)
        {
          this->E[row][col] = 0;
        }
      }
    }

  private:
    // Elements
    row_vec E[Rows];


  }; // ! Mat<T, M, N>

  /*
  //----------------------------------------------------------------------------
  // Specialized for Rows = Cols
  //----------------------------------------------------------------------------
  template <class T, dim_size N>
  class Mat<T, N, N>
  {
  public:
    // Constructors
    // Destructor
    // Setters
    // Accessors
    // Return various measures of size
    // Comparison Operators
    // Unary Negative
    // Addition Operators
    // Subtraction Operators
    // Scalar Multiplication Operators
    // Scalar Division Operators
    // Vector Multiplication Operators
    // Matrix Multiplication Operators
    // Transposes
    // Trace
    // LU Decomposition
    // Determinate
    // Inverses (Using LUP Decomposition)
    //  TODO:  Add check for Choleski Decomposition
    // Identity (return one; set to one)
    // Zeroize


  private:
    // Elements
    row_vec E[N];
  };*/


    // Constructors
    // Destructor
    // Setters
    // Accessors
    // Return various measures of size
    // Comparison Operators
    // Unary Negative
    // Addition Operators
    // Subtraction Operators
    // Scalar Multiplication Operators
    // Scalar Division Operators
    // Vector Multiplication Operators
    // Matrix Multiplication Operators
    // Transposes
    // Trace
    // LU Decomposition
    // Determinate
    // Inverses (Using LUP Decomposition)
    //  TODO:  Add check for Choleski Decomposition
    // Identity (return one; set to one)
    // Zeroize


  //----------------------------------------------------------------------------
  // Specialized for Rows = Cols = 4
  //----------------------------------------------------------------------------

  //----------------------------------------------------------------------------
  // Specialized for Rows = Cols = 3
  //----------------------------------------------------------------------------

  //----------------------------------------------------------------------------
  // Specialized for Rows = Cols = 2
  //----------------------------------------------------------------------------

} // !nemesis


//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
// Operator Overrides
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>


// operator* overload for type T * Vec
template <class T, nemesis::dim_size Rows, nemesis::dim_size Cols>
nemesis::Mat<T, Rows, Cols> operator* (T s, nemesis::Mat<T, Rows, Cols> m)
{
  return m * s;
}


#endif // !NEMESIS_MAT_H
