// input_file.h


#ifndef GUARD_input_file_h
#define GUARD_input_file_h


// Inclusions
#include "file.h"

#include <memory>
#include <string>
#include <vector>


//------------------------------------------------------------------------------
// Name:    nemesis
// Purpose: This namespace holds all aspects of the Nemesis Simulation Toolkit.
//------------------------------------------------------------------------------
namespace nemesis
{


  //----------------------------------------------------------------------------
  // Name:    InputFile
  // Purpose: This abstract class establishes the interface for all input files.
  //----------------------------------------------------------------------------
  class InputFile : public File
  {
  public:
    InputFile() { /* Does Nothing */ };

    // Functionality
    virtual void read_file(void) = 0;

  }; // !InputFile


} // !nemesis


#endif // !GUARD_input_file_h
