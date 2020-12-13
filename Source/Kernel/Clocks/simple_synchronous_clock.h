// simple_synchronous_clock.h


#ifndef SIMPLE_SYNCHRONOUS_CLOCK_H
#define SIMPLE_SYNCHRONOUS_CLOCK_H


// Inclusions
#include "sim_clock.h"


//------------------------------------------------------------------------------
// Name:    kernel
// Purpose: This namespace holds all parts of the simulation kernel.
//------------------------------------------------------------------------------
namespace kernel
{
  //----------------------------------------------------------------------------
  // Name:    SimpleSynchronousClock
  // Purpose: This concretion implements the SimClock interface to create a 
  //          simple clock that does no time stepping to handle simulating 
  //          asynchronous events.
  //----------------------------------------------------------------------------
  class SimpleSynchronousClock : public SimClock
  {
  public:
    // Constructor
    SimpleSynchronousClock();


    // Destructor
    ~SimpleSynchronousClock();


  private:
    // Functionality Implementations
    void doAdvance(void);
    void doInitialize(void);
    void doReset(double max_time_step_);


  }; // !SimpleSynchronousClock

} // !kernel


#endif // !SIMPLE_SYNCHRONOUS_CLOCK_H
