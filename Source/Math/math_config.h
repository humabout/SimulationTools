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


} // !math


#endif // !MATH_CONFIG_H
