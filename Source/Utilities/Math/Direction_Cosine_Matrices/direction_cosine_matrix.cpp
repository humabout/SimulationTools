// direction_cosine_matrix.cpp


// Inclusions
#include "direction_cosine_matrix.h"
#include "../matrix.h"


//------------------------------------------------------------------------------
// Name:    DirectionCosineMatrix
// Purpose: Default Constructor
//------------------------------------------------------------------------------
math::dcm::DirectionCosineMatrix::DirectionCosineMatrix()
{
  zeroize();
}


//------------------------------------------------------------------------------
// Name:    DirectionCosineMatrix
// Purpose: Copy Constructor
//------------------------------------------------------------------------------
math::dcm::DirectionCosineMatrix::DirectionCosineMatrix(const DirectionCosineMatrix& dcm_)
{
  set(dcm_);
}


//------------------------------------------------------------------------------
// Name:    DirectionCosineMatrix
// Purpose: Constructor Overload. Builds a DCM from a 3x3 Matrix.
//------------------------------------------------------------------------------
math::dcm::DirectionCosineMatrix::DirectionCosineMatrix(const Matrix& m_)
{
  set(m_);
}


//------------------------------------------------------------------------------
// Name:    DirectionCosineMatrix
// Purpose: Constructor Overload. Builds a DCM from individual elements.
//------------------------------------------------------------------------------
math::dcm::DirectionCosineMatrix::DirectionCosineMatrix(double e11_, double e12_, double e13_,
                                                        double e21_, double e22_, double e23_,
                                                        double e31_, double e32_, double e33_)
{
  set(e11_, e12_, e13_,
      e21_, e22_, e23_,
      e31_, e32_, e33_);
}


//------------------------------------------------------------------------------
// Name:    ~DirectionCosineMatrix
// Purpose: Destructor. This has nothing to delete, so it does nothing.
//------------------------------------------------------------------------------
math::dcm::DirectionCosineMatrix::~DirectionCosineMatrix()
{
  // Does Nothing
}


//------------------------------------------------------------------------------
// Name:    set
// Purpose: Sets this DCM to another DCM.
//------------------------------------------------------------------------------
void math::dcm::DirectionCosineMatrix::set(const DirectionCosineMatrix& dcm_)
{
  this->e11 = dcm_.e11;
  this->e12 = dcm_.e12;
  this->e13 = dcm_.e13;
  this->e21 = dcm_.e21;
  this->e22 = dcm_.e22;
  this->e23 = dcm_.e23;
  this->e31 = dcm_.e31;
  this->e32 = dcm_.e32;
  this->e33 = dcm_.e33;
}


//------------------------------------------------------------------------------
// Name:    set
// Purpose: Sets this DCM to a 3x3 matrix.
//------------------------------------------------------------------------------
void math::dcm::DirectionCosineMatrix::set(const Matrix& m_)
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
// Purpose: Sets the DCM's elements to those provided.
//------------------------------------------------------------------------------
void math::dcm::DirectionCosineMatrix::set(double e11_, double e12_, double e13_,
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