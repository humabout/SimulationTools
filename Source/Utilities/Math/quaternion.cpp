// quaterion.cpp


// Inclusions
#include <algorithm>
#include <stdexcept>
#include "math_config.h"
#include "matrix.h"
#include "quaternion.h"
#include "vector.h"


//------------------------------------------------------------------------------
// Name:    Quaternion
// Purpose: Default Constructor. Sets all elements to zero.
//------------------------------------------------------------------------------
math::Quaternion::Quaternion()
{
  this->zeroize();
}


//------------------------------------------------------------------------------
// Name:    Quaternion
// Purpose: Copy Constructor
//------------------------------------------------------------------------------
math::Quaternion::Quaternion(const Quaternion& q_)
{
  this->set(q_);
}


//------------------------------------------------------------------------------
// Name:    Quaternion
// Purpose: Constructor Overload. This takes a Matrix, assumes it is a DCM, and
//          builds a quaternion from it.
//------------------------------------------------------------------------------
math::Quaternion::Quaternion(const Matrix& dcm_)
{
  this->set(dcm_);
}


//------------------------------------------------------------------------------
// Name:    Quaternion
// Purpose: Constructor Overload. This takes a vector and builds a pure 
//          quaternion from it.
//------------------------------------------------------------------------------
math::Quaternion::Quaternion(const Vector& v_)
{
  this->set(v_);
}


//------------------------------------------------------------------------------
// Name:    Quaternion
// Purpose: Constructor Overload. This takes a scalar and a Vector and builds a
//          quaternion from them.
//------------------------------------------------------------------------------
math::Quaternion::Quaternion(double        s_,
                             const Vector& v_)
{
  this->set(s_, v_);
}


//------------------------------------------------------------------------------
// Name:    Quaternion
// Purpose: Constructor Overload. This takes an angle and an axis of rotation
//          and builds a versor from it.
//------------------------------------------------------------------------------
math::Quaternion::Quaternion(const Vector& axis_,
                             double        angle_)
{
  this->set(axis_, angle_);
}


//------------------------------------------------------------------------------
// Name:    Quaternion
// Purpose: Constructor Overload. This sets the quaternion's elements to those
//          provided.
//------------------------------------------------------------------------------
math::Quaternion::Quaternion(double w_,
                             double x_,
                             double y_,
                             double z_)
{
  this->set(w_, x_, y_, z_);
}


//------------------------------------------------------------------------------
// Name:    ~Quaternion
// Purpose: Destrutor. This class owns nothing and deletes nothing.
//------------------------------------------------------------------------------
math::Quaternion::~Quaternion()
{
  // Does nothing.
}


//------------------------------------------------------------------------------
// Name:    operator=
// Purpose: Assignment operator
//------------------------------------------------------------------------------
void math::Quaternion::operator=(const Quaternion& q_)
{
  this->w = q_.w;
  this->x = q_.x;
  this->y = q_.y;
  this->z = q_.z;
}


//------------------------------------------------------------------------------
// Name:    Operator<<
// Purpose: Converts the the argument to a pure quaternion and stores it in this
//          quaternion. This is an operator version of the set() method.
//------------------------------------------------------------------------------
void math::Quaternion::operator<<(const Vector& v_)
{
  this->w = 0;
  this->x = v_.x;
  this->y = v_.y;
  this->z = v_.z;
}


//------------------------------------------------------------------------------
// Name:    operator<<
// Purpose: Builds a quaternion from the provided DCM. This produces a 
//          Hamiltonian Left Chain quaternion (p' = q*p*q^-1).
//------------------------------------------------------------------------------
void math::Quaternion::operator<<(const Matrix& dcm_)
{
  double trace = dcm_.trace();
  double max_element = std::max(dcm_.e11, 
                                std::max(dcm_.e22, 
                                         std::max(dcm_.e33, trace)));
  double qmax = 0.5 * sqrt(1 - trace + 2 * max_element);
  double one_by_four_qmax = 1 / (4 * qmax);

  if (max_element == dcm_.e11)
  {
    this->x = qmax;
    this->y = (dcm_.e12 + dcm_.e21) * one_by_four_qmax;
    this->z = (dcm_.e13 + dcm_.e31) * one_by_four_qmax;
    this->w = (dcm_.e32 - dcm_.e23) * one_by_four_qmax;
  }
  else if (max_element == dcm_.e22)
  {
    this->x = (dcm_.e12 + dcm_.e21) * one_by_four_qmax;
    this->y = qmax;
    this->z = (dcm_.e23 + dcm_.e32) * one_by_four_qmax;
    this->w = (dcm_.e13 - dcm_.e31) * one_by_four_qmax;
  }
  else if (max_element == dcm_.e33)
  {
    this->x = (dcm_.e13 + dcm_.e31) * one_by_four_qmax;
    this->y = (dcm_.e23 + dcm_.e32) * one_by_four_qmax;
    this->z = qmax;
    this->w = (dcm_.e13 - dcm_.e31) * one_by_four_qmax;
  }
  else
  {
    this->x = (dcm_.e32 - dcm_.e23) * one_by_four_qmax;
    this->y = (dcm_.e13 - dcm_.e31) * one_by_four_qmax;
    this->z = (dcm_.e21 - dcm_.e12) * one_by_four_qmax;
    this->w = qmax;
  }
}


