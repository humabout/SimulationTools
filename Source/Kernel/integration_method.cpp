// integration_method.cpp


// Inclusions
#include <cmath>
#include "config_kernel.h"
#include "integration_method.h"
#include "runge_kutta_4.h"



// Static Variables
kernel::IntegrationMethod::type kernel::IntegrationMethod::Method;
double                          kernel::IntegrationMethod::Time_Current;
double                          kernel::IntegrationMethod::Time_Next = 0;
double                          kernel::IntegrationMethod::Time_Step;
double                          kernel::IntegrationMethod::Sample_Rate;
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
    return new RungeKutta4(state_);
  default:
    return new RungeKutta4(state_);
  }
}


//----------------------------------------------------------------------------
// Name:    doInitialize
// Purpose: This implements the Initialize() interface by setting all static
//          variables to zero.
//----------------------------------------------------------------------------
void kernel::IntegrationMethod::doInitialize(void)
{
  IntegrationMethod::Time_Current = 0;
  IntegrationMethod::Is_Ready = true;
  // RK4 also does these:
  //RungeKutta4::rkStep = 0;
  //RungeKutta4::Time_RK = 0;
}


//----------------------------------------------------------------------------
// Name:    doInitialize
// Purpose: This implements the Initialize() interface by setting all static
//          variables to zero.
//----------------------------------------------------------------------------
void kernel::IntegrationMethod::initialize(kernel::IntegrationMethod::type method_)
{
  doInitialize();
  Method = method_;
}


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
    double sample_time = floor((Time_Current + kernel::EPS) / sample_rate_ + 1)
      * sample_rate_;

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
    return (time_sample_error < kernel::EPS);
  }
  else
  {
    return false;
  }
}


//----------------------------------------------------------------------------
// Name:    reset
// Purpose: This resets the timestep, and if provided, teh sample rate for the 
//          simulation, and recalculates the next time to integrate.
//----------------------------------------------------------------------------
void kernel::IntegrationMethod::reset(double time_step_,
                                      double sample_rate_ = 0)
{
  IntegrationMethod::Time_Step = time_step_;
  IntegrationMethod::Sample_Rate = sample_rate_;
  // Overload in RK4 also does this:
  //RungeKutta4::Half_Time_Step = 0.5 * Time_Step;
}


//----------------------------------------------------------------------------
// Name:    updateClock
// Purpose: This resets updates the shared clock used by the integrator to
//          execute its algorithm. It defers actual implementation as part of
//          the template pattern so that specific integration methods can set
//          exactly how to update the clock.
//----------------------------------------------------------------------------
void kernel::IntegrationMethod::updateClock(void)
{
  doUpdateClock();
}


//----------------------------------------------------------------------------
// Name:    updateState
// Purpose: This resets updates the executes the integration algorithm that 
//          updates the state registered with this instance. It defers actual 
//          implementation as part of the template pattern so that specific 
//          integration methods can set exactly how to update the state.
//----------------------------------------------------------------------------
void kernel::IntegrationMethod::updateState(void)
{
  doUpdateState();
}


//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
// GETTERS
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
double kernel::IntegrationMethod::getTime(void)
{
  return Time_Current;
}


double kernel::IntegrationMethod::getTimeStep(void)
{
  return Time_Step;
}


double kernel::IntegrationMethod::getSampleRate(void)
{
  return Sample_Rate;
}


//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
// SETTERS
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
void kernel::IntegrationMethod::setSampleRate(double sample_rate_)
{
  Sample_Rate = sample_rate_;
}