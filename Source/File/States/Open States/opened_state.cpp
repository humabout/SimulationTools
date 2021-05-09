// opened_state.cpp


// Inclusions
#include "opened_state.h"



//------------------------------------------------------------------------------
// Name:    OpenedState
// Purpose: Default Constructor. This class has no variables to initialize.
//------------------------------------------------------------------------------
nemesis::OpenedState::OpenedState()
{
  // Does Nothing
}


//------------------------------------------------------------------------------
// Name:    close
// Purpose: This closes the file and transitions to a closed state.
//------------------------------------------------------------------------------
void nemesis::OpenedState::close(File* file)
{
  file->do_close();
  file->set_open_state(type::closed);
}


//------------------------------------------------------------------------------
// Name:    open
// Purpose: This state is already open. Calling open on it is redundant. Throw a
//          warning for logging, but otherwise do nothing.
//------------------------------------------------------------------------------
void nemesis::OpenedState::open(File* file)
{
  // TODO: Pass an exception to be logged and return control
}


//------------------------------------------------------------------------------
// Name:    read
// Purpose: This reads the contents of an opened file into memory by forwarding
//          the call to the originating file object as part of the template
//          pattern.
//------------------------------------------------------------------------------
void nemesis::OpenedState::read(File* file)
{
  file->do_read();
}


//------------------------------------------------------------------------------
// Name:    write
// Purpose: This writes to an open file by forwarding the call to the 
//          originating file object as part of the template pattern.
//------------------------------------------------------------------------------
void nemesis::OpenedState::write(File* file)
{
  file->do_write();
}
