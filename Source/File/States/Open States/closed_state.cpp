// closed_state.cpp


// Inclusions
#include "closed_state.h"
#include "../../../Console Manager/console_manager.h"

#include <cassert>



//------------------------------------------------------------------------------
// Name:    UnopenedState
// Purpose: Default Constructor. This class has no variables to initialize.
//------------------------------------------------------------------------------
nemesis::ClosedState::ClosedState()
{
  // Does nothing and does it well!
}


//------------------------------------------------------------------------------
// Name:    close
// Purpose: This file has not been opened and therefore cannot be closed. Throw
//          a warning for logging, but otherwise do nothing.
//------------------------------------------------------------------------------
void nemesis::ClosedState::close(File* file)
{
  // TODO: Pass an exception to be logged and return control
}


//------------------------------------------------------------------------------
// Name:    open
// Purpose: Opens a closed file
//------------------------------------------------------------------------------
void nemesis::ClosedState::open(File* file)
{
  // Open and validate the file stream. If something went wrong, try again and 
  // see if that fixed it.
  file->do_open(); 

  // Otherwise, ask the user what to do and then do it.
  if (file->FileStream.is_open())
  {
    // The file is open! Yay!
    file->set_open_state(type::opened);
  } 
  else
  {
    // Request user do something
    std::string menu_message = "\nFile failed to open: " + file->Directory.get() + file->Name + ".";
    std::vector<std::string> menu_options({ "Proceed without saving","Retry","Exit" });
    int user_input = nemesis::ConsoleManager::menu(menu_message, menu_options);

    switch (user_input)
    {
    case 1: // Proceed Without Saving
      file->set_open_state(type::failed);
      break;
    case 2: // Retry
      open(file);
      break;
    case 3: // Exit Gracefully
      // TODO: Send warning to error log to log exit request.
      std::exit(0);
    default:
      // Invalid result. This should never be reached. If it is, someone changed something in the code and it needs to be fixed ASAP
      assert(false);
    } // switch (user_input)
  } // !file->FileStream.is_open()
}


//------------------------------------------------------------------------------
// Name:    read
// Purpose: This file has not been opened and therefore its contents cannot be
//          read into memory. Throw a warning and do nothing
//------------------------------------------------------------------------------
void nemesis::ClosedState::read(File* file)
{
  // TODO: Pass an exception to be logged and return control
}


//------------------------------------------------------------------------------
// Name:    write
// Purpose: This file has not been opened and therefore nothing can be written
//          to it. Throw a warning and do nothing
//------------------------------------------------------------------------------
void nemesis::ClosedState::write(File* file)
{
  // TODO: Pass an exception to be logged and return control
}