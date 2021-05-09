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
// Purpose: This file has failed to open. Closing it does nothing but pass a 
//          warning for logging.
//------------------------------------------------------------------------------
void nemesis::FailedState::close(File* file)
{
  // TODO: Pass an error to be logged and return control
}


//------------------------------------------------------------------------------
// Name:    open
// Purpose: This file has failed to open. Opening it does nothing but pass a 
//          warning for logging.
//------------------------------------------------------------------------------
void nemesis::FailedState::open(File* file)
{
  // TODO: Pass an error to be logged and return control
}


//------------------------------------------------------------------------------
// Name:    read
// Purpose: This file has failed to open. Attempts to read it do nothing. Pass a
//          warning for logging.
//------------------------------------------------------------------------------
void nemesis::FailedState::read(File* file)
{
  // TODO: Pass an exception to be logged and return control
}


//------------------------------------------------------------------------------
// Name:    write
// Purpose: This file has failed to open. Attempts to write to it do nothing. 
//          Pass a warning for logging.
//------------------------------------------------------------------------------
void nemesis::FailedState::write(File* file)
{
  // TODO: Pass an exception to be logged and return control
}