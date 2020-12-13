// sim_loop.cpp


// Inclusions
#include <cstddef>
#include <vector>
#include "block.h"
#include "config.h"
#include "sim_loop.h"


//------------------------------------------------------------------------------
// Name:    SimLoop
// Purpose: Default Constructor. The integrator type defaults to Euler unless 
//          set otherwise.
//------------------------------------------------------------------------------
kernel::SimLoop::SimLoop()
{
  Time_Step = 0;
  State::setIntegrationMethod(State::type::euler);
  Clock = SimClock::create(SimClock::type::simple_synchronous);
}


//------------------------------------------------------------------------------
// Name:    SimLoop
// Purpose: Constructor Overload.
// Inputs:  Time Step [s]
//          Integration Method
//------------------------------------------------------------------------------
kernel::SimLoop::SimLoop(double      max_time_step_,
                         State::type integration_method_)
{
  Time_Step = max_time_step_;
  State::setIntegrationMethod(integration_method_);
  Clock = SimClock::create(SimClock::type::simple_synchronous);
}


//------------------------------------------------------------------------------
// Name:    SimLoop
// Purpose: Constructor Overload.
// Inputs:  Time Step [s]
//          Integration Method
//          Clock Type
//------------------------------------------------------------------------------
kernel::SimLoop::SimLoop(double         max_time_step_,
                         State::type    integration_method_,
                         SimClock::type clock_type_)
{
  Time_Step = max_time_step_;
  State::setIntegrationMethod(integration_method_);
  Clock = SimClock::create(clock_type_);
}


//------------------------------------------------------------------------------
// Name:    ~SimLoop
// Purpose: Destructor. This object owns nothing and deletes nothing.
//------------------------------------------------------------------------------
kernel::SimLoop::~SimLoop()
{
  // Does nothing.
}


//------------------------------------------------------------------------------
// Name:    addBlock
// Purpose: This method adds a block to the simulation for updating and 
//          propagation.
//------------------------------------------------------------------------------
void kernel::SimLoop::addBlock(Block::pointer block_)
{
  Blocks.push_back(block_);
}


//------------------------------------------------------------------------------
// Name:    addEndCondition
// Purpose: This method adds an end condition to the simulation for checking.
//------------------------------------------------------------------------------
void kernel::SimLoop::addEndCondition(EndCondition::pointer end_condition_)
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
bool kernel::SimLoop::isEnd(void) const 
{
  // Check all end conditions when the sim is ready for evaluation and reporting
  std::vector<EndCondition::pointer>::const_iterator condition = End_Conditions.begin();
  while (kernel::State::isReady() && 
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
void kernel::SimLoop::operator<< (Block::pointer block_)
{
  addBlock(block_);
}


//------------------------------------------------------------------------------
// Name:    operator<<
// Purpose: This operator adds an end condition to the simulation for checking
//          simulation termination.
//------------------------------------------------------------------------------
void kernel::SimLoop::operator<< (EndCondition::pointer condition_)
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
void kernel::SimLoop::run(void)
{
  // Initialize the clock
  Clock->initialize();
  Clock->reset(Time_Step);

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