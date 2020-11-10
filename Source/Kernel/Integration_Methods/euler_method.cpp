// euler_method.cpp


// Inclusions
#include "euler_method.h"


//----------------------------------------------------------------------------
// Name:    EulerMethod
// Purpose: Default constructor.
//----------------------------------------------------------------------------
kernel::EulerMethod::EulerMethod()
{
  // Does nothing.
}


//----------------------------------------------------------------------------
// Name:    ~EulerMethod
// Purpose: Destructor.
//----------------------------------------------------------------------------
kernel::EulerMethod::~EulerMethod()
{
  // Does nothing.
}


//----------------------------------------------------------------------------
// Name:    doInitialize
// Purpose: This method implements the initialization of static variables for
//          the sake of syncronizing the integration of all states.
//----------------------------------------------------------------------------
void kernel::EulerMethod::doInitialize()
{
  Time_Current = 0;
  Is_Ready = true;
}


//----------------------------------------------------------------------------
// Name:    doReset
// Purpose: This method implements the resetting of the time step to the 
//          provided value.
//----------------------------------------------------------------------------
void kernel::EulerMethod::doReset(double time_step_)
{
  Time_Step = time_step_;
}


//----------------------------------------------------------------------------
// Name:    doUpdateState
// Purpose: This propagates the state forward one time step using the Euler's
//          method.
//----------------------------------------------------------------------------
void kernel::EulerMethod::doUpdateState(State* state_)
{
  (*state_->x) += Time_Step * (*state_->dx);
  Is_Ready = true;
}


//----------------------------------------------------------------------------
// Name:    doUpdateClock
// Purpose: This implements clock updates for use with Euler's method.
//----------------------------------------------------------------------------
void kernel::EulerMethod::doUpdateClock(void)
{
  Time_Current += Time_Step;
}