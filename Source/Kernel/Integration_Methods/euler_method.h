// euler_method.h


#ifndef EULER_METHOD_H
#define EULER_METHOD_H


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
  // Name:    EulerMethod
  // Purpose: This concretion uses the Euler's integration method to propagate
  //          the state.
  //--------------------------------------------------------------------------
  class EulerMethod : public IntegrationMethod
  {
  public:
    // Constructor
    EulerMethod();
    
    // Destructor
    ~EulerMethod();

  private:
    // Interface Implementation
    void doInitialize() override;
    void doReset(double time_step_) override;
    void doUpdateState(State* state) override final;
    void doUpdateClock(void) override final;


  }; // !EulerMethod


} // !kernel


// Forward Declaration Inclusions
#include "../state.h"


#endif // !EULER_METHOD_H
