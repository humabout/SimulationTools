// sim_loop.h


#ifndef SIM_LOOP_H
#define SIM_LOOP_H


// Inclusions
#include <memory>
#include <vector>
#include "block.h"
#include "Clocks/sim_clock.h"
#include "End_Conditions/end_condition.h"


//------------------------------------------------------------------------------
// Name:    nemesis
// Purpose: This namespace holds all aspects of the Nemesis Simulation Toolkit.
//------------------------------------------------------------------------------
namespace nemesis
{


  //----------------------------------------------------------------------------
  // Name:    SimLoop
  // Purpose: This class is responsible for running the simulation loop until
  //          end conditions are met. It will use a strategy pattern to compose
  //          various parts of the loop, like end conditions and integration
  //          method from parts to give the user more flexibility when setting
  //          up a simulation.
  //----------------------------------------------------------------------------
  class SimLoop
  {
  public:
    // Typedef
    typedef std::shared_ptr<SimLoop> pointer;

    // Constructors
    SimLoop(double time_step_);
    SimLoop(double      time_step_,
            State::type integration_method_);
    SimLoop(double         time_step_,
            State::type    integration_method_,
            SimClock::type clock_type_);

    // Destructor
    ~SimLoop();

    // Functionality
    void addBlock(Block::pointer block_);
    void addEndCondition(EndCondition::pointer end_condition_);
    void operator<< (Block::pointer block_);
    void operator<< (EndCondition::pointer condition_);
    void run(void);

  private:
    // Member Variables
    SimClock::pointer                  Clock;
    std::vector<Block::pointer>        Blocks;
    std::vector<EndCondition::pointer> End_Conditions;

    // Functionality
    bool isEnd(void) const;

  }; // !SimLoop


} // !core


#endif // !SIM_LOOP_H
