// max_time_exceeded


// Inclusions
#include <cstddef>
#include "max_time_exceeded.h"
#include "../config.h"
#include "../Clocks/sim_clock.h"


//------------------------------------------------------------------------------
// Name:    MaxTimeExceeded
// Purpose: Default Constructor
//------------------------------------------------------------------------------
core::MaxTimeExceeded::MaxTimeExceeded(double time_max_)
{
  Time_Max = time_max_;
}


//------------------------------------------------------------------------------
// Name:    ~MaxTimeExceeded
// Purpose: Destructor
//------------------------------------------------------------------------------
core::MaxTimeExceeded::~MaxTimeExceeded()
{
  // This object has nothing to deallocate.
}


//------------------------------------------------------------------------------
// Name:    MaxTimeExceeded
// Purpose: If the current time has exceeded the maximum sim time by more than
//          the time error tolerance, this condition has been met.
//------------------------------------------------------------------------------
bool core::MaxTimeExceeded::met(void)
{  
  double time_current = core::SimClock::time();
  return ((Time_Max - time_current) < core::TIME_ERROR_TOLERANCE);
}