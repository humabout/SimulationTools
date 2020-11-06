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
    static double getSampleRate(void);
    static bool   isTimeToSample(void);
    static bool   isTimeToSample(double sample_rate_);

    // Setters
    // TODO: initialize should ideally be available globally, but different 
    // child classes need different things initialized. Static methods cannot 
    // be made virtual and overridden by child classes, so this presents some 
    // problems.
    //
    // THE GOAL IS TO NOT NEED TO CALL A FUNCTION ON A SPECIFIC STATE TO 
    // INITIALIZE ALL OF THE STATES
    //
    // From Stack Overflow:
    // I ran into this problem the other day : I had some classes full of static 
    // methods but I wanted to use inheritanceand virtual methodsand reduce code 
    // repetition.My solution was :
    //
    // Instead of using static methods, use a singleton with virtual methods.
    //
    // In other words, each class should contain a static method that you call
    // to get a pointer to a single, shared instance of the class.You can make
    // the true constructors private or protected so that outside code can't 
    // misuse it by creating additional instances.
    //
    // In practice, using a singleton is a lot like using static methods 
    // except that you can take advantage of inheritanceand virtual methods.
    void initialize(IntegrationMethod::type method);
    void reset(double time_step_, 
                      double sample_rate_ = 0);
    static void setSampleRate(double sample_rate_);

    // Functionality
    static IntegrationMethod* create(void);
    static IntegrationMethod* create(State* state_);
    void updateState(void);
    void updateClock(void);

  protected:
    // Member Variables
    static IntegrationMethod::type Method;
    static double Time_Current;
    static double Time_Next;
    static double Time_Step;
    static double Sample_Rate;
    static bool   Is_Ready;

    State* This_State;

    // Setters
    // TODO: Make these pure eventually
    virtual void doInitialize(void);
    virtual void doReset(double time_step_,
                         double sample_rate_);

    // Functionality
    virtual void doUpdateState(void) = 0;
    virtual void doUpdateClock() = 0;

  }; // !IntegrationMethod


} // !kernel


// Forward Declaration Inclusions
#include "state.h"


#endif // !INTEGRATION_METHOD_H
