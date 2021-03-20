// uninitialized_state.h


#ifndef GUARD_uninitialized_state_h
#define GUARD_uninitialized_state_h


// Inclusions
#include "file_init_state.h"


//------------------------------------------------------------------------------
// Name:    nemesis
// Purpose: This namespace holds all aspects of the Nemesis Simulation Toolkit.
//------------------------------------------------------------------------------
namespace nemesis
{


  //----------------------------------------------------------------------------
  // Name:    UninitializedState
  // Purpose: This concretion represents a file that has been initialized. It
  //          does not transition to any other state.
  // Note:    This class is so light it's not really worth a making separate 
  //          source file
  //----------------------------------------------------------------------------
  class UninitializedState : public FileInitState
  {
  public:
    // Constructor
    UninitializedState() { /* Nothing to initialize */ };

    // Functionality
    void initialize(File* file) { file->do_initialize(); };


  }; // !InitializedState



} // !nemesis


#endif // !GUARD_uninitialized_state_h
