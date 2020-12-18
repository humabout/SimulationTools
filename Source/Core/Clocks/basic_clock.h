// basic_clock.h


#ifndef BASIC_CLOCK_H
#define BASIC_CLOCK_H


// Inclusions
#include "sim_clock.h"


//------------------------------------------------------------------------------
// Name:    core
// Purpose: This namespace holds all parts of the simulation core.
//------------------------------------------------------------------------------
namespace core
{
  //----------------------------------------------------------------------------
  // Name:    BasicClock
  // Purpose: This concretion implements the SimClock interface to create a 
  //          simple clock that does no time stepping to handle simulating 
  //          asynchronous events.
  //----------------------------------------------------------------------------
  class BasicClock : public SimClock
  {
  public:
    // Constructor
    BasicClock(double max_tick_);

    // Destructor
    ~BasicClock();

  private:
    // Functionality Implementations
    void doAdvance(void) override final;
    void doInitialize(void) override final;


  }; // !BasicClock

} // !core


#endif // !BASIC_CLOCK_H
