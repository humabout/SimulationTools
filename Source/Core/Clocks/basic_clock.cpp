// basic_clock.cpp


// Inclusions
#include "basic_clock.h"


//------------------------------------------------------------------------------
// Name:    BasicClock
// Purpose: Default Constructor.
//------------------------------------------------------------------------------
core::BasicClock::BasicClock()
{
  // Does Nothing
}


//------------------------------------------------------------------------------
// Name:    ~BasicClock
// Purpose: Destructor. This owns nothing and deletes nothing.
//------------------------------------------------------------------------------
core::BasicClock::~BasicClock()
{
  // Does Nothing
}


//------------------------------------------------------------------------------
// Name:    doAdvance
// Purpose: This method implements the advance() method to advance the clock 
//          time by the current time step. It is part of the template pattern.
//------------------------------------------------------------------------------
void core::BasicClock::doAdvance(void)
{
  Time_Current += Tick;
}


//------------------------------------------------------------------------------
// Name:    doInitialize
// Purpose: This method implements the initialize() method to initialize the 
//          clock's time to zero. It is part of the template pattern.
//------------------------------------------------------------------------------
void core::BasicClock::doInitialize(void)
{
  Time_Current = 0;
}


//------------------------------------------------------------------------------
// Name:    doSetMaxTick
// Purpose: This method implements the setMaxTick() method to reset the clock's 
//          maximum time step and update the clock's timestep to that value. It 
//          is part of the template pattern.
//------------------------------------------------------------------------------
void core::BasicClock::doSetMaxTick(double max_time_step_)
{
  Tick_Max = max_time_step_;
  Tick = Tick_Max;
}