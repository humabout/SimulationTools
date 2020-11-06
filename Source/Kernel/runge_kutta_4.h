// runge_kutta_4.h


#ifndef RUNGE_KUTTA_4_H
#define RUNGE_KUTTA_4_H


// Inclusions
#include "config_kernel.h"
#include "integration_method.h"


//----------------------------------------------------------------------------
// Name:    kernel
// Purpose: This namespace holds all parts of the simulation kernel.
//----------------------------------------------------------------------------
namespace kernel
{


  //--------------------------------------------------------------------------
  // Name:    RungeKutta4
  // Purpose: This concretion uses the Runge Kutta 4 integration method to 
  //          propagate the state.
  //--------------------------------------------------------------------------
  class RungeKutta4 : public IntegrationMethod
  {
  public:
    // Members Variables
    static double Time_RK;
    static double Half_Time_Step;

  private:
    // Members Variables
    double x0;
    double k1;
    double k2;
    double k3;
    double k4;
    static unsigned short int RK_Step;

    // Interface Implementation
    void doUpdateState(void) override final;
    void doUpdateClock(void) override final;


  }; // !RungeKutta4


} // !kernel
#endif // !RUNGE_KUTTA_4_H
