// rk2.cpp


// Inclusions
#include "rk2.h"


//------------------------------------------------------------------------------
// Name:    RK2
// Purpose: Default Constructor
//------------------------------------------------------------------------------
nemesis::RK2::RK2(SimLoop* sim_)
{
  this->Sim = sim_;
}


//------------------------------------------------------------------------------
// Name:    RK2
// Purpose: Constructor
//------------------------------------------------------------------------------
nemesis::RK2::RK2(const RK2& that)
{
  this->Sim = that.Sim;
  this->States = that.States;
}


//------------------------------------------------------------------------------
// Name:    ~Euler
// Purpose: Destructor
//------------------------------------------------------------------------------
nemesis::RK2::~RK2()
{
  // Does nothing
}


//------------------------------------------------------------------------------
// Name:    doUpdateStates
// Purpose: Integrates all registered state variables in the correct order using
//          the RK2 method. This is a second-order integration method.
//------------------------------------------------------------------------------
void nemesis::RK2::doUpdateStates(void)
{
  // Ensure that all blocks have been updated prior to integration step
  Sim->updateBlocks();

  // Storing Initial States
  std::vector<double> x_temp;
  std::vector<double> dx_temp;
  for (Integrator::state_list::iterator state = States.begin();
    state != States.end();
    ++state)
  {
    x_temp.push_back((*state).second.x());
    dx_temp.push_back((*state).second.dx());
  }
  x.push_back(x_temp);   // [0] Original Values
  dx.push_back(dx_temp); // [0] Original Values

  // RK2 Integration
  double dt = SimClock::tick();
  for (Integrator::state_list::iterator state = States.begin();
    state != States.end();
    ++state)
  {
    // Step 1
    

    Sim->updateBlocks();

    // Step 2



  }






  Sim->updateBlocks();
}