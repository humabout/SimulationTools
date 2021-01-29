// sim_loop.cpp


// Inclusions
#include <cstddef>
#include <vector>
#include "block.h"
#include "config.h"
#include "sim_loop.h"
#include "Integrators/integrator.h"
#include "Clocks/sim_clock.h"


//------------------------------------------------------------------------------
// Name:    SimLoop
// Purpose: Constructor Overload.
// Inputs:  Time Step [s]
//------------------------------------------------------------------------------
nemesis::SimLoop::SimLoop(double max_tick_)
{
  Clock = SimClock::create(SimClock::type::basic, max_tick_);
}


//------------------------------------------------------------------------------
// Name:    SimLoop
// Purpose: Constructor Overload.
// Inputs:  Time Step [s]
//          Integration Method
//------------------------------------------------------------------------------
nemesis::SimLoop::SimLoop(double           max_tick_,
                          Integrator::type method_)
{
  Propagator = Integrator::create(method_);
  Clock = SimClock::create(SimClock::type::basic, max_tick_);
}


//------------------------------------------------------------------------------
// Name:    SimLoop
// Purpose: Constructor Overload.
// Inputs:  Time Step [s]
//          Integration Method
//          Clock Type
//------------------------------------------------------------------------------
nemesis::SimLoop::SimLoop(double           max_tick_,
                          Integrator::type method_,
                          SimClock::type   clock_type_)
{
  Propagator = Integrator::create(method_);
  Clock = SimClock::create(clock_type_, max_tick_);
}


//------------------------------------------------------------------------------
// Name:    ~SimLoop
// Purpose: Destructor. This object owns nothing and deletes nothing.
//------------------------------------------------------------------------------
nemesis::SimLoop::~SimLoop()
{
  // Does nothing.
}


//------------------------------------------------------------------------------
// Name:    addBlock
// Purpose: This method adds a block to the simulation for updating and 
//          propagation.
//------------------------------------------------------------------------------
void nemesis::SimLoop::addBlock(Block::pointer block_)
{
  Blocks.push_back(block_);
  block_->registerWith(this);
}


//------------------------------------------------------------------------------
// Name:    addEndCondition
// Purpose: This method adds an end condition to the simulation for checking.
//------------------------------------------------------------------------------
void nemesis::SimLoop::addEndCondition(EndCondition::pointer end_condition_)
{
  End_Conditions.push_back(end_condition_);
}


//------------------------------------------------------------------------------
// Name:    addState
// Purpose: This method adds a state variable and its derivative to the sim's 
//          Integrator for propagation.
//------------------------------------------------------------------------------
void nemesis::SimLoop::addState(double& x_,
                                double& dx_)
{
  Propagator->addState(x_, dx_);
}


//------------------------------------------------------------------------------
// Name:    isEnd
// Purpose: This method checks if the simulation has met any end conditions and
//          returns true if it has.
// CURRENT: The end condition checked is if the simulation has exceeded its max
//          simulated time.
//------------------------------------------------------------------------------
bool nemesis::SimLoop::isEnd(void) const
{
  // Check all end conditions when the sim is ready for evaluation and reporting
  std::vector<EndCondition::pointer>::const_iterator condition = End_Conditions.begin();
  while (condition != End_Conditions.end() )
  {
    // Stop checking as soon as an end condition is not met
    if ((*condition)->met())
    {
      return true;
    }
    // Otherwise move on to the next end condition
    else
    {
      condition++;
    }
  }

  // If we got this far, all end conditions were checked and none were met
  return false;
}


//------------------------------------------------------------------------------
// Name:    run
// Purpose: This runs the simulation loop from initializing the simulation to
//          propagating it, to determining when it should end.
// Note:    This will likely grow with time to encompass some message passing
//          both into and out of the loop. This will allow outside routines to
//          pass controls into the simulation, and let the simulation output
//          data and events.
//------------------------------------------------------------------------------
void nemesis::SimLoop::run(void)
{
  // Initialize the clock
  Clock->initialize();

  // Initialize all blocks
  std::vector< Block::pointer >::iterator current_block;
  for (current_block = Blocks.begin(); 
       current_block != Blocks.end(); 
       current_block++)
  {
    (*current_block)->initialize();
  }

  // Execute the simulation loop
  while (!isEnd())
  {
    // Updating any state-dependent information
    for (current_block = Blocks.begin();
         current_block != Blocks.end();
         current_block++)
    {
      (*current_block)->update();
    }

    // Propagating states
    Propagator->updateStates();

    // Updating clock
    Clock->advance();
  }
}