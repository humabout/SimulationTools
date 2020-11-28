// vector.h


#ifndef VECTOR_H
#define VECTOR_H


// Inclusions
#include "math_config.h"


// Forward Declarations
namespace
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
  // Name:    Vector
  // Purpose: This class holds a vector in R3 and all of the operators and 
  //          methods that operate on 3-vectors.
  //----------------------------------------------------------------------------
  class Vector
  {
  public:
    // Data
    union
    {
      double e[3];
      struct
      {
        double x;
        double y;
        double z;
      };
      struct
      {
        double e1;
        double e2;
        double e3;
      };
    };
    

    // Constructors
    Vector();
    Vector(double x_,
           double y_,
           double z_);
    Vector(const Vector& v_);


    // Destructor
    ~Vector();


    // Accessors
    double& operator[](unsigned int element_);


    // Assignment Operator
    void operator=(const Vector& v_);


    // Setters
    void set(double x_,
             double y_,
             double z_);
    void set(const Vector& v_);


    // Comparison Operators
    bool operator==(const Vector& v_) const;
    bool operator!=(const Vector& v_) const;


    // Unary -
    Vector operator-() const;


    // Addition & Subtraction
    Vector operator+(const Vector& v_) const;
    void operator+=(const Vector& v_);
    Vector operator-(const Vector& v_) const;
    void operator-=(const Vector& v_);


    // Scalar Multiplication & Division
    Vector operator*(double s_) const;
    void operator*=(double s_);
    Vector operator/(const double& s_) const;
    void operator/=(const double& s_);


    // Dot Product
    double dot(const Vector& v_) const;
    double operator*(const Vector& v_) const;


    // Cross Product
    Vector cross(const Vector& v_) const;
    Vector operator%(const Vector& v_) const;
    void operator%=(const Vector& v_);


    // Magnitude
    double magnitude(void) const;


    // Normalize
    void normalize(void);
    Vector unit(void) const;

    
    // Zeroize
    void zeroize(void);
    
    
    // Rotation Operators
    Quaternion rotatedBy(const Quaternion& q_)
    {
      return Quaternion(*this).rotatedBy(q_);
    }


  }; // !Vector


} // !math


// Operator* Overload for scalar * vector
math::Vector operator*(double              s_,
                       const math::Vector& v_);


// Forward Declaration Inclusions
#include "quaternion.h"


#endif // !VECTOR_H
