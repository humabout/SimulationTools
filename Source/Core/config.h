// config.h


// TODO: Make these user-defined, either via a file passed into the sim or 
// through some GUI menu thing.  I'm leaning toward config file for the moment.


#ifndef KERNEL_CONFIG_H
#define KERNEL_CONFIG_H


//----------------------------------------------------------------------------
// Name:    core
// Purpose: This namespace holds all parts of the simulation core.
//----------------------------------------------------------------------------
namespace core
{
  // Time Error Tolerance
  static const double TIME_ERROR_TOLERANCE = 1e-6; // [s]

} // !core

#endif // !KERNEL_CONFIG_H
