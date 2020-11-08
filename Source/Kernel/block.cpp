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
  for (
    state = States.begin();
    state != States.end();
    state++
    )
  {
    delete (*state);
  }
}


// TODO: Write this description
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


// TODO: Write this description
//------------------------------------------------------------------------------
// Name:    operator<<
// Purpose: This adds a new state to the block.
//------------------------------------------------------------------------------
void kernel::Block::operator<< (State* state_)
{
  add(state_);
}


// TODO: Write this description
//------------------------------------------------------------------------------
// Name:    doPropagate
// Purpose: This method implements the default behavior for propagating the 
//          state of the block forward one time step.
//------------------------------------------------------------------------------
void kernel::Block::doPropagate(void)
{
  std::vector<State*>::iterator state;
  for (
    state = States.begin();
    state != States.end();
    state++
    )
  {
    (*state)->propagate();
  }
}