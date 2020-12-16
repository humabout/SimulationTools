// state.cpp


// Inclusions
#include <cstddef>
#include <memory>
#include "state.h"
#include "States\state_euler.h"

// Static Variables
bool              core::State::Is_Ready = true;
core::State::type core::State::Method   = core::State::type::euler;


//----------------------------------------------------------------------------
// Name:    State
// Purpose: Default Constructor.
//----------------------------------------------------------------------------
core::State::State()
{
  this->x  = NULL;
  this->dx = NULL;
}


//----------------------------------------------------------------------------
// Name:    State
// Purpose: Copy Constructor.
//----------------------------------------------------------------------------
core::State::State(const State& that)
{
  this->x  = that.x;
  this->dx = that.dx;
}


//----------------------------------------------------------------------------
// Name:    State
// Purpose: Makes State from a shared_ptr that points at a State.
//----------------------------------------------------------------------------
core::State::State(const State::pointer& that)
{
  this->x  = that->x;
  this->dx = that->dx;
}


//----------------------------------------------------------------------------
// Name:    State
// Purpose: Initializes the state variables to those provided. Because the 
//          derrivative is passed in as a reference, this state does not own 
//          it.
//----------------------------------------------------------------------------
core::State::State(double& x_,
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
core::State::State(double&               x_,
                     const State::pointer& dx_)
{
  this->x  = &x_;
  this->dx = dx_->x;
}


//----------------------------------------------------------------------------
// Name:    ~State
// Purpose: This object does not own its own state or state derrivative. These
//          are merely linked to via reference for the sake of propagating 
//          them. The values' owners are responsible for deleting them, if
//          they live on heap. As a result, this object owns nothing and does
//          not need to delete anything.
//----------------------------------------------------------------------------
core::State::~State()
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
core::State::pointer core::State::create(double& x_,
                                                     double& dx_)
{
  switch (core::State::Method)
  {
  case State::type::euler:
    return State::pointer( new StateEuler(x_, dx_) );
  default:
    return NULL;
  }
}


//----------------------------------------------------------------------------
// Name:    create (overload)
//----------------------------------------------------------------------------
core::State::pointer core::State::create(double&               x_,
                                             const State::pointer& dx_)
{
  switch (core::State::Method)
  {
  case type::euler:
    return State::pointer(new StateEuler(x_, dx_));
  default:
    return NULL;
  }
}


//----------------------------------------------------------------------------
// Name:    create (overload)
//----------------------------------------------------------------------------
core::State::pointer core::State::create(const State::pointer& state_)
{
  switch (core::State::Method)
  {
  case type::euler:
    return State::pointer(new StateEuler(state_));
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
void core::State::setIntegrationMethod(core::State::type method_)
{
  State::Method = method_;
}


//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
// GETTERS
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
double* core::State::dx_(void) const
{
  return dx;
}
bool core::State::isReady(void)
{
  return Is_Ready;
}
double* core::State::x_(void) const
{
  return x;
}