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
    BasicClock();


    // Destructor
    ~BasicClock();


  private:
    // Functionality Implementations
    void doAdvance(void) override;
    void doInitialize(void) override;
    void doReset(double max_time_step_) override;


  }; // !BasicClock

} // !core


#endif // !BASIC_CLOCK_H
