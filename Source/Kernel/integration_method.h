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
    static double time(void);
    static double timestep(void);
    static bool   isReady(void);

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
    //
    // Notes: If we use dependency injection to have each state feed itself as
    // an argument to the propagate method, then we might only need one copy 
    // of the integrator, making it singleton-like and allowing the above 
    // advice to be used. It also let's only instantiate a single copy of 
    // this, which will save memory and runtime in an area where it may speed 
    // things up. If nothing else, it gives flexibility at a time in 
    // development where that is crucial for iterating. Once everything 
    // stabilitizes, we can revisit this idea and see if there are performance
    // gains to be had by giving each state a dedicated integrator object or 
    // even making integration part of the state itself.
    void initialize(IntegrationMethod::type method);
    void reset(double time_step_);

    // Functionality
    static IntegrationMethod* create(void);
    static IntegrationMethod* create(State* state_);
    void updateState(State* state);
    void updateClock(void);

  protected:
    // Member Variables
    static IntegrationMethod::type Method;
    static double Time_Current;
    static double Time_Step;
    static bool   Is_Ready;

    // Setters
    // TODO: Make these pure eventually
    virtual void doInitialize(void) = 0;
    virtual void doReset(double time_step_) = 0;

    // Functionality
    virtual void doUpdateState(State* state) = 0;
    virtual void doUpdateClock(void) = 0;

  }; // !IntegrationMethod


} // !kernel


// Forward Declaration Inclusions
#include "state.h"


#endif // !INTEGRATION_METHOD_H
