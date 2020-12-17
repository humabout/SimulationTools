// state_euler.cpp


// Inclusions
#include <cstddef>
#include "state_euler.h"
#include "../Clocks/sim_clock.h"


//------------------------------------------------------------------------------
// Name:    StateEuler
// Purpose: Constructor Overload.
//------------------------------------------------------------------------------
core::StateEuler::StateEuler(double& x_,
                             double& dx_)
{
  this->x  = &x_;
  this->dx = &dx_;
}


//------------------------------------------------------------------------------
// Name:    StateEuler
// Purpose: Constructor Overload.
//------------------------------------------------------------------------------
core::StateEuler::StateEuler(double&                             x_,
                             const std::shared_ptr<core::State>& dx_)
{
  this->x  = &x_;
  this->dx = dx_->x;
}


//------------------------------------------------------------------------------
// Name:    StateEuler
// Purpose: Constructor Overload.
//------------------------------------------------------------------------------
core::StateEuler::StateEuler(const std::shared_ptr<core::State>& that)
{
  this->x  = that->x;
  this->dx = that->dx;
}


//------------------------------------------------------------------------------
// Name:    ~StateEuler
// Purpose: Destructor. This class owns nothing and deletes nothing.
//------------------------------------------------------------------------------
core::StateEuler::~StateEuler()
{
  // Does Nothing
}


//------------------------------------------------------------------------------
// Name:    propagate
// Purpose: This propagates the state forward one time step using the Euler's
//          method.
//------------------------------------------------------------------------------
void core::StateEuler::propagate(void)
{
  *(this->x) += core::SimClock::tick() * *(this->dx);
  State::Is_Ready = true;
}