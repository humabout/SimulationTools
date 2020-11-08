// sim_loop.cpp


// Inclusions
#include <vector>
#include "block.h"
#include "Integration_Methods/integration_method.h"
#include "sim_loop.h"


//------------------------------------------------------------------------------
// Name:    SimLoop
// Purpose: Default Constructor. The integrator type defaults to RK4 unless set
//          otherwise.
//------------------------------------------------------------------------------
kernel::SimLoop::SimLoop()
{
  Time_Step = 0;
  Time_Max  = 0;
  IntegrationMethod::setIntegrationMethod(IntegrationMethod::type::RK4);
  Integrator = IntegrationMethod::instance();
}


//------------------------------------------------------------------------------
// Name:    SimLoop
// Purpose: Constructor Overload.
// Inputs:  Time Step [s]
//          Maximum Simulated Time [s]
//------------------------------------------------------------------------------
kernel::SimLoop::SimLoop(double                  time_step_,
                         double                  time_max_,
                         std::vector<Block*>     blocks_,
                         IntegrationMethod::type integration_method_)
{
  Time_Step = time_max_;
  Time_Max = time_max_;
  Blocks = blocks_;
  IntegrationMethod::setIntegrationMethod(integration_method_);
  Integrator = IntegrationMethod::instance();
}


//------------------------------------------------------------------------------
// Name:    ~SimLoop
// Purpose: Destructor. This object owns Integrator and is responsible for 
//          freeing that memory.
//------------------------------------------------------------------------------
kernel::SimLoop::~SimLoop()
{
  // This deletes the IntegrationMethod instance to free memory.
  IntegrationMethod::resetInstance();
}


//------------------------------------------------------------------------------
// Name:    add
// Purpose: This method adds a block to the simulation for updating and 
//          propagation.
//------------------------------------------------------------------------------
void kernel::SimLoop::add(Block* block_)
{
  Blocks.push_back(block_);
}


//------------------------------------------------------------------------------
// Name:    add
// Purpose: This method checks if the simulation has met any end conditions and
//          returns true if it has.
// CURRENT: The end condition checked is if the simulation has exceeded its max
//          simulated time.
// TODO:    This will eventually return the results of OR on all EndCondition
//          objects in the sim's end conditions list.
//------------------------------------------------------------------------------
bool kernel::SimLoop::isEnd(void) const 
{ 
  if (IntegrationMethod::isReady())
  {
    return (Integrator->time() > Time_Max);
  }
  else
  {
    return false;
  }
}



//------------------------------------------------------------------------------
// Name:    operator<<
// Purpose: This operator adds a block to the simulation for updating and 
//          propagation.
//------------------------------------------------------------------------------
void kernel::SimLoop::operator<< (Block* block_)
{
  add(block_);
}


//------------------------------------------------------------------------------
// Name:    run
// Purpose: This runs the simulation loop from initializing the simulation to
//          propagating it, to determining when it should end.
// TODO:    This will likely grow with time to encompass some message passing
//          both into and out of the loop. This will allow outside routines to
//          pass controls into the simulation, and let the simulation output
//          data and events.
//
//          Interestingly, if this is done, it is "just" a render step away from
//          being a game.
//------------------------------------------------------------------------------
void kernel::SimLoop::run(void)
{
  // Initialize the simulation
  Integrator->initialize();
  Integrator->reset(Time_Step);

  // Initialize all blocks
  std::vector<Block*>::iterator current_block;
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
    Integrator->updateClock();
  }
}