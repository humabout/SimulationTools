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
    return State::pointer( new StateEuler<double>(x_, dx_) );
  default:
    return NULL;
  }
}

core::State::pointer core::State::create(math::Vector& x_,
                                         math::Vector& dx_)
{
  switch (core::State::Method)
  {
  case State::type::euler:
    return State::pointer(new StateEuler<math::Vector>(x_, dx_));
  default:
    return NULL;
  }
}

core::State::pointer core::State::create(math::Quaternion& x_,
                                         math::Quaternion& dx_)
{
  switch (core::State::Method)
  {
  case State::type::euler:
    return State::pointer(new StateEuler<math::Quaternion>(x_, dx_));
  default:
    return NULL;
  }
}

core::State::pointer core::State::create(math::Matrix& x_,
                                         math::Matrix& dx_)
{
  switch (core::State::Method)
  {
  case State::type::euler:
    return State::pointer(new StateEuler<math::Matrix>(x_, dx_));
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
bool core::State::isReady(void)
{
  return Is_Ready;
}