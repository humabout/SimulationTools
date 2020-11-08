// block.cpp


// Inclusions
#include <vector>
#include "block.h"
#include "state.h"


//------------------------------------------------------------------------------
// Name:    ~Block
// Purpose: Destructor. Delete all States owned by this Block.
//------------------------------------------------------------------------------
kernel::Block::~Block()
{
  std::vector<State*>::iterator state;
  for (state = States.begin();
       state != States.end();
       state++)
  {
    delete (*state);
  }
}


//------------------------------------------------------------------------------
// Name:    add
// Purpose: This method adds a new state to the block.
//------------------------------------------------------------------------------
void kernel::Block::add(double& x_, double& dx_)
{
  States.push_back(new State(x_, dx_));
}


//------------------------------------------------------------------------------
// Name:    add (overload)
//------------------------------------------------------------------------------
void kernel::Block::add(double& x_, State& dx_)
{
  States.push_back(new State(x_, dx_));
}

//------------------------------------------------------------------------------
// Name:    add (overload)
//------------------------------------------------------------------------------
void kernel::Block::add(State* state_)
{
  States.push_back(state_);
}


//------------------------------------------------------------------------------
// Name:    operator<<
// Purpose: This adds a new state to the block.
//------------------------------------------------------------------------------
void kernel::Block::operator<< (State* state_)
{
  add(state_);
}


//------------------------------------------------------------------------------
// Name:    doPropagate
// Purpose: This method implements the default behavior for propagating the 
//          state of the block forward one time step.
// TODO:    Make this run state->propagate() in a loop until integration is over? Perhapse this needs to be done at the simulation level.
//------------------------------------------------------------------------------
void kernel::Block::doPropagate(void)
{
  std::vector<State*>::iterator state;
  for (state = States.begin();
       state != States.end();
       state++)
  {
    (*state)->propagate();
  }
}