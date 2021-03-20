// file_init_state.cpp


// Inclusions
#include "file_init_state.h"

#include <cassert>

#include "initialized_state.h"
#include "uninitialized_state.h"


//------------------------------------------------------------------------------
// Name:    FileInitState
// Purpose: Default Constructor.
//------------------------------------------------------------------------------
nemesis::FileInitState::FileInitState()
{
  // Nothing to initialize
}


//------------------------------------------------------------------------------
// Name:    FileInitState
// Purpose: Factory method for initialization states.
//------------------------------------------------------------------------------
nemesis::FileInitState::pointer nemesis::FileInitState::create(type new_state)
{
  switch (new_state)
  {
  case type::initialized:
    return FileInitState::pointer(new InitializedState);
  case type::uninitialized:
    return FileInitState::pointer(new UninitializedState);
  default:
    // How did we get here?
    assert(false);
  }
}