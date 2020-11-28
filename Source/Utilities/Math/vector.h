// vector.h


#ifndef VECTOR_H
#define VECTOR_H


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
    Vector()
    {
      zeroize();
    }
    Vector(double x_,
           double y_,
           double z_)
    {
      set(x_, y_, z_);
    }
    Vector(const std::array<double, 3>& v_)
    {
      set(v_);
    }
    Vector(const std::vector<double>& v_)
    {
      set(v_);
    }
    Vector(const Vector& v_)
    {
      set(v_);
    }


    // Destructor
    ~Vector()
    {
      // Nothing to delete.
    }


    // Accessors
    double& operator[](unsigned int element_)
    {
      return e[element_];
    }


    // Setters
    void operator=(const Vector& v_)
    {
      this->e[0] = v_.e[0];
      this->e[1] = v_.e[1];
      this->e[2] = v_.e[2];
    }
    void operator=(const std::array<double, 3>& v_)
    {
      this->e[0] = v_[0];
      this->e[1] = v_[1];
      this->e[2] = v_[2];
    }
    void operator=(const std::vector<double>& v_)
    {
      // TODO: Make more robust and remove this assert. This shouldn't crash the
      //       programs just because a bad vector was provided.
      assert(v_.size() == 3);
      this->e[0] = v_[0];
      this->e[1] = v_[1];
      this->e[2] = v_[2];
    }
    void set(double x_,
             double y_,
             double z_)
    {
      this->x = x_;
      this->y = y_;
      this->z = z_;
    }
    void set(const std::array<double, 3> v_)
    {
      *this = v_;
    }
    void set(const std::vector<double> v_)
    {
      *this = v_;
    }
    void set(const Vector& v_)
    {
      *this = v_;
    }


    // Comparison Operators
    bool operator==(const Vector& v_) const
    {
      return ( (this->e[0] == v_.e[0]) &&
               (this->e[1] == v_.e[1]) &&
               (this->e[2] == v_.e[2]) );
    }
    bool operator!=(const Vector& v_) const
    {
      return ( (this->e[0] != v_.e[0]) ||
               (this->e[1] != v_.e[1]) ||
               (this->e[2] != v_.e[2]) );
    }


    // Unary -
    Vector operator-() const
    {
      return Vector( -this->e[0],
                     -this->e[1],
                     -this->e[2] );
    }


    // Addition & Subtraction
    Vector operator+(const Vector& v_) const
    {
      return Vector( this->e[0] + v_.e[0],
                     this->e[1] + v_.e[1],
                     this->e[2] + v_.e[2]);
    }
    void operator+=(const Vector& v_)
    {
      (*this) = (*this) + v_;
    }
    Vector operator-(const Vector& v_) const
    {
      return Vector( this->e[0] - v_.e[0],
                     this->e[1] - v_.e[1],
                     this->e[2] - v_.e[2] );
    }
    void operator-=(const Vector& v_)
    {
      (*this) = (*this) - v_;
    }


    // Scalar Multiplication & Division
    Vector operator*(double s_) const
    {
      return Vector( s_ * this->e[0],
                     s_ * this->e[1],
                     s_ * this->e[2]);
    }
    void operator*=(double s_)
    {
      (*this) = (*this) * s_;
    }
    Vector operator/(const double& s_) const
    {
      // TODO: Make this more robust against division by near-zero. Perahps
      //       divide by a default value if near zero?
      assert(abs(s_) < math::DIVIDE_BY_ZERO_TOLERANCE);
      return (*this) * (1 / s_);
    }
    void operator/=(const double& s_)
    {
      (*this) = (*this) / s_;
    }


    // Dot Product
    double dot(const Vector& v_) const
    {
      return this->e[0] * v_.e[0] +
             this->e[1] + v_.e[1] +
             this->e[2] + v_.e[2];
    }
    double operator*(const Vector& v_) const
    {
      return this->dot(v_);
    }

    // Cross Product
    Vector cross(const Vector& v_) const
    {
      return Vector( (this->e[1]) * v_.e[2] - (this->e[2]) * v_.e[1],
                     (this->e[2]) * v_.e[0] - (this->e[0]) * v_.e[2],
                     (this->e[0]) * v_.e[1] - (this->e[1]) * v_.e[0]);
    }
    Vector operator%(const Vector& v_) const
    {
      return this->cross(v_);
    }
    void operator%=(const Vector& v_)
    {
      (*this) = this->cross(v_);
    }


    // Magnitude
    double magnitude(void) const
    {
      return sqrt( (this->e[0]) * (this->e[0]) +
                   (this->e[1]) * (this->e[1]) +
                   (this->e[2]) * (this->e[2]) );
    }


    // Normalize
    void normalize(void)
    {
      (*this) = this->unit();
    }
    Vector unit(void) const
    {
      return (*this) / (this->magnitude());
    }

    
    // Zeroize
    void zeroize(void)
    {
      set(0, 0, 0);
    }
    
  private:


  }; // !Vector


  // Operator* Overload for scalar * vector
  // TODO: Double check that this works right. Might need specific overloads for
  //       different data types
  math::Vector operator*(double s_,
                         Vector v_)
  {
    return v_ * s_;
  }


} // !math


#endif // !VECTOR_H
