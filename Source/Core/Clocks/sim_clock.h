// sim_clock.h


#ifndef SIM_CLOCK_H
#define SIM_CLOCK_H


// Inclusions
#include <memory>


//------------------------------------------------------------------------------
// Name:    core
// Purpose: This namespace holds all parts of the simulation core.
//------------------------------------------------------------------------------
namespace core
{


  //----------------------------------------------------------------------------
  // Name:    SimClock
  // Purpose: This abstract class establishes the interface and basic components
  //          of a clock that keeps time for the simulation as a whole. Its 
  //          children will implement the specifics of timekeeping via a 
  //          template pattern.
  //
  //          It is expected that there will never be more than one simulation 
  //          clock in existence at a time, and that many objects may need to
  //          reference it to operate properly. The latter will be accomplished
  //          by storing relevant data in static variables and providing static
  //          functions for accessing them.
  //----------------------------------------------------------------------------
  class SimClock
  {
  public:
    // Typedefs
    typedef std::shared_ptr<SimClock> pointer;

    // Enum for clock type
    enum class type
    {
      simple_synchronous = 1
    }; // !type


    // Constructors
    SimClock();


    // Destructor
    ~SimClock();


    // Accessors
    static double time(void);
    static double timestep(void);


    // Factory Method
    static std::shared_ptr<core::SimClock> create(type clock_type_);
    

    // Functionality
    void advance(void);
    void initialize(void);
    void reset(double max_time_step_);  // TODO: Find a more appropriate name for this


  protected:
    // Data
    static double Time_Current;
    static double Time_Step;
    static double Max_Time_Step;


    // Functionality Implementations
    virtual void doAdvance(void) = 0;
    virtual void doInitialize(void) = 0;
    virtual void doReset(double max_time_step_) = 0;
  };


} // !core



#endif // !SIM_CLOCK_H
