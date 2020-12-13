// simple_synchronous_clock.cpp


// Inclusions
#include "simple_synchronous_clock.h"


//------------------------------------------------------------------------------
// Name:    SimpleSynchronousClock
// Purpose: Default Constructor.
//------------------------------------------------------------------------------
kernel::SimpleSynchronousClock::SimpleSynchronousClock()
{
  // Does Nothing
}


//------------------------------------------------------------------------------
// Name:    ~SimpleSynchronousClock
// Purpose: Destructor. This owns nothing and deletes nothing.
//------------------------------------------------------------------------------
kernel::SimpleSynchronousClock::~SimpleSynchronousClock()
{
  // Does Nothing
}


//------------------------------------------------------------------------------
// Name:    doAdvance
// Purpose: This method implements the advance() method to advance the clock 
//          time by the current time step. It is part of the template pattern.
//------------------------------------------------------------------------------
void kernel::SimpleSynchronousClock::doAdvance(void)
{
  Time_Current += Time_Step;
}


//------------------------------------------------------------------------------
// Name:    doInitialize
// Purpose: This method implements the initialize() method to initialize the 
//          clock's time to zero. It is part of the template pattern.
//------------------------------------------------------------------------------
void kernel::SimpleSynchronousClock::doInitialize(void)
{
  Time_Current = 0;
}


//------------------------------------------------------------------------------
// Name:    doReset
// Purpose: This method implements the reset() method to reset the clock's 
//          maximum time step and update the clock's timestep to that value. It 
//          is part of the template pattern.
//------------------------------------------------------------------------------
void kernel::SimpleSynchronousClock::doReset(double max_time_step_)
{
  Max_Time_Step = max_time_step_;
  Time_Step = Max_Time_Step;
}