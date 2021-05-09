// failed_state.h


#ifndef GUARD_failed_state_h
#define GUARD_failed_state_h


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
  // Name:    FailedState
  // Purpose: This concretion represents a file that has failed to properly 
  //          open. It can be reached via the unopened state and does not 
  //          transition to any other state - one a file is failed, it stays 
  //          failed. Failed files do not do anything except pass warnings when
  //          something tries to make it do something. They do not crash a sim.
  //----------------------------------------------------------------------------
  class FailedState : public FileOpenState
  {
  public:
    // Constructor
    FailedState();

    // Fucntionality
    void close(File* file) override;
    void open(File* file) override;
    void read(File* file) override;
    void write(File* file) override;

  }; // !FailedState


} // !nemesis



// Forward Declaration Inclusions
#include "../../file.h"


#endif // !GUARD_failed_state_h
