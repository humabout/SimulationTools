// runge_kutta_4.h


#ifndef RUNGE_KUTTA_4_H
#define RUNGE_KUTTA_4_H


// Inclusions
#include "integration_method.h"


// Forward Declarations
namespace kernel
{
  class State;
}


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
    // Constructors
    RungeKutta4();

    // Destructor
    ~RungeKutta4();

  private:
    // Members Variables
    double x0;
    double k1;
    double k2;
    double k3;
    double k4;

    static double             Time_RK;
    static double             Half_Time_Step;
    static unsigned short int RK_Step;

    void doInitialize() override;
    void doReset(double time_step_) override;

    // Interface Implementation
    void doUpdateState(State* state) override final;
    void doUpdateClock(void) override final;


  }; // !RungeKutta4


} // !kernel


 // Forward Declaration Inclusions
#include "state.h"


#endif // !RUNGE_KUTTA_4_H
