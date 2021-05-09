// output_file.h


#ifndef GUARD_output_file_h
#define GUARD_output_file_h


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
  // Name:    OutputFile
  // Purpose: This abstract class establishes the interface for all output files
  //----------------------------------------------------------------------------
  class OutputFile : public File
  {
  public:
    OutputFile() { /* Does Nothing */ };

    // Functionality
    virtual void write(void) = 0;

  }; // !InputFile


} // !nemesis


#endif // !GUARD_output_file_h
