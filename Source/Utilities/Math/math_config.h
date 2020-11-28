// math_config.h


#ifndef MATH_CONFIG_H
#define MATH_CONFIG_H


//------------------------------------------------------------------------------
// Name:    math
// Purpose: This namespace holds all math objects, functions, and constants.
//------------------------------------------------------------------------------
namespace math
{
  // Proximity to zero where division by zero becomes unstable
  static const double DIVIDE_BY_ZERO_TOLERANCE = 1e-6;
  
  // Provide definitions for common multiples of Pi
  static const double PI = 3.141592653589793;
  static const double TWO_PI = 2 * PI;
  static const double HALF_PI = 0.5 * PI;


} // !math


#endif // !MATH_CONFIG_H
