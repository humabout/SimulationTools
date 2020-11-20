// vector_3d.h


#ifndef VECTOR_3D_H
#define VECTOR_3D_H


// Inclusions
#include <array>
#include <cassert>
#include <vector>
#include "math_config.h"


//------------------------------------------------------------------------------
// Name:    math
// Purpose: This namespace holds all math objects, functions, and constants.
//------------------------------------------------------------------------------
namespace math
{


  //----------------------------------------------------------------------------
  // Name:    Vector3D
  // Purpose: This class holds a vector in R3 and all of the operators and 
  //          methods that operate on 3-vectors within the context of geometric
  //          algebra and calculus.
  //----------------------------------------------------------------------------
  template <class T>
  class Vector3D
  {
  public:
    // Data
    union
    {
      T e[3];
      struct
      {
        T x;
        T y;
        T z;
      };
    };

    // Constructors
    Vector3D<T>()
    {
      zeroize();
    }
    Vector3D<T>(T x_, 
                T y_, 
                T z_)
    {
      set(x_, y_, z_);
    }
    Vector3D<T>(const std::array<T, 3>& v_)
    {
      set(v_);
    }
    Vector3D<T>(const std::vector<T>& v_)
    {
      set(v_);
    }
    Vector3D<T>(const Vector3D<T>& v_)
    {
      set(v_);
    }


    // Destructor
    ~Vector3D<T>()
    {
      // Nothing to delete.
    }


    // Setters
    void operator=(const Vector3D<T>& v_)
    {
      this->e[0] = v_[0];
      this->e[1] = v_[1];
      this->e[2] = v_[2];
    }
    void operator=(const std::array<T,3>& v_)
    {
      this->e[0] = v_[0];
      this->e[1] = v_[1];
      this->e[2] = v_[2];
    }
    void operator=(const std::vector<T>& v_)
    {
      // TODO: Make more robust and remove this assert. This shouldn't crash the
      //       programs just because a bad vector was provided.
      assert(v_.size == 3);
      this->e[0] = v_[0];
      this->e[1] = v_[1];
      this->e[2] = v_[2];
    }
    void set(T x_,
             T y_,
             T z_)
    {
      this->x = x_;
      this->y = y_;
      this->z = z_;
    }
    void set(const std::array<T, 3> v_)
    {
      *this = v_;
    }
    void set(const std::vector<T> v_)
    {
      *this = v_;
    }
    void set(const Vector3D<T>& v_)
    {
      *this = v_;
    }


    // Accessors
    T& operator[](unsigned int element_)
    {
      return e[element_];
    }
    unsigned int size(void) const
    {
      return 3;
    }
    unsigned int dim(void) const
    {
      return size();
    }
    unsigned int length(void) const
    {
      return size();
    }


    // Comparison Operators
    bool operator==(const Vector3D<T>& v_)
    {
      return ( (this->x == v_.x) &&
               (this->y == v_.y) &&
               (this->z == v_.z) );
    }
    bool operator!=(const Vector3D<T>& v_)
    {
      return ( (this->x != v_.x) ||
               (this->y != v_.y) ||
               (this->z != v_.z) );
    }


    // Unary -
    Vector3D<T> operator-()
    {
      return Vector3D<T>(-this->x,
                         -this->y,
                         -this->z);
    }


    // Addition & Subtraction
    Vector3D<T> operator+(const Vector3D<T>& v_)
    {
      return Vector3D<T>(this->x + v_.x,
                         this->y + v_.y,
                         this->z + v_.z);
    }
    void operator+=(const Vector3D<T>& v_)
    {
      (*this) = (*this) + v_;
    }
    Vector3D<T> operator-(const Vector3D<T>& v_)
    {
      return (*this) + -(v_);
    }
    void operator-=(const Vector3D<T>& v_)
    {
      (*this) = (*this) - v_;
    }


    // Scalar Multiplication & Division
    Vector3D<T> operator*(T s_)
    {
      return Vector3D<T>(s_ * this->x,
                         s_ * this->y,
                         s_ * this->z);
    }
    void operator*=(T s_)
    {
      (*this) = s_ * (*this);
    }
    Vector3D<T> operator/(T s_)
    {
      // TODO: Make this more robust against division by near-zero. Perahps
      //       divide by a default value if near zero?
      assert(abs(s_) < math::DIVIDE_BY_ZERO_TOLERANCE));
      return (*this) * (1 / s_);
    }
    void operator/=(T s_)
    {
      (*this) = (*this) / s_;
    }


    // Inner (Dot) Product
    T operator*(const Vector3D<T>& v_)
    {
      return this->x * v_.x +
             this->y + v_.y +
             this->z + v_.z;
    }
    T dot(const Vector3D<T>& v_)
    {
      return (*this) * v_;
    }

    // Outer (Wedge) Product
    Vector3D<T> operator%(const Vector3D<T> v_)
    {
      return Vector3D<T>( (this->x) * v_.y - (this->y) * v_.x,
                          (this->x) * v_.z - (this->z) * v_.x,
                          (this->y) * v_.z - (this->z) * v_.y );
    }
    void operator%=(const Vector3D<T> v_)
    {
      (*this) = (*this) % v_;
    }
    Vector3D<T> wedge(const Vector3D<T> v_)
    {
      return (*this) % v_;
    }


    // Gemoetric Product
    // TODO: Make this method once the rotor class is made

    // Magnitude
    T magnitude(void) const
    {
      // TODO: Consider storing this after calculating it the first time and 
      //       returning it on subsequent calls. This would require some sort of
      //       flag or way of informing this function that it needs to 
      //       recalculate the magnitude whenever another function changes the 
      //       value of the vector. Exposing the vector's data makes this 
      //       impossible, so new setters would be needed. This might not be 
      //       worth doing, in retrospect.
      return sqrt( (this->x) * (this->x) +
                   (this->y) * (this->y) +
                   (this->z) * (this->z) );
    }

    // Normalize
    void normalize(void)
    {
      (*this) = this->unit();
    }
    Vector3D<T> unit(void) const
    {
      T mag = this->magnitude();
      return (*this) / mag;
    }
    
    // Zeroize
    void zeroize(void)
    {
      set(0, 0, 0);
    }


  }; // !Vector3D


  // Operator* Overload for scalar * vector
  // TODO: Double check that this works right. Might need specific overloads for
  //       different data types
  template<class T>
  math::Vector3D<T> operator*(T s_,
                              const Vector3D<T>& v_)
  {
    return v_ * s_;
  }


} // !math


#endif // !VECTOR_3D_H
