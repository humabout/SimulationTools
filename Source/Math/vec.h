// vec.h


#ifndef NEMESIS_VEC_H
#define NEMESIS_VEC_H


// Inclusions
#include <stdexcept>
#include <utility>
#include "math_config.h"


//------------------------------------------------------------------------------
// Name:    nemesis
// Purpose: This namespace holds all aspects of the Nemesis Simulation Toolkit.
//------------------------------------------------------------------------------
namespace nemesis
{


  //----------------------------------------------------------------------------
  // Name:    Vec
  // Purpose: This class template represents an n-vector. It stores the vector's
  //          elements and dimensionality. It also defines common operations on
  //          vectors. Finally, it provides specific implementations for 2- and
  //          3-vectors, with hard-coded solutions to accelerate their use.
  // Inputs:  Type
  //          Length
  //----------------------------------------------------------------------------
  template <class T, unsigned int N>
  class Vec
  {
  public:
    // Typedefs
    typedef nemesis::Vec<T, N> vec;
    typedef std::pair<unsigned int, unsigned int> dimension;

    // Constructor
    Vec()
    {
      this->zeroize();
    }
    Vec(const T(& v)[N])
    {
      this->set(v);
    }
    Vec(const vec& v)
    {
      this->set(v);
    }


    // Destructor
    ~Vec()
    {
      // Does Nothing
    }


    // Setters
    void set(const T(& v)[N])
    {
      for (unsigned int i = 0; i < N; i++)
      {
        this->E[i] = v[i];
      }
    }
    void set(const vec& v)
    {
      for (unsigned int i = 0; i < N; i++)
      {
        this->E[i] = v.E[i];
      }
    }


    // Accessors
    T e(unsigned int pos) const
    {
      return this->E[pos];
    }

    // Return number of elements in the vector
    unsigned int length(void) const
    {
      return N;
    }
    unsigned int size(void) const
    {
      return N;
    }
    dimension dim(void) const
    {
      return dimension(N, 1);
    }


    // Access Operator
    T& operator[](unsigned int pos)
    {
      return this->E[pos];
    }
    const T& operator[](const unsigned int& pos) const
    {
      return this->E[pos];
    }


    // Assignment Operator
    void operator= (const vec& v)
    {
      this->set(v);
    }
    void operator= (const T(& v)[N])
    {
      this->set(v);
    }


    // Comparison Operators
    bool operator== (const vec& v) const
    {
      for (unsigned int i = 0; i < N; i++)
      {
        if (this->E[i] != v.E[i])
        {
          return false;
        }
      }
      return true;
    }
    bool operator!= (const vec& v) const
    {
      return !((*this) == v);
    }


    // Unary Negative
    vec operator-() const
    {
      Vec<T, N> output;
      for (unsigned int i = 0; i < N; i++)
      {
        output.E[i] = -(this->E[i]);
      }
      return output;
    }


    // Addition
    vec operator+(const vec& v) const
    {
      vec output;
      for (unsigned int i = 0; i < N; i++)
      {
        output.E[i] = this->E[i] + v.E[i];
      }
      return output;
    }
    void operator+=(const vec& v)
    {
      *this = *this + v;
    }


    // Subtraction
    vec operator-(const vec& v) const
    {
      return *this + -v;
    }
    void operator-=(const vec& v)
    {
      *this = *this - v;
    }


    // Scalar Multiplication
    vec operator* (T s) const
    {
      vec output;
      for (unsigned int i = 0; i < N; i++)
      {
        output.E[i] = this->E[i] * s;
      }
      return output;
    }
    void operator*= (T s)
    {
      *this = *this * s;
    }


    // Scalar Division
    vec operator/ (T s) const
    {
      T den = s;
      if (abs(s) < math::DIVIDE_BY_ZERO_TOLERANCE)
      {
        den = 1/math::DIVIDE_BY_ZERO_TOLERANCE;
        throw std::runtime_error("Warning: Division by near-zero. Dividing by tolerance, isntead.");
      }
      else
      {
        den = 1 / s;
      }
      return *this * den;
    }
    void operator/= (T s)
    {
      *this = *this / s;
    }


    // Dot Product
    T operator*(const vec& v) const
    {
      T dot_product = 0;
      for (unsigned int i = 0; i < N; i++)
      {
        dot_product += this->E[i] * v.E[i];
      }
      return dot_product;
    }


    // Magnitude
    T magnitude(void) const
    {
      T mag = 0;
      for (unsigned int i = 0; i < N; i++)
      {
        mag += this->E[i] * this->E[i];
      }
      return sqrt(mag);
    }


    // Unit & Unitization
    vec unit(void) const
    {
      return *this / (this->magnitude());
    }
    void unitize(void)
    {
      *this /= this->magnitude();
    }


