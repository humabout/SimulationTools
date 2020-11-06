// runge_kutta_4.cpp


// Inclusions
#include <cmath>
#include "config_kernel.h"
#include "runge_kutta_4.h"


// TODO: Add Description Block
void kernel::RungeKutta4::doUpdateState(void)
{
  double x = X->get();
  double dx = X->getDerrivative();
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


// TODO: Add Description Block
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