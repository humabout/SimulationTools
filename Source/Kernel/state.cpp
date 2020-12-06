// state.cpp


// Inclusions
#include <cstddef>
#include "state.h"
#include "States\state_euler.h"

// Static Variables
double              kernel::State::Time_Current = 0.0;
double              kernel::State::Time_Step = 0.0;
bool                kernel::State::Is_Ready = true;
kernel::State::type kernel::State::Method   = kernel::State::type::euler;


//----------------------------------------------------------------------------
// Name:    State
// Purpose: Default Constructor.
//----------------------------------------------------------------------------
kernel::State::State()
{
  this->x  = NULL;
  this->dx = NULL;
}


//----------------------------------------------------------------------------
// Name:    State
// Purpose: Copy Constructor.
//----------------------------------------------------------------------------
kernel::State::State(const State& that)
{
  this->x  = that.x;
  this->dx = that.dx;
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
  this->x  = &x_;
  this->dx = &dx_;
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
  this->x  = &x_;
  this->dx = dx_.x;
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
  switch (kernel::State::Method)
  {
  case State::type::euler:
    return new StateEuler(x_, dx_);
  default:
    return NULL;
  }
}


//----------------------------------------------------------------------------
// Name:    create (overload)
//----------------------------------------------------------------------------
kernel::State* kernel::State::create(double&        x_,
                                     kernel::State& dx_)
{
  switch (kernel::State::Method)
  {
  case type::euler:
    return new StateEuler(x_, dx_);
  default:
    return NULL;
  }
}


//----------------------------------------------------------------------------
// Name:    create (overload)
//----------------------------------------------------------------------------
kernel::State* kernel::State::create(const kernel::State& state_)
{
  switch (kernel::State::Method)
  {
  case type::euler:
    return new StateEuler(state_);
  default:
    return NULL;
  }
}


//----------------------------------------------------------------------------
// Name:    setMethod
// Purpose: This clears the old integration instance and sets a new method so
//          that the next time an instance is requested, the new method will
//          generated and returned.
//----------------------------------------------------------------------------
void kernel::State::setIntegrationMethod(kernel::State::type method_)
{
  State::Method = method_;
}


//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
// GETTERS
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
double kernel::State::time(void)
{
  return Time_Current;
}

double kernel::State::timestep(void)
{
  return Time_Step;
}

bool kernel::State::isReady(void)
{
  return Is_Ready;
}