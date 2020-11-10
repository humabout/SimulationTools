// runge_kutta_4.cpp


// Inclusions
#include <cmath>
#include "integration_method.h"
#include "runge_kutta_4.h"
#include "..\state.h"


//----------------------------------------------------------------------------
// Name:    RungeKutta4
// Purpose: Default constructor.
//----------------------------------------------------------------------------
kernel::RungeKutta4::RungeKutta4()
{
  this->x0      = 0;
  this->k1      = 0;
  this->k2      = 0;
  this->k3      = 0;
  this->k4      = 0;
  this->RK_Step = 0;
}


//----------------------------------------------------------------------------
// Name:    RungeKutta4
// Purpose: This propagates the state forward one time step using the Runge
//          Kutta 4 method.
//----------------------------------------------------------------------------
kernel::RungeKutta4::~RungeKutta4()
{
  // Deallocates nothing.
}


//----------------------------------------------------------------------------
// Name:    doInitialize
// Purpose: This method implements the initialization of static variables for
//          the sake of syncronizing the integration of all states.
//----------------------------------------------------------------------------
void kernel::RungeKutta4::doInitialize()
{
  Time_Current = 0;
  Is_Ready = true;
  RK_Step = 0;
  Time_RK = 0;
}


//----------------------------------------------------------------------------
// Name:    doReset
// Purpose: This method implements the resetting of the time step, and for the
//          purposes of RK4, the half time step, to the provided value.
//----------------------------------------------------------------------------
void kernel::RungeKutta4::doReset(double time_step_)
{
  Time_Step = time_step_;
  Half_Time_Step = 0.5 * Time_Step;
}


//----------------------------------------------------------------------------
// Name:    doUpdateState
// Purpose: This propagates the state forward one time step using the Runge
//          Kutta 4 method.
//----------------------------------------------------------------------------
void kernel::RungeKutta4::doUpdateState(State* state_)
{
  double x = *(state_->x);
  double dx = *(state_->dx);
  switch (RK_Step)
  {
  case 0:
    Is_Ready = false;
    x0 = x;
    k1 = dx;
    x = x0 + Half_Time_Step * k1;
    break;
  case 1:
    k2 = dx;
    x = x0 + Half_Time_Step * k2;
    break;
  case 2:
    k3 = dx;
    x = x0 + Time_Step * k3;
    break;
  case 3:
    k4 = dx;
    x = x0 + Time_Step * (k1 + 2 * k2 + 2 * k3 + k4) / 6;
    *(state_->x) = x;
    Is_Ready = true;
    break;
  default:
    break;
  }
}


//----------------------------------------------------------------------------
// Name:    doUpdateClock
// Purpose: This implements clock updates for use with the runge kutta method.
//----------------------------------------------------------------------------
void kernel::RungeKutta4::doUpdateClock(void)
{
  // Update the RK step based on where in the rk4 loop the algorithm currently 
  // is.
  switch (RK_Step)
  {
  case 0:
    Time_Current = Time_RK;
    break;
  case 1:
    break;
  case 2:
    Time_RK += Half_Time_Step;
    break;
  default:
    break;
  }
  RK_Step++;
  RK_Step = RK_Step % 4;
}