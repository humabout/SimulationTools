// integration_method.h


#ifndef INTEGRATION_METHOD_H
#define INTEGRATION_METHOD_H


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
  // Name:    IntegrationMethod
  // Purpose: This abstract class declares the interface for interation method
  //          classes. These exist to propagate states as part of a strategy
  //          pattern. It uses a template pattern to enforce the interface.
  //--------------------------------------------------------------------------
  class IntegrationMethod
  {
  public:
    // Enum
    enum class type
    {
      Euler = 1,
      RK2 = 2,
      Velocity_Verlet = 3,
      RK4 = 4
    };

    // Constructor
    IntegrationMethod();

    // Destructor
    ~IntegrationMethod() {}

    // Getters
    static double time(void);
    static double timestep(void);
    static bool   isReady(void);

    // Setters
    static void setMethod(IntegrationMethod::type method_);
    void initialize();
    void reset(double time_step_);

    // Functionality
    static IntegrationMethod* create(void);
    void updateState(State* state_);
    void updateClock(void);

  protected:
    // Member Variables
    static double                  Time_Current;
    static double                  Time_Step;
    static bool                    Is_Ready;
    static IntegrationMethod::type Method;

    // Setters
    virtual void doInitialize(void) = 0;
    virtual void doReset(double time_step_) = 0;

    // Functionality
    virtual void doUpdateState(State* state) = 0;
    virtual void doUpdateClock(void) = 0;

  }; // !IntegrationMethod


} // !kernel


// Forward Declaration Inclusions
#include "..\state.h"


#endif // !INTEGRATION_METHOD_H
