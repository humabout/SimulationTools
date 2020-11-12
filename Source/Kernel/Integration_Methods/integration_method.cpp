// integration_method.cpp


// Inclusions
#include <cmath>
#include "integration_method.h"
#include "euler_method.h"
#include "runge_kutta_4.h"



// Static Variables
double                          kernel::IntegrationMethod::Time_Current;
double                          kernel::IntegrationMethod::Time_Step;
bool                            kernel::IntegrationMethod::Is_Ready = true;
kernel::IntegrationMethod::type kernel::IntegrationMethod::Method = kernel::IntegrationMethod::type::RK4;


//----------------------------------------------------------------------------
// Name:    instance
// Purpose: This getter returns a pointer to the only instance of this class.
//----------------------------------------------------------------------------
kernel::IntegrationMethod::IntegrationMethod()
{
  Time_Current = 0;
  Time_Step    = 0;
  Is_Ready     = true;
}


//----------------------------------------------------------------------------
// Name:    create
// Purpose: This factory creates and returns an instance of the integration 
//          method currently set in Method.
//----------------------------------------------------------------------------
kernel::IntegrationMethod* kernel::IntegrationMethod::create(void)
{
  switch (kernel::IntegrationMethod::Method)
  {
  case type::Euler:
    return new EulerMethod();
  default:
    return NULL;
  }
}


//----------------------------------------------------------------------------
// Name:    initialize
// Purpose: This implements the Initialize() interface by setting all static
//          variables to zero.
//----------------------------------------------------------------------------
void kernel::IntegrationMethod::initialize()
{
  doInitialize();
}


// Commenting out anything related to determining when to sample. This doesn't
// have anything to do with propagating states, so it will sit here as a 
// comment until it an be moved to a more appropriate place.
/*
//----------------------------------------------------------------------------
// Name:    isTimeToSample
// Purpose: This checks if a new sample is ready based on the global sample
//          rate.
//----------------------------------------------------------------------------
bool kernel::IntegrationMethod::isTimeToSample(void)
{
  return isTimeToSample(IntegrationMethod::Sample_Rate);
}


//----------------------------------------------------------------------------
// Name:    isTimeToSample
// Purpose: This checks if a new sample is ready based on the sample rate 
//          provided.
//----------------------------------------------------------------------------
bool kernel::IntegrationMethod::isTimeToSample(double sample_rate_)
{
  if (Is_Ready)
  {
    // Calculating the next sample time before the next inegration time
    double sample_time = floor((Time_Current + kernel::Sample_Time_Error) /
                         sample_rate_ + 1) * sample_rate_;

    // If the next sample is before the next integration time, set the next 
    // integration time to the next sample time and update it.
    if (sample_time < Time_Next)
    {
      Time_Next = sample_time;
      Time_Step = Time_Next - Time_Current;
      // RK4 needs RungeKutta4::Half_Time_Step = 0.5 * IntegrationMethod::Time_Step;
      // TODO: Consider makign this entire thing a function that can be 
      // overriden by children
    }
    else
    {
      // Continue
    }

    // Check if it truly is time to sample based on updates
    double time_sample_error = Time_Current - sample_time + sample_rate_;
    return (time_sample_error < kernel::Sample_Time_Error);
  }
  else
  {
    return false;
  }
}
*/


//----------------------------------------------------------------------------
// Name:    reset
// Purpose: This resets the timestep, and if provided, the sample rate for the 
//          simulation, and recalculates the next time to integrate.
//----------------------------------------------------------------------------
void kernel::IntegrationMethod::reset(double time_step_)
{
  doReset(time_step_);
}


//----------------------------------------------------------------------------
// Name:    setMethod
// Purpose: This clears the old integration instance and sets a new method so
//          that the next time an instance is requested, the new method will
//          generated and returned.
//----------------------------------------------------------------------------
void kernel::IntegrationMethod::setMethod(kernel::IntegrationMethod::type method_)
{
  IntegrationMethod::Method = method_;
}


//----------------------------------------------------------------------------
// Name:    updateClock
// Purpose: This updates the shared clock used by the integrator to execute 
//          its algorithm. It defers actual implementation as part of the 
//          template pattern so that specific integration methods can set
//          exactly how to update the clock.
//----------------------------------------------------------------------------
void kernel::IntegrationMethod::updateClock(void)
{
  doUpdateClock();
}


//----------------------------------------------------------------------------
// Name:    updateState
// Purpose: This updates the executes the integration algorithm that updates 
//          the state registered with this instance. It defers actual 
//          implementation as part of the template pattern so that specific 
//          integration methods can set exactly how to update the state.
//----------------------------------------------------------------------------
void kernel::IntegrationMethod::updateState(State* state_)
{
  doUpdateState(state_);
}


//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
// GETTERS
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
double kernel::IntegrationMethod::time(void)
{
  return Time_Current;
}

double kernel::IntegrationMethod::timestep(void)
{
  return Time_Step;
}

bool kernel::IntegrationMethod::isReady(void)
{
  return Is_Ready;
}