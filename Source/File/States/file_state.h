// file_state.h


#ifndef GUARD_file_state_h
#define GUARD_file_state_h


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
  // Name:    FileState
  // Purpose: This abstract class declares the interface for file state classes
  //          and enables the state pattern. Its children implement this pattern
  //          for the File class and its children and form a state machine.
  //----------------------------------------------------------------------------
  class FileState
  {
  public:
    // Typedef
    typedef std::shared_ptr<FileState> pointer;
    enum class type
    {
      unopened = 0, // Can transit to opened or failed
      opened   = 1, // Can transit to closed
      closed   = 2, // Can transit to opened
      failed   = 3  // Does not transit
    }; // FileState::type

    // Constructor
    FileState() {};

    // Factory
    static FileState::pointer create(type state_type);

    // Functionality
    virtual void open(File* file) = 0;
    virtual void close(File* file) = 0;


  }; // !FileState


} // !nemesis


// Forward Declaration Inclusion
#include "../file.h"


#endif // !GUARD_file_state_h
