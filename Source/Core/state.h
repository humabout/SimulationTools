// state.h


#ifndef STATE_H
#define STATE_H


// Inclusions
#include <memory>


// Forward Declarations
namespace core
{
  class StateEuler;
}


//----------------------------------------------------------------------------
// Name:    core
// Purpose: This namespace holds all parts of the simulation core.
//----------------------------------------------------------------------------
namespace core
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
    State(double&               x_, 
          const State::pointer& dx_);
    State(const State::pointer& that);
    State(const State& that);

    // Destructor
    virtual ~State();

    // Getters
    static bool isReady(void);
    double* x_(void) const;
    double* dx_(void) const;

    // Setters
    static void setIntegrationMethod(State::type method_);

    // Factory
    static State::pointer create(double& x_, 
                                 double& dx_);
    static State::pointer create(double&               x_,
                                 const State::pointer& dx_);
    static State::pointer create(const State::pointer& state_);

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


  }; // !StateInterface


} // !core


// Forward Declaration Inclusions
#include "States/state_euler.h"


#endif // !STATE_H

