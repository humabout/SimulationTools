// sim_clock.h


// Inclusions
#include <memory>
#include "sim_clock.h"
#include "basic_clock.h"


// Static Variable Declarations
double core::SimClock::Time_Current;
double core::SimClock::Tick;
double core::SimClock::Tick_Max;


//------------------------------------------------------------------------------
// Name:    SimClock
// Purpose: Default Constructor.
//------------------------------------------------------------------------------
core::SimClock::SimClock()
{
  Time_Current = 0;
  Tick = 0;
  Tick_Max = 0;
}


//------------------------------------------------------------------------------
// Name:    ~SimClock
// Purpose: Destructor. This owns nothing and deletes nothing.
//------------------------------------------------------------------------------
core::SimClock::~SimClock()
{
  // Does Nothing
}


//------------------------------------------------------------------------------
// Name:    create
// Purpose: Factory Method. Returns an instance of the correct sim clock type.
//------------------------------------------------------------------------------
std::shared_ptr<core::SimClock> core::SimClock::create(core::SimClock::type type_,
                                                       double               max_tick_)
{
  switch (type_)
  {
  case core::SimClock::type::basic:
    return std::shared_ptr<core::SimClock>( new BasicClock(max_tick_) );
  default:
    return std::shared_ptr<core::SimClock>( new BasicClock(max_tick_) );
  }
}


//------------------------------------------------------------------------------
// Name:    advance
// Purpose: This method advances the clock time by the current time step. It is 
//          part of the template pattern and forwards the call to doAdvance for 
//          implementation.
//------------------------------------------------------------------------------
void core::SimClock::advance(void)
{
  this->doAdvance();
}


//------------------------------------------------------------------------------
// Name:    initialize
// Purpose: This method initializes the clock. It is part of the template 
//          pattern and forwards the call to doInitialize for implementation.
//------------------------------------------------------------------------------
void core::SimClock::initialize(void)
{
  this->doInitialize();
}


//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
// GETTERS
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
double core::SimClock::time(void)
{
  return SimClock::Time_Current;
}

double core::SimClock::tick(void)
{
  return SimClock::Tick;
}