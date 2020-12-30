// mat.h


#ifndef NEMESIS_MAT_H
#define NEMESIS_MAT_H


// Inclusions
#include <memory>
#include <stdexcept>
#include <utility>
#include "math_config.h"
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
  template<class T, unsigned int Rows, unsigned int Cols>
  class Mat
  {
  public:
    // Typedefs
    typedef Mat<T, Rows, Cols>                    mat;
    typedef std::shared_ptr< Mat<T, Rows, Cols> > pointer;

    // Constructors
    // Destructor
    // Setters
    // Accessors
    // Access Operator
    // Assignment Operator
    // Comparison Operators
    // Unary Negative
    // Addition Operators
    // Subtraction Operators
    // Scalar Multiplication Operators
    // Scalar Division Operators
    // Vector Multiplication Operator
    // Mextix Mulitplication Operators
    // Transposes (return a transpose and transpose this matrix)
    // Trace
    // Determinate (via LUP decomposition)
    // Inverses (return the inverse and invert this matrix) (via LUP decomposition)
    // Zeroize
    void zeroize(void)
    {
      for (std::size_t row = 0; row < Rows; row++)
      {

      }
    }

  private:
    // Elements
    Vec<T, Cols> E[Rows];


  }; // ! Mat<T, M, N>


} // !nemesis


#endif // !NEMESIS_MAT_H
