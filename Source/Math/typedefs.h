// typedefs.h


#ifndef MATH_TYPEDEFS_H
#define MATH_TYPEDEFS_H


// Inclusions
#include <utility>


//------------------------------------------------------------------------------
// Name:    nemesis
// Purpose: This namespace holds all aspects of the Nemesis Simulation Toolkit.
//------------------------------------------------------------------------------
namespace nemesis
{


  // Element position within a matrix, quaternion, vector, etc.
  typedef unsigned int element;

  // Size of one dimension of a matrix, quaternion, vector, etc.
  typedef unsigned int dim_size;

  // An object that stores the dimensions of a matrix, quaternion, vector, etc.
  typedef std::pair<dim_size, dim_size> dimension;

} // !nemesis


#endif // !MATH_TYPEDEFS_H
