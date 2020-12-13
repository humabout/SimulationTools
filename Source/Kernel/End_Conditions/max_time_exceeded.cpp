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
kernel::MaxTimeExceeded::MaxTimeExceeded()
{
  Time_Max     = 0;
}


//------------------------------------------------------------------------------
// Name:    MaxTimeExceeded
// Purpose: Default Constructor
//------------------------------------------------------------------------------
kernel::MaxTimeExceeded::MaxTimeExceeded(double time_max_)
{
  Time_Max     = time_max_;
}


//------------------------------------------------------------------------------
// Name:    ~MaxTimeExceeded
// Purpose: Destructor
//------------------------------------------------------------------------------
kernel::MaxTimeExceeded::~MaxTimeExceeded()
{
  // This object has nothing to deallocate.
}


//------------------------------------------------------------------------------
// Name:    MaxTimeExceeded
// Purpose: If the current time has exceeded the maximum sim time by more than
//          the time error tolerance, this condition has been met.
//------------------------------------------------------------------------------
bool kernel::MaxTimeExceeded::met(void)
{  
  double time_current = kernel::SimClock::time();
  return ((Time_Max - time_current) < kernel::TIME_ERROR_TOLERANCE);
}