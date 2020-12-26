// block.cpp


// Inclusions
#include <memory>
#include <vector>
#include "block.h"
#include "state.h"


//------------------------------------------------------------------------------
// Name:    ~Block
// Purpose: Destructor. This object owns nothing and deletes nothing.
//------------------------------------------------------------------------------
core::Block::~Block()
{

}


//------------------------------------------------------------------------------
// Name:    add
// Purpose: This method adds a new state to the block.
//------------------------------------------------------------------------------
void core::Block::addState(double& x_, 
                           double& dx_)
{
  States.push_back(State::create(x_, dx_));
}


//------------------------------------------------------------------------------
// Name:    doPropagate
// Purpose: This method implements the default behavior for propagating the 
//          state of the block forward one time step.
//------------------------------------------------------------------------------
void core::Block::doPropagate(void)
{
  std::vector< std::shared_ptr<State> >::iterator state;
  for (state = States.begin();
       state != States.end();
       state++)
  {
    (*state)->propagate();
  }
}


//------------------------------------------------------------------------------
// Name:    initialize
// Purpose: This method sets the initial values for the block's internal state.
//          It is part of the template pattern and deferes implementation to
//          doInitialize().
//------------------------------------------------------------------------------
void core::Block::initialize(void)
{
  doInitialize();
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
void core::Block::propagate(void)
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
void core::Block::update(void)
{
  doUpdate();
}