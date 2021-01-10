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
      Mat<T, Rows, P> output;
      for (element i = 0; i < Rows; i++)
      {
        for (element j = 0; j < P; j++)
        {
          for (element k = 0; k < Cols; k++)
          {
            output[i][j] += this->E[i][k] * m[k][j];
          }
        }
      }
      return output;
    }


    // Transposes
    Mat<T, Cols, Rows> transpose(void) const
    {
      Mat<T, Cols, Rows> output;
      for (element row = 0; row < Rows; row++)
      {
        for (element col = 0; col < Cols; col++)
        {
          output[col][row] = this->E[row][col];
        }
      }
      return output;
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

  
  //----------------------------------------------------------------------------
  // Name:    LUP
  // Purpose: This is a helper class for executing LUP decompositions on square
  //          matrices. These are used a lot for inverting square matrices or 
  //          calculating determinates.
  //----------------------------------------------------------------------------
  template<class T, dim_size N>
  class LUP
  {
  public:
    // Constructor & Destructor
    LUP() { N = 0; }
    LUP(const Mat<T, N, N>& A) { this->decompose(A); }
    ~LUP() { /* Does Nothing */ }

    // Accessors
    Mat<T, N, N> lower(void) const
    {
      Mat<T, N, N> low;
      for (element row = 0; row < N; row++)
      {
        for (element col = 0; col < N; col++)
        {
          if (row <= col)
          {
            low[row][col] = LU[row][col];
          }
          else
          {
            // Leave the zero in place
          }
        }
      }
      return low;
    }
    Mat<T, N, N> upper(void) const { return LU - this->lower(); }
    Mat<T, N, N> lower_upper(void) const { return LU; }
    Vec<T, N>    permutation(void) const { return P; }
    unsigned int swap_count(void) const { return N; }

    // Functionality
    void deompose(const Mat<T, N, N>& A)
    {
      // Algorithm from https://en.wikipedia.org/wiki/LU_decomposition#C_code_example

      // Initializing the matrix that will hold the sum of the L-E matrix and 
      // the U matrix. The algorithm will build the answer here.
      LU = A;

      // Initializing the permutation matrix vector
      for (element i = 0; i < N; i++)
      {
        P[i] = i;
      }

      // Initializing the number of row swaps to zero
      N = 0;

      // Executing the LUP Decomposition
      for (element i = 0; i < N; i++)
      {
        // Finding the pivot position
        T       A_abs = 0;
        T       A_max = 0;
        element i_max = i;
        for (element k = i; k < N; k++)
        {
          A_abs = abs(LU[k][i]);
          if (A_abs > A_max)
          {
            A_max = A_abs;
            i_max = k;
          }
        }

        // Checking for degeneracy
        if (A_max < math::DIVIDE_BY_ZERO_TOLERANCE)
        {
          throw std::runtime_error("Fatal Error: Matrix is degenerate and cannot be decomposed.");
        }

        // Pivoting
        if (i != i_max)
        {
          // Pivoting
          std::swap(P [i], P [i_max]);
          std::swap(LU[i], LU[i_max]);

          // Counting pivots
          N++;
        }

        // Building the matrix
        for (element j = i + 1; j < N; j++)
        {
          A[j][i] /= A[i][i];

          for (element k = i + 1; k < N; k++)
          {
            A[j][k] -= A[j][i] * A[i][k];
          }
        }
      }
    }

  private:
    // Stores L-E plus U in a single matrix
    Mat<T, N, N> LU;

    // Stores the column indices where the permutation matrix has a one
    Vec<element, N> P;

    // Number of row swaps
    unsigned int N;
  };


  //----------------------------------------------------------------------------
  // Specialized for Square Matrces (Rows = Cols)
  //----------------------------------------------------------------------------
  template <class T, dim_size N>
  class Mat<T, N, N>
  {
  public:
    // Typedefs
    typedef Mat<T, N, N>                    mat;
    typedef Vec<T, N>                       row_vec;
    typedef Vec<T, N>                       col_vec;
    typedef std::shared_ptr< Mat<T, N, N> > pointer;


    // Constructors
    Mat()
    {
      this->zeroize();
    }
    Mat(const T(& m)[N * N])
    {
      this->set(m);
    }
    Mat(const row_vec(& m)[N])
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
      // Does Nothing
    }


    // Setters
    void set(const T(& m)[N * N])
    {
      // This assumed that the elements of each row are contiguous, and that the
      // first row appears first in the array each successive row appears in 
      // ascending order, with the last row at the end of the array.
      // For example:
      // [ 1, 2, 3,
      //   4, 5, 6,  = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }
      //   7, 8, 9]
      for (element row = 0; row < N; row++)
      {
        for (element col = 0; col < N; col++)
        {
          this->E[row][col] = m[(row * N) + col];
        }
      }
    }
    void set(const row_vec(& m)[N])
    {
      for (element row = 0; row < N; row++)
      {
        this->E[row] = m[row];
      }
    }
    void set(const mat& m)
    {
      for (element row = 0; row < N; row++)
      {
        for (element col = 0; col < N; col++)
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
      for (element row = 0; row < N; row++)
      {
        output[row] = this->E[row][c];
      }
      return output;
    }

    // Return various measures of size
    dim_size length(void) const
    {
      // Returns the largest dimension of the matrix
      return N;
    }
    dim_size size(void) const
    {
      // Returns the total number of elements in the matrix
      return N * N;
    }
    dimension dim(void) const
    {
      // Returns the number of rows and columsn in a dimension object
      // NOTE:  This is not the true dimensionality of the matrix in the 
      //        mathematical sense.
      return dimension(N, N);
    }


    // Comparison Operators
    template<dim_size P, dim_size Q>
    bool operator==(const Mat<T, P, Q>& m) const
    {
      // Check if sizes are the same
      if (this->dim() != m.dim())
      {
        return false;
      }

      // Check if the elements are the same

      // Providing specialized methods for N=2 and N=3 because those are common
      // sizes that can be made to run faster. All other sizes use a default
      // algorithm.
      switch (N)
      {
      case 2:
        // 2x2 Matrix
        return (this->E[0] == m[0]) &&
               (this->E[1] == m[1]);
      case 3:
        // 3x3 Matrix
        return (this->E[0] == m[0]) &&
               (this->E[1] == m[1]) &&
               (this->E[2] == m[2]);
      default:
        // All other square matrices
        for (element row = 0; row < N; row++)
        {
          for (element col = 0; col < N; col++)
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
    }
    template<dim_size P, dim_size Q>
    bool operator!=(const Mat<T, P, Q>& m) const
    {
      return !(*this == m);
    }


    // Unary Negative
    mat operator-() const
    {
      mat output;

      // Providing specialized methods for N=2 and N=3 because those are common
      // sizes that can be made to run faster. All other sizes use a default
      // algorithm.
      switch (N)
      {
      case 2:
        // 2x2 Matrix
        output.E[0][0] = -(this->E[0][0]);
        output.E[0][1] = -(this->E[0][1]);
        output.E[1][0] = -(this->E[1][0]);
        output.E[1][1] = -(this->E[1][1]);
        break;
      case 3:
        // 3x3 Matrix
        output.E[0][0] = -(this->E[0][0]);
        output.E[0][1] = -(this->E[0][1]);
        output.E[0][2] = -(this->E[0][2]);
        output.E[1][0] = -(this->E[1][0]);
        output.E[1][1] = -(this->E[1][1]);
        output.E[1][2] = -(this->E[1][2]);
        output.E[2][0] = -(this->E[2][0]);
        output.E[2][1] = -(this->E[2][1]);
        output.E[2][2] = -(this->E[2][2]);
        break;
      default:
        // All Other Square Matrices
        for (element row = 0; row < N; row++)
        {
          for (element col = 0; col < N; col++)
          {
            output.E[row][col] = -(this->E[row][col]);
          }
        }
      }
      return output;
    }


    // Addition Operators
    mat operator+(const mat& m) const
    {
      mat output;

      // Providing specialized methods for N=2 and N=3 because those are common
      // sizes that can be made to run faster. All other sizes use a default
      // algorithm.
      switch (N)
      {
      case 2:
        // 2x2 Matrix
        output[0][0] = this->E[0][0] + m[0][0];
        output[0][1] = this->E[0][1] + m[0][1];
        output[1][0] = this->E[1][0] + m[1][0];
        output[1][1] = this->E[1][1] + m[1][1];
        break;
      case 3:
        // 3x3 Matrix
        output[0][0] = this->E[0][0] + m[0][0];
        output[0][1] = this->E[0][1] + m[0][1];
        output[0][2] = this->E[0][2] + m[0][2];
        output[1][0] = this->E[1][0] + m[1][0];
        output[1][1] = this->E[1][1] + m[1][1];
        output[1][2] = this->E[1][2] + m[1][2];
        output[2][0] = this->E[2][0] + m[2][0];
        output[2][1] = this->E[2][1] + m[2][1];
        output[2][2] = this->E[2][2] + m[2][2];
        break;
      default:
        // All Other Square Matrices
        for (element row = 0; row < N; row++)
        {
          for (element col = 0; col < N; col++)
          {
            output[row][col] = this->E[row][col] + m[row][col];
          }
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

      // Providing specialized methods for N=2 and N=3 because those are common
      // sizes that can be made to run faster. All other sizes use a default
      // algorithm.
      switch (N)
      {
      case 2:
        // 2x2 Matrix
        output.E[0][0] = s * this->E[0][0];
        output.E[0][1] = s * this->E[0][1];
        output.E[1][0] = s * this->E[1][0];
        output.E[1][1] = s * this->E[1][1];
        break;
      case 3:
        // 3x3 Matrix
        output.E[0][0] = s * this->E[0][0];
        output.E[0][1] = s * this->E[0][1];
        output.E[0][2] = s * this->E[0][2];
        output.E[1][0] = s * this->E[1][0];
        output.E[1][1] = s * this->E[1][1];
        output.E[1][2] = s * this->E[1][2];
        output.E[2][0] = s * this->E[2][0];
        output.E[2][1] = s * this->E[2][1];
        output.E[2][2] = s * this->E[2][2];
        break;
      default:
        // All Other Square Matrices
        for (element row = 0; row < N; row++)
        {
          for (element col = 0; col < N; col++)
          {
            output.E[row][col] = s * this->E[row][col];
          }
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

      // Providing specialized methods for N=2 and N=3 because those are common
      // sizes that can be made to run faster. All other sizes use a default
      // algorithm.
      switch (N)
      {
      case 2:
        // 2x2 Matrix
        output[0] += this->E[0][0] * v[0];
        output[0] += this->E[0][1] * v[1];
        output[1] += this->E[1][0] * v[0];
        output[1] += this->E[1][1] * v[1];
        break;
      case 3:
        // 3x3 Matrix
        output[0] += this->E[0][0] * v[0];
        output[0] += this->E[0][1] * v[1];
        output[0] += this->E[0][2] * v[2];
        output[1] += this->E[1][0] * v[0];
        output[1] += this->E[1][1] * v[1];
        output[1] += this->E[1][2] * v[2];
        output[2] += this->E[2][0] * v[0];
        output[2] += this->E[2][1] * v[1];
        output[2] += this->E[2][2] * v[2];
        break;
      default:
        // All Other Square Matrices
        for (element row = 0; row < N; row++)
        {
          for (element col = 0; col < N; col++)
          {
            output[row] += this->E[row][col] * v[col];
          }
        }
      }
      return output;
    }


    // Matix Mulitplication Operators
    template<dim_size P>
    Mat<T, N, P> operator*(const Mat<T, N, P>& m) const
    {
      Mat<T, N, P> output;

      // Providing specialized methods for N=2 and N=3 because those are common
      // sizes that can be made to run faster. All other sizes use a default
      // algorithm.
      if (N == P)
      {
        // If both matrices are square, choose an algorithm based on their size.
        // If their size is greater than 3x3, use the default algorithm.
        switch (N)
        {
        case 2:
          // 2x2 Matrix
          output[0][0] = this->E[0][0] * m[0][0] + this->E[0][1] * m[1][0];
          output[0][1] = this->E[0][0] * m[0][1] + this->E[0][1] * m[1][1];
          output[1][0] = this->E[1][0] * m[0][0] + this->E[1][1] * m[1][0];
          output[0][1] = this->E[1][0] * m[0][1] + this->E[1][1] * m[1][1];
          return output;
        case 3:
          // 3x3 Matrix
          output[0][0] = this->E[0][0] * m[0][0] + this->E[0][1] * m[1][0] + this->E[0][2] * m[2][0];
          output[0][1] = this->E[0][0] * m[0][1] + this->E[0][1] * m[1][1] + this->E[0][2] * m[2][1];
          output[0][2] = this->E[0][0] * m[0][2] + this->E[0][1] * m[1][2] + this->E[0][2] * m[2][2];
          output[1][0] = this->E[1][0] * m[0][0] + this->E[1][1] * m[1][0] + this->E[1][2] * m[2][0];
          output[1][1] = this->E[1][0] * m[0][1] + this->E[1][1] * m[1][1] + this->E[1][2] * m[2][1];
          output[1][2] = this->E[1][0] * m[0][2] + this->E[1][1] * m[1][2] + this->E[1][2] * m[2][2];
          output[2][0] = this->E[2][0] * m[0][0] + this->E[2][1] * m[1][0] + this->E[2][2] * m[2][0];
          output[2][1] = this->E[2][0] * m[0][1] + this->E[2][1] * m[1][1] + this->E[2][2] * m[2][1];
          output[2][2] = this->E[2][0] * m[0][2] + this->E[2][1] * m[1][2] + this->E[2][2] * m[2][2];
          return output;
        default:
          // All other matrices pass through to the generic calculation below
        }
      }

      // Generic Algorithm
      for (element i = 0; i < N; i++)
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
    mat transpose(void) const
    {
      mat output;

      // Providing specialized methods for N=2 and N=3 because those are common
      // sizes that can be made to run faster. All other sizes use a default
      // algorithm.
      switch (N)
      {
      case 2:
        // 2x2 Matrix
        output[1][0] = this->E[0][1];
        output[0][1] = this->E[1][0];
        break;
      case 3:
        // 3x3 Matrix
        output[1][0] = this->E[0][1];
        output[0][1] = this->E[1][0];
        output[2][0] = this->E[0][2];
        output[0][2] = this->E[2][0];
        output[1][2] = this->E[2][1];
        output[2][1] = this->E[1][2];
        break;
      default:
        // All Other Square Matrices
        for (element row = 0; row < N; row++)
        {
          for (element col = 0; col < N; col++)
          {
            output[col][row] = this->E[row][col];
          }
        }
      }
      return output;
    }


    // Trace
    T trace(void) const
    {
      // Providing specialized methods for N=2 and N=3 because those are common
      // sizes that can be made to run faster. All other sizes use a default
      // algorithm.
      switch (N)
      {
      case 2:
        // 2x2 Matrix
        return this->E[0][0] + this->E[1][1];
      case 3:
        // 3x3 Matrix
        return this->E[0][0] + this->E[1][1] + this->E[2][2];
      default:
        // All Other Square Matrices
        T tr = 0;
        for (element i = 0; i < N; i++)
        {
          tr += this->E[i][i];
        }
        return tr;
      }
    }


    // Symmetry Check
    bool is_symmetric(void) const
    {
      // Providing specialized methods for N=2 and N=3 because those are common
      // sizes that can be made to run faster. All other sizes use a default
      // algorithm.
      switch (N)
      {
      case 2:
        // 2x2 Matrix
        return (this->E[0][1] == this->E[1][0]);
      case 3:
        // 3x3 Matrix
        return (this->E[0][1] == this->E[1][0]) &&
               (this->E[0][2] == this->E[2][0]) &&
               (this->E[2][1] == this->E[1][2]);
      default:
        // All Other Square Matrices
        for (element i = 0; i < N; i++)
        {
          for (element j = 0; j < N; j++)
          {
            if (this->E[i][j] != this->E[j][i])
            {
              return false;
            }
          }
        }
        return true;
      }
    }


    // Determinate
    T determinant(void) const
    {
      // Providing specialized methods for N=2 and N=3 because those are common
      // sizes that can be made to run faster. All other sizes use a default
      // algorithm.
      switch (N)
      {
      case 2:
        // 2x2 Matrix
        return (this->E[0][0] * this->[1][1]) - (this->E[0][1] * this->E[1][0]);
      case 3:
        // 3x3 Matrix
        return (this->E[0][0] * (this->E[1][1] * this->E[2][2] - this->E[1][2] * this->E[2][1]))
             - (this->E[0][1] * (this->E[1][0] * this->E[2][2] - this->E[0][2] * this->E[2][0]))
             + (this->E[0][2] * (this->E[1][0] * this->E[2][1] - this->E[0][2] * this->E[1][1]));
      default:
        // All Other Square Matrices
        // LUP Decompostion
        LUP<T, N> lup(*this);
        mat A = lup.LU();

        // Calculating the determinant
        T det = A[0][0];
        for (element i = 1; i < N; i++)
        {
          det *= A[i][i];
        }

        // Setting the sign of the determinant
        if ((lup.N() - N) % 2 != 0)
        {
          det = -det;
        }

        return det;
      }
    }

    // Inverses (Using LUP Decomposition)
    mat inverse(void) const
    {
      // Providing specialized methods for N=2 and N=3 because those are common
      // sizes that can be made to run faster. All other sizes use a default
      // algorithm.
      switch (N)
      {
      case 2:
        // 2x2 Matrix
        T det = this->determinant();
        if (abs(det) < math::DIVIDE_BY_ZERO_TOLERANCE)
        {
          throw std::runtime_error("Warning: Matrix is near degenerate")
        }
        else
        {
          return mat([ this->E[1][1], -this->E[0][1], 
                      -this->E[1][0],  this->E[0][0]]) / this->determinant();
        }
      case 3:
        // 3x3 Matrix
        T det = this->determinant();
        if (abs(det) < math::DIVIDE_BY_ZERO_TOLERANCE)
        {
          throw std::runtime_error("Warning: Matrix is near degenerate")
        }
        else
        {
          mat inv;
          T det_inv = 1 / det;

          inv->E[0][0] = ( this->E[1][1] * this->E[2][2] - this->E[2][1] * this->E[1][2] ) * det_inv;
          inv->E[0][1] = ( this->E[0][2] * this->E[2][1] - this->E[0][1] * this->E[2][2] ) * det_inv;
          inv->E[0][2] = ( this->E[0][1] * this->E[1][2] - this->E[0][2] * this->E[1][1] ) * det_inv;
          inv->E[1][0] = ( this->E[1][2] * this->E[2][0] - this->E[1][0] * this->E[2][2] ) * det_inv;
          inv->E[1][1] = ( this->E[0][0] * this->E[2][2] - this->E[0][2] * this->E[2][0] ) * det_inv;
          inv->E[1][2] = ( this->E[1][0] * this->E[0][2] - this->E[0][0] * this->E[1][2] ) * det_inv;
          inv->E[2][0] = ( this->E[1][0] * this->E[2][1] - this->E[2][0] * this->E[1][1] ) * det_inv;
          inv->E[2][1] = ( this->E[2][0] * this->E[0][1] - this->E[0][0] * this->E[2][1] ) * det_inv;
          inv->E[2][2] = ( this->E[0][0] * this->E[1][1] - this->E[1][0] * this->E[0][1] ) * det_inv;

          return inv;
        }
      default:
        // All Other Square Matrices

        // LUP Decompostion
        LUP<T, N> lup(*this);
        mat A = lup.LU();
        col_vec P = lup.P();

        // Algorithm from https://en.wikipedia.org/wiki/LU_decomposition#C_code_example
        mat inv;
        for (element j = 0; j < N; j++)
        {
          for (element i = 0; i < N; i++)
          {
            if (P[i] == j) { inv[i][j] = 1; }
            else { inv[i][j] = 0; }

            for (element k = 0; k < i; k++)
            {
              inv[i][j] -= A[i][k] * inv[k][j];
            }
          }

          for (element i = N; i >= 0; i--)
          {
            for (element k = i + 1; k < N; k++)
            {
              inv[i][j] -= A[i][k] * inv[k][j];
            }
            inv[i][j] /= A[i][i];
          }
        }

        return inv;
      }
    }
    void invert(void)
    {
      *this = this->inverse();
    }


    // Identity
    void set_to_identity(void)
    {
      // Providing specialized methods for N=2 and N=3 because those are common
      // sizes that can be made to run faster. All other sizes use a default
      // algorithm.
      switch (N)
      {
      case 2:
        // 2x2 Matrix
        this->E[0][0] = 1;
        this->E[1][1] = 1;

        this->E[0][1] = 0;
        this->E[1][0] = 0;
        break;
      case 3:
        // 3x3 Matrix
        this->E[0][0] = 1;
        this->E[1][1] = 1;
        this->E[2][2] = 1;

        this->E[0][1] = 0;
        this->E[0][2] = 0;
        this->E[1][0] = 0;
        this->E[2][0] = 0;
        this->E[1][2] = 0;
        this->E[2][1] = 0;
        break;
      default:
        // All Other Square Matrices
        for (element row = 0; row < N; row++)
        {
          for (element col = 0; col < N; col++)
          {
            if (row == col)
            {
              this->E[row][col] = 1;
            }
            else
            {
              this->E[row][col] = 0;
            }
          }
        }
      }
    }
    
    static mat identity(void)
    {
      // Providing specialized methods for N=2 and N=3 because those are common
      // sizes that can be made to run faster. All other sizes use a default
      // algorithm.
      switch (N)
      {
      case 2:
        // 2x2 Matrix
        return mat({ 1, 0, 0, 1 });
      case 3:
        // 3x3 Matrix
        return mat({ 1, 0, 0, 0, 1, 0, 0, 0, 1 });
      default:
        mat output;
        for (element i = 0; i < N; i++)
        {
          output[i][i] = 1;
        }
        return output;
      }
    }


    // Zeroize
    void zeroize(void)
    {
      // Providing specialized methods for N=2 and N=3 because those are common
      // sizes that can be made to run faster. All other sizes use a default
      // algorithm.
      switch (N)
      {
      case 2:
        // 2x2 Matrix
        this->set({ 0, 0, 0, 0 });
        break;
      case 3:
        // 3x3 Matrix
        this->set({ 0, 0, 0, 0, 0, 0, 0, 0, 0 });
      default:
        // All Other Square Matrices
        for (element row = 0; row < N; row++)
        {
          for (element col = 0; col < N; col++)
          {
            this->E[row][col] = 0;
          }
        }
      }
    }


  private:
    // Elements
    row_vec E[N];


  };


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
    // Symmetry Check
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
