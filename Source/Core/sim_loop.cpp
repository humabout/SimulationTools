// sim_loop.cpp


// Inclusions
#include <cstddef>
#include <vector>
#include "block.h"
#include "config.h"
#include "sim_loop.h"


//------------------------------------------------------------------------------
// Name:    SimLoop
// Purpose: Constructor Overload.
// Inputs:  Time Step [s]
//------------------------------------------------------------------------------
core::SimLoop::SimLoop(double      max_tick_)
{
  State::setIntegrationMethod(State::type::euler);
  Clock = SimClock::create(SimClock::type::basic, max_tick_);
}


//------------------------------------------------------------------------------
// Name:    SimLoop
// Purpose: Constructor Overload.
// Inputs:  Time Step [s]
//          Integration Method
//------------------------------------------------------------------------------
core::SimLoop::SimLoop(double      max_tick_,
                       State::type integration_method_)
{
  State::setIntegrationMethod(integration_method_);
  Clock = SimClock::create(SimClock::type::basic, max_tick_);
}


//------------------------------------------------------------------------------
// Name:    SimLoop
// Purpose: Constructor Overload.
// Inputs:  Time Step [s]
//          Integration Method
//          Clock Type
//------------------------------------------------------------------------------
core::SimLoop::SimLoop(double         max_tick_,
                       State::type    integration_method_,
                       SimClock::type clock_type_)
{
  State::setIntegrationMethod(integration_method_);
  Clock = SimClock::create(clock_type_, max_tick_);
}


//------------------------------------------------------------------------------
// Name:    ~SimLoop
// Purpose: Destructor. This object owns nothing and deletes nothing.
//------------------------------------------------------------------------------
core::SimLoop::~SimLoop()
{
  // Does nothing.
}


//------------------------------------------------------------------------------
// Name:    addBlock
// Purpose: This method adds a block to the simulation for updating and 
//          propagation.
//------------------------------------------------------------------------------
void core::SimLoop::addBlock(Block::pointer block_)
{
  Blocks.push_back(block_);
}


//------------------------------------------------------------------------------
// Name:    addEndCondition
// Purpose: This method adds an end condition to the simulation for checking.
//------------------------------------------------------------------------------
void core::SimLoop::addEndCondition(EndCondition::pointer end_condition_)
{
  End_Conditions.push_back(end_condition_);
}


//------------------------------------------------------------------------------
// Name:    isEnd
// Purpose: This method checks if the simulation has met any end conditions and
//          returns true if it has.
// CURRENT: The end condition checked is if the simulation has exceeded its max
//          simulated time.
//------------------------------------------------------------------------------
bool core::SimLoop::isEnd(void) const 
{
  // Check all end conditions when the sim is ready for evaluation and reporting
  std::vector<EndCondition::pointer>::const_iterator condition = End_Conditions.begin();
  while (core::State::isReady() && 
         condition != End_Conditions.end()    )
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
// Name:    operator<<
// Purpose: This operator adds a block to the simulation for updating and 
//          propagation.
//------------------------------------------------------------------------------
void core::SimLoop::operator<< (Block::pointer block_)
{
  addBlock(block_);
}


//------------------------------------------------------------------------------
// Name:    operator<<
// Purpose: This operator adds an end condition to the simulation for checking
//          simulation termination.
//------------------------------------------------------------------------------
void core::SimLoop::operator<< (EndCondition::pointer condition_)
{
  addEndCondition(condition_);
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
void core::SimLoop::run(void)
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
    for (current_block = Blocks.begin();
         current_block != Blocks.end();
         current_block++)
    {
      (*current_block)->propagate();
    }

    // Updating clock
    Clock->advance();
  }
}