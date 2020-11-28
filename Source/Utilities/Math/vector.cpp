// vector.cpp


// Inclusions
#include <cassert>
#include <cmath>
#include "math_config.h"
#include "quaternion.h"
#include "vector.h"


//------------------------------------------------------------------------------
// Name:    Vector
// Purpose: Default Constructor. Sets all elements to zero.
//------------------------------------------------------------------------------
math::Vector::Vector()
{
  this->zeroize();
}


//------------------------------------------------------------------------------
// Name:    Vector
// Purpose: Copy Constructor.
//------------------------------------------------------------------------------
math::Vector::Vector(const Vector& v_)
{
  this->set(v_);
}


//------------------------------------------------------------------------------
// Name:    Vector
// Purpose: Constructor Overload. Sets the vector's elements to those provided.
//------------------------------------------------------------------------------
math::Vector::Vector(double x_,
                     double y_,
                     double z_)
{
  this->set(x_, y_, z_);
}


//------------------------------------------------------------------------------
// Name:    ~Vector
// Purpose: Destructor. This objet owns nothing and deletes nothing.
//------------------------------------------------------------------------------
math::Vector::~Vector()
{
  // Does nothing in abudnance.
}


//------------------------------------------------------------------------------
// Name:    operator[]
// Purpose: Accesses the element at the given index. This is zero-indexed.
//------------------------------------------------------------------------------
double& math::Vector::operator[](unsigned int element_)
{
  return this->e[element_];
}


//------------------------------------------------------------------------------
// Name:    operator=
// Purpose: Assignement Operator.
//------------------------------------------------------------------------------
void math::Vector::operator=(const Vector& v_)
{
  this->e[0] = v_.e[0];
  this->e[1] = v_.e[1];
  this->e[2] = v_.e[2];
}


//------------------------------------------------------------------------------
// Name:    set
// Purpose: Sets the elements of this vector equal to those values provieded.
//------------------------------------------------------------------------------
void math::Vector::set(double x_,
                       double y_,
                       double z_)
{
  this->x = x_;
  this->y = y_;
  this->z = z_;
}


//------------------------------------------------------------------------------
// Name:    set
// Purpose: Sets this vector equal to the Vector provided.
//------------------------------------------------------------------------------
void math::Vector::set(const Vector& v_)
{
  *this = v_;
}


//------------------------------------------------------------------------------
// Name:    operator==
// Purpose: Returns true if the two vectors are equal.
//------------------------------------------------------------------------------
bool math::Vector::operator==(const Vector& v_) const
{
  return ( (this->e[0] == v_.e[0]) &&
           (this->e[1] == v_.e[1]) &&
           (this->e[2] == v_.e[2]) );
}


//------------------------------------------------------------------------------
// Name:    operator!=
// Purpose: Returns true if the two vectors are not equal.
//------------------------------------------------------------------------------
bool math::Vector::operator!=(const Vector& v_) const
{
  return !(*this == v_);
}


//------------------------------------------------------------------------------
// Name:    operator-
// Purpose: Unary -. Negates this vector.
//------------------------------------------------------------------------------
math::Vector math::Vector::operator-() const
{
  return Vector(-this->x,
                -this->y,
                -this->z);
}


//------------------------------------------------------------------------------
// Name:    operator+
// Purpose: Returns the sum of this and another vector.
//------------------------------------------------------------------------------
math::Vector math::Vector::operator+(const Vector& v_) const
{
  return Vector(this->e[0] + v_.e[0],
                this->e[1] + v_.e[1],
                this->e[2] + v_.e[2]);
}


//------------------------------------------------------------------------------
// Name:    operator+=
// Purpose: Sets this vector equal to the sum of itself and another vector.
//------------------------------------------------------------------------------
void math::Vector::operator+=(const Vector& v_)
{
  *this = *this + v_;
}


//------------------------------------------------------------------------------
// Name:    operator-
// Purpose: Returns the difference of this and another vector.
//------------------------------------------------------------------------------
math::Vector math::Vector::operator-(const Vector& v_) const
{
  return *this + -v_;
}


