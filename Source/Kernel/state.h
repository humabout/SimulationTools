// state.h


#ifndef STATE_H
#define STATE_H


// Inclusions
#include <memory>


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
    // Typedefs
    typedef std::shared_ptr<State> pointer;

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
    State(double&                       x_, 
          const State::pointer& dx_);
    State(const State::pointer& that);
    State(const State& that);

    // Destructor
    virtual ~State();

    // Getters
    static bool isReady(void);

    // Setters
    static void setIntegrationMethod(State::type method_);

    // Factory
    static std::shared_ptr<State> create(double& x_, 
                                         double& dx_);
    static std::shared_ptr<State> create(double&               x_, 
                                         const State::pointer& dx_);
    static std::shared_ptr<State> create(const State::pointer& state_);

    // Functionality
    virtual void initialize() = 0;
    virtual void updateState(void) = 0;

  protected:
    // Member Variables
    static bool Is_Ready;
    static type Method;

    // State Variables
    double* x;
    double* dx;

    // Friend Child Classes
    friend StateEuler;


  }; // !StateInterface


} // !kernel


// Forward Declaration Inclusions
#include "States/state_euler.h"


#endif // !STATE_H

