// direction_cosine_matrix.h


#ifndef DIRECTION_COSINE_MATRIX_H
#define DIRECTION_COSINE_MATRIX_H


// Inclusions
#include "../matrix.h"


// Forward Declarations
namespace math
{
  class Quaternion;
}


//------------------------------------------------------------------------------
// Name:    math
// Purpose: This namespace holds all math objects, functions, and constants.
//------------------------------------------------------------------------------
namespace math
{


  //----------------------------------------------------------------------------
  // Name:    dcm
  // Purpose: This namespace holds all DCMs and functions that operate on them.
  //----------------------------------------------------------------------------
  namespace dcm
  {
    //--------------------------------------------------------------------------
    // Name:    DirectionCosineMatrix
    // Purpose: This class serves as a common parent for all DCM classes. This
    //          provides an accelerated inversion process and the means to
    //          generate DCMs from quaternions and vice versa. It also serves as
    //          a branching point for specific DCMs, each of which will need its
    //          own construction and angle-reporting procedures.
    //--------------------------------------------------------------------------
    class DirectionCosineMatrix : public Matrix
    {
    public:
      // Constructors
      DirectionCosineMatrix();
      DirectionCosineMatrix(const DirectionCosineMatrix& dcm_);
      DirectionCosineMatrix(const Matrix& m_);
      //DirectionCosineMatrix(const Quaternion& q_);
      DirectionCosineMatrix(double e11_, double e12_, double e13_,
                            double e21_, double e22_, double e23_,
                            double e31_, double e32_, double e33_);


      // Destructor
      virtual ~DirectionCosineMatrix();


      // Setters
      void set(const DirectionCosineMatrix& dcm_);
      void set(const Matrix& m_);
//      void set(const Quaternion& dcm_);
      void set(double e11_, double e12_, double e13_,
               double e21_, double e22_, double e23_,
               double e31_, double e32_, double e33_);


      // Inversion
      void invert(void) override
      {
        // TODO: Put this in the source file
        DirectionCosineMatrix inverse(this->transpose());
        *this = inverse;
      }


    }; // !DirectionCosineMatrix


  } // !dcm


} // !math


// Forward Declaration Inclusions
// TODO: Add this once Quaternion is done


#endif // !DIRECTION_COSINE_MATRIX_H
