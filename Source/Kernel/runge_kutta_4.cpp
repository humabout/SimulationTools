// runge_kutta_4.cpp


// Inclusions
#include <cmath>
#include "config_kernel.h"
#include "runge_kutta_4.h"


//----------------------------------------------------------------------------
// Name:    RungeKutta4
// Purpose: Default constructor. Sets the pointer to NULL.
//----------------------------------------------------------------------------
kernel::RungeKutta4::RungeKutta4()
{
  this->x0      = 0;
  this->k1      = 0;
  this->k2      = 0;
  this->k3      = 0;
  this->k4      = 0;
  this->RK_Step = 0;
  This_State = NULL;
}


//----------------------------------------------------------------------------
// Name:    RungeKutta4
// Purpose: Constructor overload. This sets the state to be updated.
//----------------------------------------------------------------------------
kernel::RungeKutta4::RungeKutta4(State* state_)
{
  this->x0 =      0;
  this->k1 =      0;
  this->k2 =      0;
  this->k3 =      0;
  this->k4 =      0;
  this->RK_Step = 0;
  This_State = state_;
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


// TODO: Needs a description
void kernel::RungeKutta4::doInitialize()
{
  IntegrationMethod::Time_Current = 0;
  IntegrationMethod::Is_Ready = true;
  RungeKutta4::RK_Step = 0;
  RungeKutta4::Time_RK = 0;
}


// TODO: Needs a description
void kernel::RungeKutta4::doReset(double time_step_,
                                  double sample_rate_)
{
  IntegrationMethod::Time_Step = time_step_;
  IntegrationMethod::Sample_Rate = sample_rate_;
  RungeKutta4::Half_Time_Step = 0.5 * Time_Step;
}


//----------------------------------------------------------------------------
// Name:    doUpdateState
// Purpose: This propagates the state forward one time step using the Runge
//          Kutta 4 method.
//----------------------------------------------------------------------------
void kernel::RungeKutta4::doUpdateState(void)
{
  double x = This_State->get();
  double dx = This_State->getDerrivative();
  switch (RK_Step)
  {
  case 0:
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
  // Update the RK step based on where in teh rk4 loop the algorithm currently is
  switch (RK_Step)
  {
  case 0:
  case 2:
    Time_RK += Half_Time_Step;
    break;
  default:
    break;
  }
  RK_Step++;
  RK_Step = RK_Step % 4;

  // Updates whether or not it may be time to sample
  bool is_first_iteration = (RK_Step == 0);
  Is_Ready = (is_first_iteration) && (abs(Time_Next - Time_Current) < kernel::EPS);

  // Updates the next current time and next rk4 time to update, provided something doesn't drive that to occur sooner
  if (is_first_iteration)
  {
    Time_Current = Time_RK;
    Time_Next += Time_Step;
  }
}