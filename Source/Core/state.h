// state.h


#ifndef STATE_H
#define STATE_H


// Inclusions
#include <memory>
#include "../Math/matrix.h"
#include "../Math/quaternion.h"
#include "../Math/vector.h"


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

    // Factory
    static State::pointer create(double& x_, 
                                 double& dx_);
    static State::pointer create(math::Vector& x_,
                                 math::Vector& dx_);
    static State::pointer create(math::Quaternion& x_,
                                 math::Quaternion& dx_);
    static State::pointer create(math::Matrix& x_,
                                 math::Matrix& dx_);

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

