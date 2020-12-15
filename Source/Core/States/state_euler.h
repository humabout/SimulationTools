// state_euler.h


#ifndef STATE_EULER_H
#define STATE_EULER_H


// Inclusions
#include <memory>
#include "..\state.h"


//----------------------------------------------------------------------------
// Name:    core
// Purpose: This namespace holds all parts of the simulation core.
//----------------------------------------------------------------------------
namespace core
{


  //--------------------------------------------------------------------------
  // Name:    StateEuler
  // Purpose: 
  //--------------------------------------------------------------------------
  class StateEuler : public State
  {
  public:
    // Constructor
    StateEuler(double& x_, 
               double& dx_);
    StateEuler(double&                               x_, 
               const std::shared_ptr<core::State>& dx_);
    StateEuler(const std::shared_ptr<core::State>& that);

    // Destructor
    ~StateEuler();

    // Functionality
    void initialize(void) override final;
    void updateState(void) override final;


  }; // !StateEuler


} // !core


#endif // !STATE_EULER_H