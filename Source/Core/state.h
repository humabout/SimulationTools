// state.h


#ifndef STATE_H
#define STATE_H


// Inclusions
#include <memory>


// Forward Declarations
namespace core
{
  template <class T> class StateEuler;
}


//----------------------------------------------------------------------------
// Name:    core
// Purpose: This namespace holds all parts of the simulation core.
//----------------------------------------------------------------------------
namespace core
{


  //--------------------------------------------------------------------------
  // Name:    State
  // Purpose: This class provides the static interface for propagating state 
  //          variables. Each child class will provide a template that 
  //          implements the following functions for the type defined:
  //          1. double
  //          2. math::Vector
  //          3. math::Quaternion
  //          4. math::Matrix
  //
  //          Each child will also provide a constructor that accepts a state
  //          variable and state derivative of type T, plus a propagate method
  //          for integrating the state.
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

    // Destructor
    virtual ~State();

    // Getters
    static bool isReady(void);

    // Setters
    static void setIntegrationMethod(State::type method_);

    //------------------------------------------------------------------------
    // Name:    create
    // Purpose: This factory method creates and returns a new state with the 
    //          provided state and state derrivative.
    // Inputs:  The state
    //          The state derrivative
    //------------------------------------------------------------------------
    template<class T>
    static State::pointer create(T& x_, T& dx_)
    {
      switch (core::State::Method)
      {
      case State::type::euler:
        return State::pointer(new StateEuler<T>(x_, dx_));
      default:
        return NULL;
      }
    }

    // Pure Virtual Functionality
    virtual void propagate(void) = 0;

  protected:
    // Member Variables
    static bool Is_Ready;
    static type Method;


  }; // !StateInterface


} // !core


// Forward Declaration Inclusions
#include "States/state_euler.h"


#endif // !STATE_H

