// basic_clock.cpp


// Inclusions
#include "basic_clock.h"


//------------------------------------------------------------------------------
// Name:    BasicClock
// Purpose: Arithmetic Constructor. Creates a basic clock with a maximum tick as
//          as provided in the input argument.
// Inputs:  max_tick [seconds]
//------------------------------------------------------------------------------
nemesis::BasicClock::BasicClock(double max_tick_)
{
  Time_Current = 0;
  Tick_Max = max_tick_;
  Tick = Tick_Max;  
}


//------------------------------------------------------------------------------
// Name:    ~BasicClock
// Purpose: Destructor. This owns nothing and deletes nothing.
//------------------------------------------------------------------------------
nemesis::BasicClock::~BasicClock()
{
  // Does Nothing
}


//------------------------------------------------------------------------------
// Name:    doAdvance
// Purpose: This method implements the advance() method to advance the clock 
//          time by the current time step. It is part of the template pattern.
//------------------------------------------------------------------------------
void nemesis::BasicClock::doAdvance(void)
{
  Time_Current += Tick;
}


//------------------------------------------------------------------------------
// Name:    doInitialize
// Purpose: This method implements the initialize() method to initialize the 
//          clock's time to zero. It is part of the template pattern.
//------------------------------------------------------------------------------
void nemesis::BasicClock::doInitialize(void)
{
  Time_Current = 0;
}