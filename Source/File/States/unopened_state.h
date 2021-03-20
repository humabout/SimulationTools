// unopened_state.h


#ifndef GUARD_unopened_state_h
#define GUARD_unopened_state_h


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
  // Name:    UnopenedState
  // Purpose: This concretion represents a file that has not been opened before. 
  //          It can not be reached by any other state and transitions to either
  //          an open or failed state. Unopened files do not do anything other
  //          than open or fail to open.
  //----------------------------------------------------------------------------
  class UnopenedState : public FileState
  {
  public:
    // Constructor
    UnopenedState();

    void open(File* file) override;
    void close(File* file) override;
  };


} // !nemesis

#endif // !GUARD_unopened_state_h