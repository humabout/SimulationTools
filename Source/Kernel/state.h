// state.h


#ifndef STATE_H
#define STATE_H


// Forward Declarations
namespace kernel
{
  class StateEuler;
}


//----------------------------------------------------------------------------
// Name:    kernel
// Purpose: This namespace holds all parts of the simulation kernel.
//----------------------------------------------------------------------------
namespace kernel
{


  //--------------------------------------------------------------------------
  // Name:    State
  // Purpose: This class provides the interface and basic necessities for 
  //          propagating state variables. Each child class implements a 
  //          specific integration method.
  //--------------------------------------------------------------------------
  class State
  {
  public:
    // Enum
    enum class type
    {
      euler = 1,
      rk2   = 2,
      rk4   = 3
    };

    // Constructors
    State();
    State(double& x_, 
          double& dx_);
    State(double& x_, 
          State& dx_);
    State(const State& that);

    // Destructor
    virtual ~State();

    // Getters
    static double time(void);
    static double timestep(void);
    static bool   isReady(void);

    // Setters
    static  void setMethod(State::type method_);

    // Factory
    static State* create(double& x_, double& dx_);
    static State* create(double& x_, State& dx_);
    static State* create(const State& state_);

    // Functionality
    virtual void initialize() = 0;
    virtual void reset(double time_step_) = 0;
    virtual void updateState(void) = 0;
    virtual void updateClock(void) = 0;

  protected:
    // Member Variables
    static double Time_Current;
    static double Time_Step;
    static bool   Is_Ready;
    static type   Method;

    // State Variables
    double* x;
    double* dx;

    // Friend Child Classes
    friend StateEuler;


  }; // !StateInterface


} // !kernel


// Forward Declaration Inclusions
#include "States\state_euler.h"


#endif // !STATE_H

