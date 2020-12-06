// state_euler.h


#ifndef STATE_EULER_H
#define STATE_EULER_H


// Inclusions
#include "state.h"


//----------------------------------------------------------------------------
// Name:    kernel
// Purpose: This namespace holds all parts of the simulation kernel.
//----------------------------------------------------------------------------
namespace kernel
{


  //--------------------------------------------------------------------------
  // Name:    StateEuler
  // Purpose: 
  //--------------------------------------------------------------------------
  class StateEuler : public State
  {
  public:
    // Constructor
    StateEuler();
    StateEuler(double& x_, 
               double& dx_);
    StateEuler(double&      x_, 
               StateEuler&  dx_);
    StateEuler(const StateEuler& that);

    // Destructor
    ~StateEuler();

    // Functionality
    void initialize(void) override final;
    void reset(double time_step_) override final;
    void updateState(State* state_) override final;
    void updateClock(void) override final;


  }; // !StateEuler


} // !kernel


#endif // !STATE_EULER_H