    // Zeroize
    void zeroize(void)
    {
      for (unsigned int i = 0; i < N; i++)
      {
        this->E[i] = 0;
      }
    }

  private:
    // Vector Elements
    T E[N];


  }; // !Vec<T, N>


  //----------------------------------------------------------------------------
  // Specialized for N=2
  //----------------------------------------------------------------------------
  template <class T>
  class Vec<T, 2>
  {
  public:
    // Typedefs
    typedef nemesis::Vec<T, 2> vec;
    typedef std::pair<unsigned int, unsigned int> dimension;


    // Constructors
    Vec()
    {
      this->zeroize();
    }
    Vec(const T(& v)[2])
    {
      this->set(v);
    }
    Vec(const vec& v)
    {
      this->set(v);
    }
    Vec(const T& x_,
        const T& y_)
    {
      this->set(x_, y_);
    }


    // Destructor
    ~Vec()
    {
      // Does Nothing
    }


    // Setters
    void set(const T(& v)[2])
    {
      this->E[0] = v[0];
      this->E[1] = v[1];
    }
    void set(const vec& v)
    {
      this->E[0] = v.E[0];
      this->E[1] = v.E[1];
    }
    void set(const T& x_,
             const T& y_)
    {
      this->X = x_;
      this->Y = y_;
    }


    // Accessors
    T e(unsigned int pos) const
    {
      return this->E[pos];
    }

    // Return number of elements in the vector
    unsigned int length(void) const
    {
      return 2;
    }
    unsigned int size(void) const
    {
      return 2;
    }
    dimension dim(void) const
    {
      return dimension(2, 1);
    }


    // Access Operator
    T& operator[](unsigned int pos)
    {
      return this->E[pos];
    }
    const T& operator[](const unsigned int& pos) const
    {
      return this->E[pos];
    }
    T& x(void)
    {
      return this->X;
    }
    T& y(void)
    {
      return this->Y;
    }


    // Assignment Operator
    void operator= (const vec& v)
    {
      this->set(v);
    }
    void operator= (const T(& v)[2])
    {
      this->set(v);
    }


    // Comparison Operators
    bool operator== (const vec& v) const
    {
      return (this->X == v.X) && 
             (this->Y == v.Y);
    }
    bool operator!= (const vec& v) const
    {
      return (this->X != v.X) || 
             (this->Y != v.Y);
    }


    // Unary Negative
    vec operator-() const
    {
      return vec( -(this->X), 
                  -(this->Y) );
    }


    // Addition Operators
    vec operator+(const vec& v) const
    {
      return vec( (this->X + v.X),
                  (this->Y + v.Y)) ;
    }
    void operator+=(const vec& v)
    {
      *this = *this + v;
    }


    // Subtraction Operators
    vec operator-(const vec& v) const
    {
      return *this + -v;
    }
    void operator-=(const vec& v)
    {
      *this = *this - v;
    }


    // Scalar Multiplication Operators
    vec operator* (T s) const
    {
      return vec( s * this->X,
                  s * this->Y );
    }
    void operator*= (T s)
    {
      *this = *this * s;
    }


    // Scalar Division
    vec operator/ (T s) const
    {
      T den = s;
      if (abs(s) < math::DIVIDE_BY_ZERO_TOLERANCE)
      {
        den = 1 / math::DIVIDE_BY_ZERO_TOLERANCE;
        throw std::runtime_error("Warning: Division by near-zero. Dividing by tolerance, isntead.");
      }
      else
      {
        den = 1 / s;
      }
      return *this * den;
    }
    void operator/= (T s)
    {
      *this = *this / s;
    }


    // Dot Product Operators
    T operator* (const vec& v) const
    {
      return (this->X * v.X) +
             (this->Y * v.Y);
    }


    // Magnitude
    T magnitude(void) const
    {
      return sqrt( this->X * this->X +
                   this->Y * this->Y );
    }


    // Unit & Unitization
    vec unit(void) const
    {
      return *this / (this->magnitude());
    }
    void unitize(void)
    {
      *this /= this->magnitude();
    }


    // Zeroize
    void zeroize(void)
    {
      this->X = 0;
      this->Y = 0;
    }

  private:
    // Vector Elements
    union
    {
      T E[2];
      struct
      {
        T X;
        T Y;
      };
    };


  }; // !Vec<T, 2>



  //----------------------------------------------------------------------------
  // Specialized for N=3
  //----------------------------------------------------------------------------
  template <class T>
  class Vec<T, 3>
  {
  public:
    // Typedefs
    typedef nemesis::Vec<T, 3> vec;
    typedef std::pair<unsigned int, unsigned int> dimension;

    // Constructors
    Vec()
    {
      this->zeroize();
    }
    Vec(const T(& v)[3])
    {
      this->set(v);
    }
    Vec(const vec& v)
    {
      this->set(v);
    }
    Vec(const T& x_,
        const T& y_,
        const T& z_)
    {
      this->set(x_, y_, z_);
    }

