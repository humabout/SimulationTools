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
  IntegrationMethod::Time_Current = 0;
  IntegrationMethod::Is_Ready = true;
}


//----------------------------------------------------------------------------
// Name:    doReset
// Purpose: This method implements the resetting of the time step to the 
//          provided value.
//----------------------------------------------------------------------------
void kernel::EulerMethod::doReset(double time_step_)
{
  IntegrationMethod::Time_Step = time_step_;
}


//----------------------------------------------------------------------------
// Name:    doUpdateState
// Purpose: This propagates the state forward one time step using the Euler's
//          method.
//----------------------------------------------------------------------------
void kernel::EulerMethod::doUpdateState(State* state_)
{
  (*state_->x) += IntegrationMethod::Time_Step * (*state_->dx);
  IntegrationMethod::Is_Ready = true;
}


//----------------------------------------------------------------------------
// Name:    doUpdateClock
// Purpose: This implements clock updates for use with Euler's method.
//----------------------------------------------------------------------------
void kernel::EulerMethod::doUpdateClock(void)
{
  IntegrationMethod::Time_Current += IntegrationMethod::Time_Step;
}