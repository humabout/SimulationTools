// unopened_state.cpp


// Inclusions
#include "unopened_state.h"



//------------------------------------------------------------------------------
// Name:    UnopenedState
// Purpose: Default Constructor. This class has no variables to initialize.
//------------------------------------------------------------------------------
nemesis::UnopenedState::UnopenedState()
{

}


//------------------------------------------------------------------------------
// Name:    open
// Purpose: 
//------------------------------------------------------------------------------
void nemesis::UnopenedState::open(File* file)
{
  // Open and validate the file stream. If something went wrong, try again and 
  // see if that fixed it.
  file->do_open(); 

  // Otherwise, ask the user what to do and then do it.
  if (file->FileStream.is_open())
  {
    // The file is open! Yay!
    file->initialize();
    file->set_state(type::opened);
  } 
  else
  {
    // Request user do something
    std::string message = "\nFile failed to open: " + file->Directory.get() + file->Name + ".";
    std::vector<std::string> menu_options({ "Proceed without saving","Retry","Exit" });
    int user_input = 0; // TODO: Hook this up. We need a console manager to do this.

    switch (user_input)
    {
    case 1: // Proceed Without Saving
      file->set_state(type::failed);
      break;
    case 2: // Retry
      open(file);
      break;
    case 3: // Exit Gracefully
      // TODO: Send warning to error log to log exit request.
      std::exit(0);
    default:
      // Invalid result. This should never be reached.
      // TODO: Send warning to error log
    } // switch (user_input)
  } // !file->FileStream.is_open()
}


//------------------------------------------------------------------------------
// Name:    close
// Purpose: This file has not been opened and therefore cannot be closed. Throw
//          a warning for logging, but otherwise do nothing.
//------------------------------------------------------------------------------
void nemesis::UnopenedState::close(File* file)
{
  // TODO: Pass an exception to be logged and return control
}