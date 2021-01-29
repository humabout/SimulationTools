// block.cpp


// Inclusions
#include <memory>
#include "block.h"
#include "state.h"
#include "sim_loop.h"


//------------------------------------------------------------------------------
// Name:    ~Block
// Purpose: Destructor. This object owns nothing and deletes nothing.
//------------------------------------------------------------------------------
nemesis::Block::~Block()
{
  // Does Nothing.
}


//------------------------------------------------------------------------------
// Name:    addState
// Purpose: This method adds a new state to the block. It forwards the call to 
//          Sim->addState, which adds the state to the Integrator.
//------------------------------------------------------------------------------
void nemesis::Block::addState(double&  x_,
                              double&  dx_,
                              SimLoop* sim_)
{
  sim_->addState(x_, dx_);
}


//------------------------------------------------------------------------------
// Name:    initialize
// Purpose: This method sets the initial values for the block's internal state.
//          It is part of the template pattern and deferes implementation to
//          doInitialize().
//------------------------------------------------------------------------------
void nemesis::Block::initialize(void)
{
  doInitialize();
}


//------------------------------------------------------------------------------
// Name:    registerWith
// Purpose: This method registers the Block with the sim. Part of this is 
//          process includes registering any state variables that belong to the 
//          Block with the Sim for propagation. For this reason, child classes 
//          are expected to provide the implementation for this method via a 
//          template pattern. The implementation is stored in the pure virtual 
//          function doRegisterWith.
//------------------------------------------------------------------------------
void nemesis::Block::registerWith(SimLoop* sim_)
{
  doRegisterWith(sim_);
}


//------------------------------------------------------------------------------
// Name:    update
// Purpose: This method updates the part of the block's state that is dependent 
//          on state variables. This is done in preparation for propagating the 
//          It is part of the template pattern and deferes implementation to 
//          doUpdate().
//------------------------------------------------------------------------------
void nemesis::Block::update(void)
{
  doUpdate();
}