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

  // TODO:  This implementation is really screaming "Use a strategy 
  //        pattern!"
  IntegrationMethod::setIntegrationMethod(IntegrationMethod::type::RK4);
  Integrator = IntegrationMethod::create();
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

  // TODO:  This implementation is really screaming "Use a strategy 
  //        pattern!"
  IntegrationMethod::setIntegrationMethod(integration_method_);
  Integrator = IntegrationMethod::create();
}


//------------------------------------------------------------------------------
// Name:    ~SimLoop
// Purpose: Destructor. This object owns Integrator and is responsible for 
//          freeing that memory.
//------------------------------------------------------------------------------
kernel::SimLoop::~SimLoop()
{
  delete Integrator;
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
  return (Integrator->time() > Time_Max); 
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
  // TODO:  Should this be its own function?
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
  // TODO:  Somewhere in here is where we might want to check when the integrator has computed the actual value.
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