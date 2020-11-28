// quaternion.h


#ifndef QUATERNION_H
#define QUATERNION_H


// Inclusions
#include <array>
#include <cassert>
#include <vector>
#include "math_config.h"
#include "matrix.h"
#include "vector.h"


// Forward Declarations


//------------------------------------------------------------------------------
// Name:    math
// Purpose: This namespace holds all math objects, functions, and constants.
//------------------------------------------------------------------------------
namespace math
{


  //----------------------------------------------------------------------------
  // Name:    Quaternion
  // Purpose: This class holds a Quaternion and all of the operators and methods
  //          that operate on Quaternions. The data in the quaternion is exposed
  //          because this container's elements are expected to be accessed 
  //          often, and this provides that in a syntax that is easily followed
  //          from a mathematical point of view.
  // NOTE:    This is a left-chain Hamiltonian quaternion.
  // TODO:    Clean up these comments and make it read better.
  //----------------------------------------------------------------------------
  class Quaternion
  {
    // Data
    union
    {
      double e[4];
      struct
      {
        double s;
        Vector v;
      };
      struct
      {
        double w;
        double x;
        double y;
        double z;
      };
    };

    
    // Constructors
    Quaternion();
    Quaternion(double w_,
               double x_,
               double y_,
               double z_);
    Quaternion(double        s_,
               const Vector& v_);
    Quaternion(const Vector& axis_,
               double        rotation_);
    Quaternion(const Matrix& dcm_);
    Quaternion(const Vector& q_);
    Quaternion(const Quaternion& q_);
    Quaternion(const std::array<double, 4>& q_);
    Quaternion(const std::vector<double>& q_);


    // Destructor
    ~Quaternion();


    // Assignment Operator
    void operator=(const Quaternion& q_);


    // Conversion Operator
    // TODO:  Overload this operator to convert Quaternions into other objects, 
    //        too.
    void operator<<(const Vector& v_);
    void operator<<(const std::array<double, 4>& q_);
    void operator<<(const std::vector<double>& q_);
    void operator<<(const Matrix& dcm_);


    // Accessor
    double& operator[](unsigned int element_);


    // Setters
    void set(const std::array<double, 4>& q_);
    void set(const Matrix& dcm_);
    void set(const Quaternion& q_);
    void set(const Vector& q_);
    void set(const std::vector<double>& q_);
    void set(double        s_,
             const Vector& v_);
    void set(const Vector& axis_,
             double        rotation_);
    void set(double w_,
             double x_,
             double y_,
             double z_);

    // Unary -
    Quaternion operator-() const;


    // Comparison Operators
    bool operator==(const Quaternion& q_) const;
    bool operator!=(const Quaternion& q_) const;


    // Addition & Subtraction
    Quaternion operator+(const Quaternion& q_) const;
    void       operator+=(const Quaternion& q_);
    Quaternion operator-(const Quaternion& q_) const;
    void       operator-=(const Quaternion& q_);


    // Scalar Multiplication & Division
    Quaternion operator*(double s_) const;
    void       operator*=(double s_);
    Quaternion operator/(double s_) const;
    void       operator/=(double s_);


    // Quaternion Pre-Multiplication (this * q_)
    Quaternion operator*(const Quaternion& q_) const;
    void       operator*=(const Quaternion& q_);


    // Quaternion Post-Division (this * (1/q_))
    Quaternion operator/(const Quaternion& q_) const;
    void       operator/=(const Quaternion& q_);


    // Magnitude (Tensor)
    double magnitude(void) const;
    double tensor(void) const;


    // Quaternion Norm (w*w + x*x + y*y + z*z)
    double norm(void) const;


    // Unit (Versor)
    void unitize(void);
    Quaternion unit(void) const;
    Quaternion versor(void) const;


    // Quaternion Conjugate
    Quaternion conjugate(void) const;


    // Quaternion Inverse
    Quaternion inverse(void) const;
    void       invert(void);


    // Zeroize
    void zeroize();


  }; // !Quaternion


  // Scalar Multiplication
  Quaternion operator*(double            s_,
                       const Quaternion& q_);


  // Vector Quotient
  Quaternion operator/(math::Vector lhs,
                       math::Vector rhs);


} // !math


#endif // !QUATERNION_H
