// state_interface.h


#ifndef STATE_INTERFACE_H
#define STATE_INTERFACE_H


// Forward Declarations
namespace kernel
{
  class Integrator;
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
  //          propagating itself in time and reporting the results. It uses
  //          several static variables to sync integration across all states
  //          because time integration must always use the same timing and
  //          method to produce usefully comparable results.
  //
  //          This class may serve as a superclass for states using other
  //          integration methods.
  //
  // TODO:    Consider breakign integration method and associated static
  //          timing variables into their own integration classes that can be
  //          used as part of a strategy pattern to compose a state. This may
  //          do a better job of encapsulating reponsibility and allowing for
  //          more flexibility and ease of interfacing from a user's point of
  //          view.
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
    double set(double x_);

    // Functionality
    void propagate(void);

  protected:

  private:
    // State Variables
    double* x;
    double* dx;

    // Integration Method
    Integrator* Propagate;

  }; // !StateInterface

} // !kernel
#endif // !STATE_INTERFACE_H

