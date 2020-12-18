// basic_clock.cpp


// Inclusions
#include "basic_clock.h"


//------------------------------------------------------------------------------
// Name:    BasicClock
// Purpose: Arithmetic Constructor. Creates a basic clock with a maximum tick as
//          as provided in the input argument.
// Inputs:  max_tick [seconds]
//------------------------------------------------------------------------------
core::BasicClock::BasicClock(double max_tick_)
{
  Tick_Max = max_tick_;
  Tick = Tick_Max;  
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