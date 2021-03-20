// file_init_state.h


#ifndef GUARD_file_init_state_h
#define GUARD_file_init_state_h


// Inclusions
#include <memory>


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
  // Name:    FileInitState
  // Purpose: This abstract class establishes the interface for file 
  //          initialization states and fascilitates the state pattern.
  //----------------------------------------------------------------------------
  class FileInitState
  {
  public:
    // Enums and Typedefs
    typedef std::shared_ptr< FileInitState > pointer;
    enum class type
    {
      uninitialized = 0,
      initialized = 1
    }; // !type

    // Constructor
    FileInitState();

    // Factory
    static FileInitState::pointer create(type new_state);

    // Functionality
    virtual void initialize(File* file) = 0;


  }; // !FileInitState


} // !nemesis


// Forward Declaration Inclusions
#include "../../file.h"


#endif // !GUARD_file_init_state_h
