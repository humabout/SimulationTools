// state.h


#ifndef STATE_H
#define STATE_H


// Inclusions
#include <cstddef>
#include "integration_method.h"


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


  }; // !StateInterface
  

} // !kernel


#endif // !STATE_H

