// state.h


#ifndef STATE_H
#define STATE_H


// Inclusions
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
    State(const State& that);

    // Destructor
    ~State();

    // Assignment Operator
    void operator= (const State& that);

    // Getters
    double get(void) const;

    // Setters
    void set(double* x_,
             double* dx_);

    // Functionality
    void propagate(void);

  protected:
    // State Variables
    double* x;
    double* dx;

    // Integration Method
    kernel::IntegrationMethod* Integrator;


  }; // !StateInterface
  

} // !kernel


#endif // !STATE_H