//------------------------------------------------------------------------------
// Name:    operato-=
// Purpose: Sets this vector equal to the difference between itself and another 
//          vector.
//------------------------------------------------------------------------------
void math::Vector::operator-=(const Vector& v_)
{
  *this = *this - v_;
}


//------------------------------------------------------------------------------
// Name:    operator*
// Purpose: Returns the scalar product of this vector and a scalar.
//------------------------------------------------------------------------------
math::Vector math::Vector::operator*(double s_) const
{
  return Vector(s_ * this->x,
                s_ * this->y,
                s_ * this->z);
}


//------------------------------------------------------------------------------
// Name:    operator*=
// Purpose: Sets this vector equal to the scalar product of itself and a scalar.
//------------------------------------------------------------------------------
void math::Vector::operator*=(double s_)
{
  *this = *this * s_;
}


//------------------------------------------------------------------------------
// Name:    operator/
// Purpose: Returns the scalar quotient of this vector and the given scalar.
//------------------------------------------------------------------------------
math::Vector math::Vector::operator/(const double& s_) const
{
  // TODO: Make this more robust against division by near-zero. Perahps
  //       divide by a default value if near zero?
  assert(abs(s_) > math::DIVIDE_BY_ZERO_TOLERANCE);
  return *this * (1 / s_);
}


//------------------------------------------------------------------------------
// Name:    operator/=
// Purpose: Sets this vector equal to itself divided by a scalar.
//------------------------------------------------------------------------------
void math::Vector::operator/=(const double& s_)
{
  *this = *this / s_;
}


//------------------------------------------------------------------------------
// Name:    dot
// Purpose: Returns the dot product of this and another vector.
//------------------------------------------------------------------------------
double math::Vector::dot(const Vector& v_) const
{
  return this->x * v_.x + this->y * v_.y + this->z * v_.z;
}


//------------------------------------------------------------------------------
// Name:    operator*
// Purpose: Returns the dot product of this and another vector.
//------------------------------------------------------------------------------
double math::Vector::operator*(const Vector& v_) const
{
  return this->dot(v_);
}


//------------------------------------------------------------------------------
// Name:    cross
// Purpose: returns the crossproduct of this vector and the given one.
//------------------------------------------------------------------------------
math::Vector math::Vector::cross(const Vector& v_) const
{
  return Vector(this->y * v_.z - this->z * v_.y,
                this->z * v_.x - this->x * v_.z,
                this->x * v_.y - this->y * v_.x);
}


//------------------------------------------------------------------------------
// Name:    operator%
// Purpose: returns the crossproduct of this vector and the given one.
//------------------------------------------------------------------------------
math::Vector math::Vector::operator%(const Vector& v_) const
{
  return this->cross(v_);
}


//------------------------------------------------------------------------------
// Name:    operator%=
// Purpose: Sets this vector equal to the crossproduct of itself and the given
//          vector.
//------------------------------------------------------------------------------
void math::Vector::operator%=(const Vector& v_)
{
  *this = this->cross(v_);
}


//------------------------------------------------------------------------------
// Name:    magnitude
// Purpose: Returns the Eulcidian norm of the vector.
//------------------------------------------------------------------------------
double math::Vector::magnitude(void) const
{
  return sqrt(x * x + y * y + z * z);
}


//------------------------------------------------------------------------------
// Name:    normalize
// Purpose: Normalizes this vector.
//------------------------------------------------------------------------------
void math::Vector::unitize(void)
{
  *this = this->unit();
}


//------------------------------------------------------------------------------
// Name:    unit
// Purpose: Returns a the unit vector of this vector.
//------------------------------------------------------------------------------
math::Vector math::Vector::unit(void) const
{
  return *this / this->magnitude();
}


//------------------------------------------------------------------------------
// Name:    zeroize
// Purpose: Sets this vector to a zero vector.
//------------------------------------------------------------------------------
void math::Vector::zeroize(void)
{
  this->set(0, 0, 0);
}


//------------------------------------------------------------------------------
// Name:    operator*
// Purpose: Binary scalar product operator. This allows for left-multiplication
//          of a vector by a scalar.
//------------------------------------------------------------------------------
math::Vector operator*(double              s_,
                       const math::Vector& v_) 
{
  return v_ * s_;
}