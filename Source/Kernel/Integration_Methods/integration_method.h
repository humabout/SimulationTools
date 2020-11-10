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
    // Destructor-like 
    static void resetInstance(void);

    // Getters
    double time(void);
    double timestep(void);
    bool   isReady(void);

    // Setters
    void setMethod(IntegrationMethod::type method_);
    void initialize();
    void reset(double time_step_);

    // Functionality
    static IntegrationMethod* instance(void);
    void updateState(State* state_);
    void updateClock(void);

  protected:
    // Member Variables
    // TODO:  Do these need to be static anymore? I don't think so...
    double                         Time_Current;
    double                         Time_Step;
    bool                           Is_Ready;
    static IntegrationMethod::type Method;

    // Singleton Pattern
    static IntegrationMethod* Instance;

    // Enforcing Singleton Pattern
    IntegrationMethod();
    ~IntegrationMethod() {}

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
