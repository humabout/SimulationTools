// failed_state.cpp


// Inclusions
#include "failed_state.h"



//------------------------------------------------------------------------------
// Name:    FailedState
// Purpose: Default Constructor. This class has no variables to initialize.
//------------------------------------------------------------------------------
nemesis::FailedState::FailedState()
{
  // Does Nothing
}


//------------------------------------------------------------------------------
// Name:    close
// Purpose: This state has failed to open. Closing it does nothing but pass a 
//          warning for logging.
//------------------------------------------------------------------------------
void nemesis::FailedState::close(File* file)
{
  // TODO: Pass an error to be logged and return control
}


//------------------------------------------------------------------------------
// Name:    open
// Purpose: This state has failed to open. Opening it does nothing but pass a 
//          warning for logging.
//------------------------------------------------------------------------------
void nemesis::FailedState::open(File* file)
{
  // TODO: Pass an error to be logged and return control
}