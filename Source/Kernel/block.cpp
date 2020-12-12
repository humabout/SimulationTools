// block.cpp


// Inclusions
#include <vector>
#include "block.h"
#include "state.h"


//------------------------------------------------------------------------------
// Name:    Block
// Purpose: Default Constructor.
//------------------------------------------------------------------------------
kernel::Block::Block()
{
  States.clear();
}



//------------------------------------------------------------------------------
// Name:    Block
// Purpose: Copy Constructor.
//------------------------------------------------------------------------------
kernel::Block::Block(const Block& that)
{
  this->States = that.States;
}


//------------------------------------------------------------------------------
// Name:    ~Block
// Purpose: Destructor. Delete all States owned by this Block.
//------------------------------------------------------------------------------
kernel::Block::~Block()
{
  /*
  std::vector<State*>::iterator state;
  for (state = States.begin();
       state != States.end();
       ++state)
  {
    delete *state;
    *state = nullptr;
  }
  */
}


//------------------------------------------------------------------------------
// Name:    add
// Purpose: This method adds a new state to the block.
//------------------------------------------------------------------------------
void kernel::Block::add(double& x_, double& dx_)
{
  States.push_back(State::create(x_, dx_));
}


//------------------------------------------------------------------------------
// Name:    add (overload)
//------------------------------------------------------------------------------
void kernel::Block::add(double& x_, State& dx_)
{
  States.push_back(State::create(x_, dx_));
}


//------------------------------------------------------------------------------
// Name:    add (overload)
//------------------------------------------------------------------------------
void kernel::Block::add(State* state_)
{
  States.push_back(state_);
}


//------------------------------------------------------------------------------
// Name:    doPropagate
// Purpose: This method implements the default behavior for propagating the 
//          state of the block forward one time step.
//------------------------------------------------------------------------------
void kernel::Block::doPropagate(void)
{
  std::vector<State*>::iterator state;
  for (state = States.begin();
       state != States.end();
       state++)
  {
    (*state)->updateState();
  }
}


//------------------------------------------------------------------------------
// Name:    initialize
// Purpose: This method sets the initial values for the block's internal state.
//          It is part of the template pattern and deferes implementation to
//          doInitialize().
//------------------------------------------------------------------------------
void kernel::Block::initialize(void)
{
  doInitialize();
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
// Name:    propagate
// Purpose: This method propagates the block's state variables forward one 
//          integration step. This may not be a true time step, depending on the
//          integration method used. It is up to the integrator to track when 
//          the value of state variables are real and when they are inbetween 
//          values. It is part of the template pattern and deferes 
//          implementation to doPropagate().
//------------------------------------------------------------------------------
void kernel::Block::propagate(void)
{
  doPropagate();
}


//------------------------------------------------------------------------------
// Name:    update
// Purpose: This method updates the part of the block's state that is dependent 
//          on state variables. This is done in preparation for propagating the 
//          It is part of the template pattern and deferes implementation to 
//          doUpdate().
//------------------------------------------------------------------------------
void kernel::Block::update(void)
{
  doUpdate();
}