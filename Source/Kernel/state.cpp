// state.cpp


// Inclusions
//#include <cmath>
//#include <cstdlib>
//#include <ctime>
#include "config_kernel.h"
#include "state.h"


//----------------------------------------------------------------------------
// Name:    State
// Purpose: Default Constructor.
//----------------------------------------------------------------------------
kernel::State::State()
{
  *(this->x)             = 0;
  *(this->dx)            = 0;
  this->Owns_Derrivative = true;
  this->Integrator       = kernel::IntegrationMethod::create();
}


//----------------------------------------------------------------------------
// Name:    State
// Purpose: Copy Constructor.
//----------------------------------------------------------------------------
kernel::State::State(const State& that)
{
  *this = that;
}


//----------------------------------------------------------------------------
// Name:    State
// Purpose: Initializes the state variables to those provided. Because the 
//          derrivative is passed in as a reference, this state does not own 
//          it.
//----------------------------------------------------------------------------
kernel::State::State(double& x_, 
                     double& dx_)
{
  this->x                = &x_;
  this->dx               = &dx_;
  this->Owns_Derrivative = true;
  this->Integrator       = kernel::IntegrationMethod::create();
}


//----------------------------------------------------------------------------
// Name:    State
// Purpose: Initializes the state variables to those provided. Because the 
//          derrivative is the value of another state, this state does not own
//          its derrivative.
//----------------------------------------------------------------------------
kernel::State::State(double& x_, 
                     State&  dx_)
{
  this->x                = &x_;
  this->dx               = &(dx_.getReference());
  this->Owns_Derrivative = false;
  this->Integrator       = kernel::IntegrationMethod::create();
}


//----------------------------------------------------------------------------
// Name:    ~State
// Purpose: This object owns its own value and is responsible for deleting it.
//          It may or may not own its own derrivative, but if it does, it also
//          deallocates that memory.
//----------------------------------------------------------------------------
kernel::State::~State()
{
  if (x != NULL)
  {
    delete x;
  }
  if (dx != NULL && Owns_Derrivative)
  {
    delete dx;
  }
}


//----------------------------------------------------------------------------
// Name:    create
// Purpose: This factory method creates and returns a new state with the 
//          provided state and state derrivative.
// Inputs:  The state
//          The state derrivative
//----------------------------------------------------------------------------
kernel::State* kernel::State::create(double& x_,
  double& dx_)
{
  return new State(x_, dx_);
}


//----------------------------------------------------------------------------
// Name:    create (overload)
//----------------------------------------------------------------------------
kernel::State* kernel::State::create(double& x_,
  kernel::State& dx_)
{
  return new State(x_, dx_);
}


//----------------------------------------------------------------------------
// Name:    create (overload)
//----------------------------------------------------------------------------
kernel::State* kernel::State::create(const kernel::State& state_)
{
  return new State(state_);
}


//----------------------------------------------------------------------------
// Name:    initialize
// Purpose: This method initializes state to a given initial condition.
// Inputs:  The state's initial condition
//----------------------------------------------------------------------------
void kernel::State::initialize(double x_)
{
  *x = x_;
}


//----------------------------------------------------------------------------
// Name:    isNewSample
// Purpose: This method checks if there is a new sample available. It forwards
//          the call to the integrator, which handles tracking time as part of
//          its operation.
// TODO:    Consider breaking timekeeping into its own object. This will 
//          ensure that everything stays synced to whatever it should and can 
//          be expanded to handle asynchronous events.
//----------------------------------------------------------------------------
bool kernel::State::isNewSample(void)
{
  return Integrator->isTimeToSample();
}


//----------------------------------------------------------------------------
// Name:    isNewSample (overload)
//----------------------------------------------------------------------------
bool kernel::State::isNewSample(double sample_rate_)
{
  return Integrator->isTimeToSample(sample_rate_);
}


//----------------------------------------------------------------------------
// Name:    operator=
// Purpose: Assignment Operator.
//----------------------------------------------------------------------------
void kernel::State::operator= (const State& that)
{
  this->x = that.x;
  this->dx = that.dx;
  this->Owns_Derrivative = that.Owns_Derrivative;
  this->Integrator = that.Integrator;
}


//----------------------------------------------------------------------------
// Name:    updateClock
// Purpose: This method updates the clock. 
// TODO:    Evaluate if this is even needed here. I think it is an internal
//          thing for the integration method.
//----------------------------------------------------------------------------
void kernel::State::updateClock(void)
{
  Integrator->updateClock();
}


//----------------------------------------------------------------------------
// Name:    updateState
// Purpose: This method propagates the state forward one time step. It is part
//          of a strategy pattern and forwards the call to the Integrator to
//          execute based on whatever type of IntegrationMethod is being used.
//----------------------------------------------------------------------------
void kernel::State::updateState(void)
{
  Integrator->updateState();
}


//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
// GETTERS
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
double kernel::State::get(void) const
{
  return *x;
}

double& kernel::State::getReference(void) const
{
  return (*x);
}