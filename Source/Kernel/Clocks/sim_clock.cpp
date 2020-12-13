// sim_clock.h


// Inclusions
#include <memory>
#include "sim_clock.h"
#include "simple_synchronous_clock.h"


// Static Variable Declarations
double kernel::SimClock::Time_Current;
double kernel::SimClock::Time_Step;
double kernel::SimClock::Max_Time_Step;


//------------------------------------------------------------------------------
// Name:    SimClock
// Purpose: Default Constructor.
//------------------------------------------------------------------------------
kernel::SimClock::SimClock()
{
  Time_Current = 0;
  Time_Step = 0;
  Max_Time_Step = 0;
}


//------------------------------------------------------------------------------
// Name:    ~SimClock
// Purpose: Destructor. This owns nothing and deletes nothing.
//------------------------------------------------------------------------------
kernel::SimClock::~SimClock()
{
  // Does Nothing
}


//------------------------------------------------------------------------------
// Name:    create
// Purpose: Factory Method. Returns an instance of the correct sim clock type.
//------------------------------------------------------------------------------
std::shared_ptr<kernel::SimClock> kernel::SimClock::create(kernel::SimClock::type type_)
{
  switch (type_)
  {
  case kernel::SimClock::type::simple_synchronous:
    return std::shared_ptr<kernel::SimClock>(new SimpleSynchronousClock);
  default:
    return std::shared_ptr<kernel::SimClock>(new SimpleSynchronousClock);
  }
}


//------------------------------------------------------------------------------
// Name:    advance
// Purpose: This method advances the clock time by the current time step. It is 
//          part of the template pattern and forwards the call to doAdvance for 
//          implementation.
//------------------------------------------------------------------------------
void kernel::SimClock::advance(void)
{
  this->doAdvance();
}


//------------------------------------------------------------------------------
// Name:    initialize
// Purpose: This method initializes the clock. It is part of the template 
//          pattern and forwards the call to doInitialize for implementation.
//------------------------------------------------------------------------------
void kernel::SimClock::initialize(void)
{
  this->doInitialize();
}


//------------------------------------------------------------------------------
// Name:    reset
// Purpose: This method resets the clock's time step. It is part of the template
//          pattern and forwards the call to doReset for implementation.
//------------------------------------------------------------------------------
void kernel::SimClock::reset(double max_time_step_)
{
  this->doReset(max_time_step_);
}



//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
// GETTERS
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
double kernel::SimClock::time(void)
{
  return SimClock::Time_Current;
}

double kernel::SimClock::timestep(void)
{
  return SimClock::Time_Step;
}