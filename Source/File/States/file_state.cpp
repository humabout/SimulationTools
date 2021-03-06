// file_state.cpp


// Inclusions
#include <memory>

#include "file_state.h"

#include "failed_state.h"


//------------------------------------------------------------------------------
// Name:    FileState
// Purpose: Default Constructor. This class has nothing to initialize.
//------------------------------------------------------------------------------
nemesis::FileState::FileState()
{
  // Does Nothing
}


//------------------------------------------------------------------------------
// Name:    create
// Purpose: Factory Method. Returns a shared pointer to a new instance of the
//          requested fiel state type.
//------------------------------------------------------------------------------
nemesis::FileState::pointer nemesis::FileState::create(type state_type)
{
  switch (state_type)
  {
  case type::unopened:
  case type::opened:
  case type::closed:
  case type::failed:
    return std::make_shared<FileState>(new FailedState);
  default:
    // How did we even get here?!
    // TODO: Create and throw an error if this is reached.
  }
}