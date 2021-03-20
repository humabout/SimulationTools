// file_open_state.h


#ifndef GUARD_file_open_state_h
#define GUARD_file_open_state_h


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
  // Name:    FileOpenState
  // Purpose: This abstract class declares the interface for file state classes
  //          and enables the state pattern. Its children implement this pattern
  //          for the File class and its children and form a state machine.
  //----------------------------------------------------------------------------
  class FileOpenState
  {
  public:
    // Typedef
    typedef std::shared_ptr<FileOpenState> pointer;
    enum class type
    {
      opened   = 0, // Can transit to closed
      closed   = 1, // Can transit to opened or failed
      failed   = 2  // Does not transit
    }; // FileState::type

    // Constructor
    FileOpenState();

    // Factory
    static FileOpenState::pointer create(type state_type);

    // Functionality
    virtual void open(File* file) = 0;
    virtual void close(File* file) = 0;


  }; // !FileState


} // !nemesis


// Forward Declaration Inclusion
#include "../../file.h"


#endif // !GUARD_file_open_state_h
