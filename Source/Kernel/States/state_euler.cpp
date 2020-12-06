// state_euler.cpp


// Inclusions
#include <cstddef>
#include "state_euler.h"


//------------------------------------------------------------------------------
// Name:    StateEuler
// Purpose: Default Constructor.
//------------------------------------------------------------------------------
kernel::StateEuler::StateEuler()
{
  this->x  = NULL;
  this->dx = NULL;
}


//------------------------------------------------------------------------------
// Name:    StateEuler
// Purpose: Constructor Overload.
//------------------------------------------------------------------------------
kernel::StateEuler::StateEuler(double& x_,
                               double& dx_)
{
  this->x  = &x_;
  this->dx = &dx_;
}


//------------------------------------------------------------------------------
// Name:    StateEuler
// Purpose: Constructor Overload.
//------------------------------------------------------------------------------
kernel::StateEuler::StateEuler(double&        x_,
                               kernel::State& dx_)
{
  this->x  = &x_;
  this->dx = dx_.x;
}


//------------------------------------------------------------------------------
// Name:    StateEuler
// Purpose: Copy Constructor.
//------------------------------------------------------------------------------
kernel::StateEuler::StateEuler(const kernel::State& that)
{
  this->x  = that.x;
  this->dx = that.dx;
}


//------------------------------------------------------------------------------
// Name:    ~StateEuler
// Purpose: Destructor. This class owns nothing and deletes nothing.
//------------------------------------------------------------------------------
kernel::StateEuler::~StateEuler()
{
  // Does Nothing
}


//------------------------------------------------------------------------------
// Name:    initialize
// Purpose: This method implements the initialization of static variables for
//          the sake of syncronizing the integration of all states.
//------------------------------------------------------------------------------
void kernel::StateEuler::initialize(void)
{
  State::Time_Current = 0;
  State::Is_Ready = true;
}


//------------------------------------------------------------------------------
// Name:    reset
// Purpose: This method implements the resetting of the time step to the 
//          provided value.
//------------------------------------------------------------------------------
void kernel::StateEuler::reset(double time_step_)
{
  State::Time_Step = time_step_;
}


//------------------------------------------------------------------------------
// Name:    updateState
// Purpose: This propagates the state forward one time step using the Euler's
//          method.
//------------------------------------------------------------------------------
void kernel::StateEuler::updateState(void)
{
  (*this->x) += State::Time_Step * (*this->dx);
  State::Is_Ready = true;
}


//------------------------------------------------------------------------------
// Name:    updateClock
// Purpose: This implements clock updates for use with Euler's method.
//------------------------------------------------------------------------------
void kernel::StateEuler::updateClock(void)
{
  State::Time_Current += State::Time_Step;
}