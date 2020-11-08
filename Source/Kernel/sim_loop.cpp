// sim_loop.cpp


// Inclusions
#include <vector>
#include "block.h"
#include "Integration_Methods/integration_method.h"
#include "sim_loop.h"


// TODO: Write this description
//------------------------------------------------------------------------------
// Name:    run
// Purpose: 
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