    // Destructor
    ~Vec()
    {
      // Does Nothing
    }


    // Setters
    void set(const T(& v)[3])
    {
      this->E[0] = v[0];
      this->E[1] = v[1];
      this->E[2] = v[2];
    }
    void set(const vec& v)
    {
      this->E[0] = v.E[0];
      this->E[1] = v.E[1];
      this->E[2] = v.E[2];
    }
    void set(const T& x_,
             const T& y_,
             const T& z_)
    {
      this->X = x_;
      this->Y = y_;
      this->Z = z_;
    }


    // Accessors
    T e(unsigned int pos) const
    {
      return this->E[pos];
    }

    // Return number of elements in the vector
    unsigned int length(void) const
    {
      return 3;
    }
    unsigned int size(void) const
    {
      return 3;
    }
    dimension dim(void) const
    {
      return dimension(3, 1);
    }


    // Access Operator
    T& operator[](unsigned int pos)
    {
      return this->E[pos];
    }
    const T& operator[](const unsigned int& pos) const
    {
      return this->E[pos];
    }
    T& x(void)
    {
      return this->X;
    }
    T& y(void)
    {
      return this->Y;
    }
    T& z(void)
    {
      return this->Z;
    }


    // Assignment Operator
    void operator= (const vec& v)
    {
      this->set(v);
    }
    void operator= (const T(& v)[3])
    {
      this->set(v);
    }


    // Comparison Operators
    bool operator== (const vec& v) const
    {
      return (this->X == v.X) && 
             (this->Y == v.Y) && 
             (this->Z == v.Z);
    }
    bool operator!= (const vec& v) const
    {
      return (this->X != v.X) ||
             (this->Y != v.Y) ||
             (this->Z != v.Z);
    }


    // Unary Negative
    vec operator-() const
    {
      return vec( -(this->X),
                  -(this->Y),
                  -(this->Z) );
    }


    // Addition Operators
    vec operator+(const vec& v) const
    {
      return vec( (this->X + v.X),
                  (this->Y + v.Y),
                  (this->Z + v.Z) );
    }
    void operator+=(const vec& v)
    {
      *this = *this + v;
    }


    // Subtraction Operators
    vec operator-(const vec& v) const
    {
      return *this + -v;
    }
    void operator-=(const vec& v)
    {
      *this = *this - v;
    }


    // Scalar Multiplication Operators
    vec operator* (T s) const
    {
      return vec( s * this->X,
                  s * this->Y,
                  s * this->Z );
    }
    void operator*= (T s)
    {
      *this = *this * s;
    }


    // Scalar Division
    vec operator/ (T s) const
    {
      T den = s;
      if (abs(s) < math::DIVIDE_BY_ZERO_TOLERANCE)
      {
        den = 1 / math::DIVIDE_BY_ZERO_TOLERANCE;
        throw std::runtime_error("Warning: Division by near-zero. Dividing by tolerance, isntead.");
      }
      else
      {
        den = 1 / s;
      }
      return *this * den;
    }
    void operator/= (T s)
    {
      *this = *this / s;
    }


    // Dot Product Operators
    T operator* (const vec& v) const
    {
      return (this->X * v.X) +
             (this->Y * v.Y) +
             (this->Z * v.Z);
    }


    // Cross Product Operators
    vec operator% (const vec& v) const
    {
      return vec( (this->Y * v.Z - this->Z * v.Y),
                  (this->Z * v.X - this->X * v.Z),
                  (this->X * v.Y - this->Y * v.X) );
    }
    void operator%=(const vec& v)
    {
      *this = *this % v;
    }


    // Magnitude
    T magnitude(void) const
    {
      return sqrt( this->X * this->X + 
                   this->Y * this->Y +
                   this->Z * this->Z );
    }


    // Unit & Unitization
    vec unit(void) const
    {
      return *this / (this->magnitude());
    }
    void unitize(void)
    {
      *this /= this->magnitude();
    }


    // Zeroize
    void zeroize(void)
    {
      this->X = 0;
      this->Y = 0;
      this->Z = 0;
    }

  private:
    // Vector Elements
    union
    {
      T E[3];
      struct
      {
        T X;
        T Y;
        T Z;
      };
    };


  }; // !Vec<T, 3>


  //----------------------------------------------------------------------------
  // Typedefs & Aliases
  //----------------------------------------------------------------------------
  template <class T> using Vec2 = Vec<T, 2>;
  template <class T> using Vec3 = Vec<T, 3>;



} // !nemesis


//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
// Operator Overrides
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>


// operator* overload for type T * Vec
template <class T, unsigned int N>
nemesis::Vec<T, N> operator* (T s, nemesis::Vec<T, N> v)
{
  return v * s;
}


#endif // !NEMESIS_VEC_H
