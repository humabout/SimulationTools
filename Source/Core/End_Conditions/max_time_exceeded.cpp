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
nemesis::MaxTimeExceeded::MaxTimeExceeded(double time_max_)
{
  Time_Max = time_max_;
}


//------------------------------------------------------------------------------
// Name:    ~MaxTimeExceeded
// Purpose: Destructor
//------------------------------------------------------------------------------
nemesis::MaxTimeExceeded::~MaxTimeExceeded()
{
  // This object has nothing to deallocate.
}


//------------------------------------------------------------------------------
// Name:    MaxTimeExceeded
// Purpose: If the current time has exceeded the maximum sim time by more than
//          the time error tolerance, this condition has been met.
//------------------------------------------------------------------------------
bool nemesis::MaxTimeExceeded::met(void)
{  
  double time_current = nemesis::SimClock::time();
  return ((Time_Max - time_current) < nemesis::TIME_ERROR_TOLERANCE);
}