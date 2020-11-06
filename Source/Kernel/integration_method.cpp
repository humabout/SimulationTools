// integration_method.cpp


// Inclusions
#include <cmath>
//#include <cstdlib>
//#include <ctime>
//#include <iostream>
//#include <stdexcept>
#include "config_kernel.h"
#include "integration_method.h"



// Static Variables
kernel::IntegrationMethod::type kernel::IntegrationMethod::Method;
double                          kernel::IntegrationMethod::Time_Current;
double                          kernel::IntegrationMethod::Time_Next = 0;
double                          kernel::IntegrationMethod::Time_Step;
double                          kernel::IntegrationMethod::Sample_Rate;
bool                            kernel::IntegrationMethod::Is_Ready = true;


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


