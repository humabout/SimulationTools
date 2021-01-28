// sim_clock.h


// Inclusions
#include <memory>
#include "sim_clock.h"
#include "basic_clock.h"


// Static Variable Declarations
double nemesis::SimClock::Time_Current = 0.0;
double nemesis::SimClock::Tick         = 0.0;
double nemesis::SimClock::Tick_Max     = 0.0;


//------------------------------------------------------------------------------
// Name:    ~SimClock
// Purpose: Destructor. This owns nothing and deletes nothing.
//------------------------------------------------------------------------------
nemesis::SimClock::~SimClock()
{
  // Does Nothing
}


//------------------------------------------------------------------------------
// Name:    create
// Purpose: Factory Method. Returns an instance of the correct sim clock type.
//------------------------------------------------------------------------------
std::shared_ptr<nemesis::SimClock> nemesis::SimClock::create(nemesis::SimClock::type type_,
                                                             double                  max_tick_)
{
  switch (type_)
  {
  case nemesis::SimClock::type::basic:
    return std::shared_ptr<nemesis::SimClock>( new BasicClock(max_tick_) );
  default:
    return std::shared_ptr<nemesis::SimClock>( new BasicClock(max_tick_) );
  }
}


//------------------------------------------------------------------------------
// Name:    advance
// Purpose: This method advances the clock time by the current time step. It is 
//          part of the template pattern and forwards the call to doAdvance for 
//          implementation.
//------------------------------------------------------------------------------
void nemesis::SimClock::advance(void)
{
  this->doAdvance();
}


//------------------------------------------------------------------------------
// Name:    initialize
// Purpose: This method initializes the clock. It is part of the template 
//          pattern and forwards the call to doInitialize for implementation.
//------------------------------------------------------------------------------
void nemesis::SimClock::initialize(void)
{
  this->doInitialize();
}


//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
// GETTERS
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
double nemesis::SimClock::time(void)
{
  return SimClock::Time_Current;
}

double nemesis::SimClock::tick(void)
{
  return SimClock::Tick;
}