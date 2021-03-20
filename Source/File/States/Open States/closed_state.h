// closed_state.h


#ifndef GUARD_closed_state_h
#define GUARD_closed_state_h


// Inclusions
#include "file_open_state.h"


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
  // Name:    ClosedState
  // Purpose: This concretion represents a file that is not currently open. It
  //          can be reached from the open state and transitions to either open
  //          or failed state.
  //----------------------------------------------------------------------------
  class ClosedState : public FileOpenState
  {
  public:
    // Constructor
    ClosedState();

    void open(File* file) override;
    void close(File* file) override;
  };


} // !nemesis

#endif // !GUARD_closed_state_h