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
  template <class T>
  class StateEuler : public State
  {
  public:
    // Constructor
    StateEuler(T& x_,
               T& dx_);

    // Destructor
    ~StateEuler();

    // Functionality
    void propagate();

  private:
    T* x;
    T* dx;


  }; // !StateEuler


} // !core


#endif // !STATE_EULER_H