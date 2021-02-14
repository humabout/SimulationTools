// euler.cpp


// Inclusions
#include <map>
#include "euler.h"


//------------------------------------------------------------------------------
// Name:    Euler
// Purpose: Default Constructor
//------------------------------------------------------------------------------
nemesis::Euler::Euler(SimLoop* sim_)
{
  this->Sim = sim_;
}


//------------------------------------------------------------------------------
// Name:    Euler
// Purpose: Constructor
//------------------------------------------------------------------------------
nemesis::Euler::Euler(const Euler& that)
{
  this->Sim    = that.Sim;
  this->States = that.States;
}


//------------------------------------------------------------------------------
// Name:    ~Euler
// Purpose: Destructor
//------------------------------------------------------------------------------
nemesis::Euler::~Euler()
{
  // Does nothing
}


//------------------------------------------------------------------------------
// Name:    Euler
// Purpose: Integrates all registered state variables in the correct order using
//          Euler's method. This is a first-order integration method and may
//          incur non-negligible errors without a sufficiently small time step.
//------------------------------------------------------------------------------
void nemesis::Euler::doUpdateStates(void)
{
  // Ensure that all blocks have been updated prior to integration step
  Sim->updateBlocks();

  // Euler Integration
  double dt = SimClock::tick();
  for (Integrator::state_list::iterator state = States.begin();
    state != States.end();
    ++state)
  {
    (*state).second.x() += dt * (*state).second.dx();
  }
}