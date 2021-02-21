// file_state.h


#ifndef NEMESIS_FILE_STATE_H
#define NEMESIS_FILE_STATE_H


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

    // Constructor
    FileState() {};

    // Functionality
    virtual void open(File* file) = 0;
    virtual void close(File* file) = 0;


  }; // !FileState


} // !nemesis


// Forward Declaration Inclusion
#include "../file.h"


#endif // !NEMESIS_FILE_STATE_H
