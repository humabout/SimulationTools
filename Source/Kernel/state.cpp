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
  *(this->x)             = 0;
  *(this->dx)            = 0;
  this->Owns_Derrivative = true;
  this->Integrator       = kernel::IntegrationMethod::create(this);
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
  this->Integrator       = kernel::IntegrationMethod::create(this);
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
  this->Owns_Derrivative = false;
  this->Integrator       = kernel::IntegrationMethod::create(this);
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