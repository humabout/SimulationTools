// integration_method.cpp


// Inclusions
#include <cmath>
#include "integration_method.h"
#include "runge_kutta_4.h"



// Static Variables
kernel::IntegrationMethod::type kernel::IntegrationMethod::Method;
double                          kernel::IntegrationMethod::Time_Current;
double                          kernel::IntegrationMethod::Time_Step;
bool                            kernel::IntegrationMethod::Is_Ready = true;


//----------------------------------------------------------------------------
// Name:    IntegrationMethod
// Purpose: Default Constructor.
//----------------------------------------------------------------------------
kernel::IntegrationMethod::IntegrationMethod()
{
  // Nothing to initialize.
}


//----------------------------------------------------------------------------
// Name:    ~IntegrationMethod
// Purpose: Destructor. This interface has no memory to deallocate.
//----------------------------------------------------------------------------
kernel::IntegrationMethod::~IntegrationMethod()
{
  // Nothing to dealocate.
}


//----------------------------------------------------------------------------
// Name:    create
// Purpose: Factory method that returns an instance of the correct type of
//          integration method based on the global integration method being
//          used.
//----------------------------------------------------------------------------
kernel::IntegrationMethod* kernel::IntegrationMethod::create(void)
{
  switch (Method)
  {
  case type::Euler:
    // return new Euler();
  case type::RK2:
    // return new RungeKutta2();
  case type::Velocity_Verlet:
    // return new VelocityVerlet();
  case type::RK4:
    return new RungeKutta4();
  default:
    return new RungeKutta4();
  }
}


//----------------------------------------------------------------------------
// Name:    create (overload)
//----------------------------------------------------------------------------
kernel::IntegrationMethod* kernel::IntegrationMethod::create(kernel::State* state_)
{
  switch (Method)
  {
  case type::Euler:
    // return new Euler(state_);
  case type::RK2:
    // return new RungeKutta2(state_);
  case type::Velocity_Verlet:
    // return new VelocityVerlet(state_);
  case type::RK4:
    return new RungeKutta4();
  default:
    return new RungeKutta4();
  }
}


//----------------------------------------------------------------------------
// Name:    initialize
// Purpose: This implements the Initialize() interface by setting all static
//          variables to zero.
//----------------------------------------------------------------------------
void kernel::IntegrationMethod::initialize(kernel::IntegrationMethod::type method_)
{
  doInitialize();
  Method = method_;
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
void kernel::IntegrationMethod::updateState(State* state)
{
  doUpdateState(state);
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