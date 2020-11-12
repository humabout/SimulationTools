// runge_kutta_4.cpp


// Inclusions
#include <cmath>
#include "integration_method.h"
#include "runge_kutta_4.h"
#include "..\state.h"


// Static Variables
double             kernel::RungeKutta4::Time_RK;
double             kernel::RungeKutta4::Half_Time_Step;
unsigned short int kernel::RungeKutta4::RK_Step = 0;


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
  kernel::IntegrationMethod::Time_Current = 0;
  kernel::IntegrationMethod::Is_Ready = true;
  kernel::RungeKutta4::RK_Step = 0;
  kernel::RungeKutta4::Time_RK = 0;
}


//----------------------------------------------------------------------------
// Name:    doReset
// Purpose: This method implements the resetting of the time step, and for the
//          purposes of RK4, the half time step, to the provided value.
//----------------------------------------------------------------------------
void kernel::RungeKutta4::doReset(double time_step_)
{
  kernel::IntegrationMethod::Time_Step = time_step_;
  kernel::RungeKutta4::Half_Time_Step = 0.5 * Time_Step;
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
  switch (kernel::RungeKutta4::RK_Step)
  {
  case 0:
    kernel::IntegrationMethod::Is_Ready = false;
    x0 = x;
    k1 = dx;
    x = x0 + kernel::RungeKutta4::Half_Time_Step * k1;
    break;
  case 1:
    k2 = dx;
    x = x0 + kernel::RungeKutta4::Half_Time_Step * k2;
    break;
  case 2:
    k3 = dx;
    x = x0 + kernel::IntegrationMethod::Time_Step * k3;
    break;
  case 3:
    k4 = dx;
    x = x0 + kernel::IntegrationMethod::Time_Step * (k1 + 2 * k2 + 2 * k3 + k4) / 6;
    *(state_->x) = x;
    kernel::IntegrationMethod::Is_Ready = true;
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
  switch (kernel::RungeKutta4::RK_Step)
  {
  case 0:
    kernel::IntegrationMethod::Time_Current = kernel::RungeKutta4::Time_RK;
    break;
  case 1:
    break;
  case 2:
    kernel::RungeKutta4::Time_RK += kernel::RungeKutta4::Half_Time_Step;
    break;
  default:
    break;
  }
  kernel::RungeKutta4::RK_Step++;
  kernel::RungeKutta4::RK_Step = kernel::RungeKutta4::RK_Step % 4;
}