// integration_method.cpp


// Inclusions
#include <cmath>
#include "integration_method.h"
#include "euler_method.h"
#include "runge_kutta_4.h"



// Static Variables
double                          kernel::IntegrationMethod::Time_Current;
double                          kernel::IntegrationMethod::Time_Step;
bool                            kernel::IntegrationMethod::Is_Ready = true;
kernel::IntegrationMethod::type kernel::IntegrationMethod::Method = kernel::IntegrationMethod::type::RK4;


//----------------------------------------------------------------------------
// Name:    instance
// Purpose: This getter returns a pointer to the only instance of this class.
//----------------------------------------------------------------------------
kernel::IntegrationMethod::IntegrationMethod()
{
  Time_Current = 0;
  Time_Step    = 0;
  Is_Ready     = true;
}


//----------------------------------------------------------------------------
// Name:    create
// Purpose: This factory creates and returns an instance of the integration 
//          method currently set in Method.
//----------------------------------------------------------------------------
kernel::IntegrationMethod* kernel::IntegrationMethod::create(void)
{
  switch (kernel::IntegrationMethod::Method)
  {
  case type::Euler:
    return new EulerMethod();
  default:
    return NULL;
  }
}


//----------------------------------------------------------------------------
// Name:    initialize
// Purpose: This implements the Initialize() interface by setting all static
//          variables to zero.
//----------------------------------------------------------------------------
void kernel::IntegrationMethod::initialize()
{
  doInitialize();
}


//----------------------------------------------------------------------------
// Name:    reset
// Purpose: This resets the timestep, and if provided, the sample rate for the 
//          simulation, and recalculates the next time to integrate.
//----------------------------------------------------------------------------
void kernel::IntegrationMethod::reset(double time_step_)
{
  doReset(time_step_);
}


//----------------------------------------------------------------------------
// Name:    setMethod
// Purpose: This clears the old integration instance and sets a new method so
//          that the next time an instance is requested, the new method will
//          generated and returned.
//----------------------------------------------------------------------------
void kernel::IntegrationMethod::setMethod(kernel::IntegrationMethod::type method_)
{
  IntegrationMethod::Method = method_;
}


//----------------------------------------------------------------------------
// Name:    updateClock
// Purpose: This updates the shared clock used by the integrator to execute 
//          its algorithm. It defers actual implementation as part of the 
//          template pattern so that specific integration methods can set
//          exactly how to update the clock.
//----------------------------------------------------------------------------
void kernel::IntegrationMethod::updateClock(void)
{
  doUpdateClock();
}


//----------------------------------------------------------------------------
// Name:    updateState
// Purpose: This updates the executes the integration algorithm that updates 
//          the state registered with this instance. It defers actual 
//          implementation as part of the template pattern so that specific 
//          integration methods can set exactly how to update the state.
//----------------------------------------------------------------------------
void kernel::IntegrationMethod::updateState(State* state_)
{
  doUpdateState(state_);
}


//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
// GETTERS
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
double kernel::IntegrationMethod::time(void)
{
  return Time_Current;
}

double kernel::IntegrationMethod::timestep(void)
{
  return Time_Step;
}

bool kernel::IntegrationMethod::isReady(void)
{
  return Is_Ready;
}