// file_open_state.cpp


// Inclusions
#include <memory>

#include "file_open_state.h"

#include "failed_state.h"
#include "opened_state.h"
#include "closed_state.h"

#include <cassert>


//------------------------------------------------------------------------------
// Name:    FileOpenState
// Purpose: Default Constructor. This class has nothing to initialize.
//------------------------------------------------------------------------------
nemesis::FileOpenState::FileOpenState()
{
  // Does Nothing
}


//------------------------------------------------------------------------------
// Name:    create
// Purpose: Factory Method. Returns a shared pointer to a new instance of the
//          requested fiel state type.
//------------------------------------------------------------------------------
nemesis::FileOpenState::pointer nemesis::FileOpenState::create(type state_type)
{
  switch (state_type)
  {
  case type::opened:
    return nemesis::FileOpenState::pointer(new OpenedState);
  case type::closed:
    return nemesis::FileOpenState::pointer(new ClosedState);
  case type::failed:
    return nemesis::FileOpenState::pointer(new FailedState);
  default:
    // How did we even get here?!
    // TODO: Create and throw an error if this is reached.
    assert(false);
  }
}