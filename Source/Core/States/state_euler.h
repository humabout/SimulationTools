// state_euler.h


#ifndef STATE_EULER_H
#define STATE_EULER_H


// Inclusions
#include <memory>
#include "../state.h"
#include "../Clocks/sim_clock.h"


//------------------------------------------------------------------------------
// Name:    nemesis
// Purpose: This namespace holds all aspects of the Nemesis Simulation Toolkit.
//------------------------------------------------------------------------------
namespace nemesis
{


  //--------------------------------------------------------------------------
  // Name:    StateEuler
  // Purpose: This concrete State integrates its state derivative to get its 
  //          variable using Euler's method.
  //--------------------------------------------------------------------------
  template <class T>
  class StateEuler : public State
  {
  public:
    // Constructor
    StateEuler(T& x_,
               T& dx_)
    {
      this->x  = &x_;
      this->dx = &dx_;
    }

    // Destructor
    ~StateEuler()
    {
      // Does Nothing.
    }

    // Functionality
    void propagate(void)
    {
      *(this->x) += nemesis::SimClock::tick() * *(this->dx);
      State::Is_Ready = true;
    }

  private:
    T* x;
    T* dx;


  }; // !StateEuler


} // !core


#endif // !STATE_EULER_H