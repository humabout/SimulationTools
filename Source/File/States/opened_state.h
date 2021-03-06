// opened_state.h


#ifndef GUARD_opened_state_h
#define GUARD_opened_state_h


// Inclusions
#include "file_state.h"


// Forward Declarations
namespace nemesis
{
  class File;
}


//------------------------------------------------------------------------------
// Name:    nemesis
// Purpose: This namespace holds all aspects of the Nemesis Simulation Toolkit.
//------------------------------------------------------------------------------
namespace nemesis
{


  //----------------------------------------------------------------------------
  // Name:    OpenedState
  // Purpose: This concretion represents a file that has been successfully 
  //          opened and is ready for use. It can be reached via the unopened or
  //          closed state and transitions to closed state.
  //----------------------------------------------------------------------------
  class OpenedState : public FileState
  {
  public:
    // Constructor
    OpenedState();

    void open(File* file) override;
    void close(File* file) override;

  }; // !FailedState


} // !nemesis



// Forward Declaration Inclusions
#include "../file.h"


#endif // !GUARD_opened_state_h
#pragma once
