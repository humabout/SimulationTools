// max_time_exceeded.h


#ifndef MAX_TIME_EXCEEDED_H
#define MAX_TIME_EXCEEDED_H


// Inclusions
#include "end_condition.h"

//------------------------------------------------------------------------------
// Name:    nemesis
// Purpose: This namespace holds all aspects of the Nemesis Simulation Toolkit.
//------------------------------------------------------------------------------
namespace nemesis
{


  //----------------------------------------------------------------------------
  // Name:    MaxTimeExceeded
  // Purpose: This end condition triggers when the maximum simulation time has
  //          been met
  //----------------------------------------------------------------------------
  class MaxTimeExceeded : public EndCondition
  {
  public:
    // Constructor
    MaxTimeExceeded(double time_max_);

    // Destructor
    ~MaxTimeExceeded();

    // Functionality
    bool met(void) override;

  private:
    double  Time_Max;

  }; // !MaxTimeExceeded
} // !core


#endif // !MAX_TIME_EXCEEDED_H
