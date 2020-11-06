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
    ~IntegrationMethod();

    // Getters
    static double getTime(void);
    static double getTimeStep(void);
    static bool   isTimeToReport(void);

    // Setters
    static void initialize(void);
    static void initialize(IntegrationMethod::type method); // Call doInitialize() and set Method
    void registerState(State* state);

    // Functionality
    static IntegrationMethod* create(void);
    void propagate(void);

  protected:
    // Member Variables
    static IntegrationMethod::type Method;
    static double Time;
    static double Time_Step;
    static double Write_Rate;
    static bool   Is_Time_To_Report;

    // Setters
    virtual void doInitialize(void);
    virtual void doRegisterState(State* state);

    // Functionality
    virtual void doPropagate(void) = 0;
  }; // !IntegrationMethod


} // !kernel


// Forward Declaration Inclusions
#include "state.h"


#endif // !INTEGRATION_METHOD_H
