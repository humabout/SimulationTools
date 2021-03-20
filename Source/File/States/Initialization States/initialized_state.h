// initialized_state.h


#ifndef GUARD_initialized_state_h
#define GUARD_initialized_state_h


// Inclusions
#include "file_init_state.h"


//------------------------------------------------------------------------------
// Name:    nemesis
// Purpose: This namespace holds all aspects of the Nemesis Simulation Toolkit.
//------------------------------------------------------------------------------
namespace nemesis
{


  //----------------------------------------------------------------------------
  // Name:    InitializedState
  // Purpose: This concretion represents a file that has been initialized. It
  //          does not transition to any other state.
  // Note:    This class is so light it's not really worth a making separate 
  //          source file
  //----------------------------------------------------------------------------
  class InitializedState : public FileInitState
  {
  public:
    // Constructor
    InitializedState() { /* Nothing to initialize */ };

    // Functionality
    void initialize(File* file) { /* Nothing to do here */ };


  }; // !InitializedState




} // !nemesis


#endif // !GUARD_initialized_state_h
