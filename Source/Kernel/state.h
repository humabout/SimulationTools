// state.h


#ifndef STATE_H
#define STATE_H


// Inclusions
#include "integration_method.h"


// Forward Declarations
namespace kernel
{
  class RungeKutta4;
}


//----------------------------------------------------------------------------
// Name:    kernel
// Purpose: This namespace holds all parts of the simulation kernel.
//----------------------------------------------------------------------------
namespace kernel
{


  //--------------------------------------------------------------------------
  // Name:    State
  // Purpose: This class represents a single state that is responsible for
  //          propagating itself. It uses a strategy pattern to provide
  //          flexibility in the integration method used, while ensuring that
  //          all states use the same method.
  //--------------------------------------------------------------------------
  class State
  {
  public:
    // Constructors
    State();
    State(double& x_, double& dx_);
    State(double& x_, State& dx_);
    State(const State& that);

    // Destructor
    ~State();

    // Assignment Operator
    void operator= (const State& that);

    // Getters
    double  get(void) const;

    // Setters
    void initialize(double x);

    // Factory
    static State* create(double& x_, double& dx_);
    static State* create(double& x_, State& dx_);
    static State* create(const State& state_);

    // Functionality
    void propagate(void);

  private:
    // State Variables
    double* x;
    double* dx;
    bool Owns_Derrivative;

    // Integration Method
    kernel::IntegrationMethod* Integrator;

    // Friend Classes
    // These classes are considered friend classes because they alone need 
    // access to the value of the state and state derrivative. If there is a 
    // way to give access to only those two values, I'd rather do that. For 
    // now, making integrators, which exist solely to modify the state value, 
    // full access will work.
    friend IntegrationMethod;
    friend RungeKutta4;

  }; // !StateInterface
  

} // !kernel


// Forward Declaration Inclusions
#include "runge_kutta_4.h"


#endif // !STATE_H

