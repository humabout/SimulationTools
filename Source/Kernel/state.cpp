// state.cpp


// Inclusions
#include <cstddef>
#include "state.h"


//----------------------------------------------------------------------------
// Name:    State
// Purpose: Default Constructor.
//----------------------------------------------------------------------------
kernel::State::State()
{
  *(this->x)             = NULL;
  *(this->dx)            = NULL;
  this->Integrator       = kernel::IntegrationMethod::create();
}


//----------------------------------------------------------------------------
// Name:    State
// Purpose: Copy Constructor.
//----------------------------------------------------------------------------
kernel::State::State(const State& that)
{
  this->x = that.x;
  this->dx = that.dx;
  this->Integrator = that.Integrator;
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
  this->dx               = dx_.x;
  this->Integrator       = kernel::IntegrationMethod::create();
}


//----------------------------------------------------------------------------
// Name:    ~State
// Purpose: This object does not own its own state or state derrivative. These
//          are merely linked to via reference for the sake of propagating 
//          them. The values' owners are responsible for deleting them, if
//          they live on heap. As a result, this object owns nothing and does
//          not need to delete anything.
//----------------------------------------------------------------------------
kernel::State::~State()
{
  // Does nothing.
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
// Name:    operator=
// Purpose: Assignment Operator.
//----------------------------------------------------------------------------
kernel::State& kernel::State::operator= (const State& that)
{
  return *new State(that);
}


//----------------------------------------------------------------------------
// Name:    propagate
// Purpose: This method propagates the state forward one time step. It is part
//          of a strategy pattern and forwards the call to the Integrator to
//          execute based on whatever type of IntegrationMethod is being used.
//----------------------------------------------------------------------------
void kernel::State::propagate(void)
{
  Integrator->updateState(this);
}


//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
// GETTERS
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
double kernel::State::get(void) const
{
  return *x;
}