//------------------------------------------------------------------------------
// Name:    set
// Purpose: Treats the given matrix as a DCM and converts it to a quaternion. It
//          then sets this quaternion to that result.
//------------------------------------------------------------------------------
void math::Quaternion::set(const Matrix& dcm_)
{
  *this << dcm_;
}


//------------------------------------------------------------------------------
// Name:    set
// Purpose: Sets this quaternion equal to another.
//------------------------------------------------------------------------------
void math::Quaternion::set(const Quaternion& q_)
{
  *this = q_;
}


//------------------------------------------------------------------------------
// Name:    set
// Purpose: Sets this quaternion to a pure quaternion built from the provided
//          vector.
//------------------------------------------------------------------------------
void math::Quaternion::set(const Vector& v_)
{
  *this << v_;
}


//------------------------------------------------------------------------------
// Name:    set
// Purpose: Sets this quaternion to the given scalar and vector.
//------------------------------------------------------------------------------
void math::Quaternion::set(double        s_,
                           const Vector& v_)
{
  this->s = s_;
  this->v = v_;
}


//------------------------------------------------------------------------------
// Name:    set
// Purpose: Builds a quaternion from the provided axis of rotation and rotation
//          angle, given in radians.
// Inputs:  Axis of rotation [Vector]
//          Magnitude of Rotation [radians]
//------------------------------------------------------------------------------
void math::Quaternion::set(const Vector& axis_,
                           double        rotation_)
{
  double half_sin = sin(0.5 * rotation_);
  double half_cos = cos(0.5 * rotation_);

  // Ensuring that the axis is a unit vector
  Vector axis = axis_;
  axis.unitize();

  // Building the Quaternion
  this->w = half_cos;
  this->x = axis.x * half_sin;
  this->y = axis.y * half_sin;
  this->z = axis.z * half_sin;
}


//------------------------------------------------------------------------------
// Name:    set
// Purpose: Sets this quaternion's elements to the arguments provided.
//------------------------------------------------------------------------------
void math::Quaternion::set(double w_,
                           double x_,
                           double y_,
                           double z_)
{
  this->w = w_;
  this->x = x_;
  this->y = y_;
  this->z = z_;
}


//------------------------------------------------------------------------------
// Name:    zeroize
// Purpose: Sets this quaternion's elements to zero.
//------------------------------------------------------------------------------
void math::Quaternion::zeroize()
{
  set(0, 0, 0, 0);
}


//------------------------------------------------------------------------------
// Name:    operator[]
// Purpose: Returns the given element, indexed from zero.
//------------------------------------------------------------------------------
double& math::Quaternion::operator[](unsigned int element_)
{
  return this->e[element_];
}


//------------------------------------------------------------------------------
// Name:    operator-
// Purpose: Returns the negative of the quaternion.
//------------------------------------------------------------------------------
math::Quaternion math::Quaternion::operator-() const
{
  return Quaternion(-(this->w),
                    -(this->x),
                    -(this->y),
                    -(this->z));
}


//------------------------------------------------------------------------------
// Name:    operator==
// Purpose: Returns true if the quaternions are the same.
//------------------------------------------------------------------------------
bool math::Quaternion::operator==(const Quaternion& q_) const
{
  return (this->w == q_.w) &&
         (this->x == q_.x) &&
         (this->y == q_.y) &&
         (this->z == q_.z);
}


//------------------------------------------------------------------------------
// Name:    operator!=
// Purpose: Returns true if the quaternions are not the same.
//------------------------------------------------------------------------------
bool math::Quaternion::operator!=(const Quaternion& q_) const
{
  return !(*this == q_);
}


//------------------------------------------------------------------------------
// Name:    operator+
// Purpose: Returns the sum of the two quaternions.
//------------------------------------------------------------------------------
math::Quaternion math::Quaternion::operator+(const Quaternion& q_) const
{
  return Quaternion(this->w + q_.w,
                    this->x + q_.x,
                    this->y + q_.y,
                    this->z + q_.z);
}


//------------------------------------------------------------------------------
// Name:    operator+=
// Purpose: Sets this quaternion to the sum of itself and the argument.
//------------------------------------------------------------------------------
void math::Quaternion::operator+=(const Quaternion& q_)
{
  *this = *this + q_;
}


//------------------------------------------------------------------------------
// Name:    operator-
// Purpose: Returns the difference between this quaternion and another.
//------------------------------------------------------------------------------
math::Quaternion math::Quaternion::operator-(const Quaternion& q_) const
{
  return *this + -q_;
}


//------------------------------------------------------------------------------
// Name:    operator-=
// Purpose: Sets this quaternion equal to the difference of itself and the 
//          argument.
//------------------------------------------------------------------------------
void math::Quaternion::operator-=(const Quaternion & q_)
{
  *this = *this - q_;
}


//------------------------------------------------------------------------------
// Name:    operator*
// Purpose: Returns the product of a quaternion and a scalar.
//------------------------------------------------------------------------------
math::Quaternion math::Quaternion::operator*(double s_) const
{
  return Quaternion(s_ * this->w,
                    s_ * this->x,
                    s_ * this->y,
                    s_ * this->z);
}


//------------------------------------------------------------------------------
// Name:    operator*=
// Purpose: Sets this quaternion's value to the product of itself and a scalar.
//------------------------------------------------------------------------------
void math::Quaternion::operator*=(double s_)
{
  *this = *this * s_;
}


//------------------------------------------------------------------------------
// Name:    operator/
// Purpose: Returns the scalar quotient of this quaternion and a scalar.
//------------------------------------------------------------------------------
math::Quaternion math::Quaternion::operator/(double s_) const
{
  // Check to make sure the denominator is not so close to zero that the result
  // becomes unstable.
  if (abs(s_) <= math::DIVIDE_BY_ZERO_TOLERANCE)
  {
    throw std::runtime_error("Warning: Division by near-zero may result in an unstable answer.");
  }

  // Perform Division
  return *this * (1 / s_);
}


//------------------------------------------------------------------------------
// Name:    operator/=
// Purpose: Sets this quaternion to the quotient of itself and a scalar.
//------------------------------------------------------------------------------
void math::Quaternion::operator/=(double s_)
{
  *this = *this / s_;
}


//------------------------------------------------------------------------------
// Name:    magnitude
// Purpose: Returns the magnitude, or tensor, of the quaternion.
//------------------------------------------------------------------------------
double math::Quaternion::magnitude(void) const
{
  return sqrt(this->norm());
}


//------------------------------------------------------------------------------
// Name:    tensor
// Purpose: Returns the tensor, or magnitude, of the quaternion.
//------------------------------------------------------------------------------
double math::Quaternion::tensor(void) const
{
  return this->magnitude();
}


//------------------------------------------------------------------------------
// Name:    norm
// Purpose: Returns the quaternion norm of the quaternion: the sum of squares of
//          the quaternion's elements.
//------------------------------------------------------------------------------
double math::Quaternion::norm(void) const
{
  return w * w + x * x + y * y + z * z;
}


//------------------------------------------------------------------------------
// Name:    unitize
// Purpose: Sets this quaternion to its own versor.
//------------------------------------------------------------------------------
void math::Quaternion::unitize()
{
  // Normalize the quaternion.
  *this = this->versor();
}


//------------------------------------------------------------------------------
// Name:    unit
// Purpose: Returns the unit-quaternion, or versor, built on this quaternion.
//------------------------------------------------------------------------------
math::Quaternion math::Quaternion::unit(void) const
{
  double mag = this->tensor();

  // Checking if the tensor is too close to zero to be stable. This is done here
  // rather than in the impending division so the error will throw from here.
  if (abs(mag) <= math::DIVIDE_BY_ZERO_TOLERANCE)
  {
    throw std::runtime_error("Warning: Division by near-zero may result in an unstable answer.");
  }

  // Normalize the quaternion.
  return *this / mag;
}


//------------------------------------------------------------------------------
// Name:    versor
// Purpose: Returns the unit-quaternion, or versor, built on this quaternion.
//------------------------------------------------------------------------------
math::Quaternion math::Quaternion::versor(void) const
{
  return this->unit();
}


//------------------------------------------------------------------------------
// Name:    conjugate
// Purpose: Returns the conjugate of the quaternion.
//------------------------------------------------------------------------------
math::Quaternion math::Quaternion::conjugate(void) const
{
  return Quaternion( this->s,
                    -this->v);
}


//------------------------------------------------------------------------------
// Name:    inverse
// Purpose: Returns the inverse of the quaternion.
//------------------------------------------------------------------------------
math::Quaternion math::Quaternion::inverse(void) const
{
  return this->conjugate() / this->norm();
}


//------------------------------------------------------------------------------
// Name:    invert
// Purpose: Sets this quaternion equal to its inverse.
//------------------------------------------------------------------------------
void math::Quaternion::invert(void)
{
  *this = this->inverse();
}


//------------------------------------------------------------------------------
// Name:    rotatedBy
// Purpose: Returns a quaternion rotated by the provided quaternion. If the 
//          input is not a versor, it is made one.
//------------------------------------------------------------------------------
math::Quaternion math::Quaternion::rotatedBy(const Quaternion& q_) const
{
  // Ensuring that the provided quaternion is a versor
  Quaternion R = q_.versor();
  return R * (*this) * R.inverse();  
}


//------------------------------------------------------------------------------
// Name:    operator*
// Purpose: Returns the scalar pre-product of the quaternion.
//------------------------------------------------------------------------------
math::Quaternion operator*(double                  s_,
                           const math::Quaternion& q_)
{
  return q_ * s_;
}


//------------------------------------------------------------------------------
// Name:    operator/
// Purpose: Returns the quaternion quotient of two vectors.
//------------------------------------------------------------------------------
math::Quaternion operator/(const math::Vector& lhs,
                           const math::Vector& rhs)
{
  return math::Quaternion (lhs) / math::Quaternion(rhs);
}


//------------------------------------------------------------------------------
// Name:    operator*
// Purpose: Returns the pre-product of this quaternion and the argument.
//          [this * arg]
//------------------------------------------------------------------------------
math::Quaternion math::Quaternion::operator*(const Quaternion& q_) const
{
  return Quaternion(
    this->w * q_.w - this->x * q_.x - this->y * q_.y - this->z * q_.z,
    this->w * q_.x + this->x * q_.w + this->y * q_.z - this->z * q_.y,
    this->w * q_.y - this->x * q_.z + this->y * q_.w + this->z * q_.x,
    this->w * q_.z + this->x * q_.y - this->y * q_.x + this->z * q_.w
  );
}


//------------------------------------------------------------------------------
// Name:    operator*=
// Purpose: Sets this quaternion equal to the pre-product of itself and the
//          argument. [this = this * arg]
//------------------------------------------------------------------------------
void math::Quaternion::operator*=(const Quaternion& q_)
{
  *this = *this * q_;
}


//------------------------------------------------------------------------------
// Name:    operator/
// Purpose: Returns the post-quotient of this quaternion and the argument.
//          [this * (1/arg)]
//------------------------------------------------------------------------------
math::Quaternion math::Quaternion::operator/(const Quaternion& q_) const
{
  return *this * q_.inverse();
}


//------------------------------------------------------------------------------
// Name:    operator/=
// Purpose: Sets this quaternion equal to the post-quotient of itself and the
//          argument [this = this * (1/arg)]
//------------------------------------------------------------------------------
void math::Quaternion::operator/=(const Quaternion& q_)
{
  *this = *this / q_;
}


//------------------------------------------------------------------------------
// Name:    operator/=
// Purpose: Generates and returns a DCM from this quaternion. If it is not a 
//          versor, it is made one, first.
//------------------------------------------------------------------------------
math::Matrix math::Quaternion::getDCM(void) const
{
  // Ensuring that a versor is used.
  Quaternion versor = this->versor();

  // Building the matrix
  double wx = versor.w * versor.x;
  double wy = versor.w * versor.y;
  double wz = versor.w * versor.z;
  double xx = versor.x * versor.x;
  double xy = versor.x * versor.y;
  double xz = versor.x * versor.z;
  double yy = versor.y * versor.y;
  double yz = versor.y * versor.z;
  double zz = versor.z * versor.z;
  return Matrix( 1 - 2 * (yy - zz),     2 * (xy - wz),     2 * (xz + wy),
                     2 * (xy + wz), 1 - 2 * (xx - zz),     2 * (yz - wx),
                     2 * (xz - wy),     2 * (yz + wx), 1 - 2 * (xx - yy) );
}


//------------------------------------------------------------------------------
// Name:    getAxis
// Purpose: Returns the axis of rotation vector of the quaternion.
//------------------------------------------------------------------------------
math::Vector math::Quaternion::getAxis(void) const
{
  return math::Vector(this->x, this->y, this->z).unit();
}


//------------------------------------------------------------------------------
// Name:    getAngle
// Purpose: Returns the angle through which the quaternion rotates vectors, in
//          radians.
//------------------------------------------------------------------------------
double math::Quaternion::getAngle(void) const
{
  return 2 * acos(w);
}