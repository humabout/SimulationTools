// file.h


#ifndef NEMESIS_FILE_H
#define NEMESIS_FILE_H


// Inclusions
#include <fstream>
#include <memory>
#include <string>
#include "file_path.h"
#include "States/file_state.h"


//------------------------------------------------------------------------------
// Name:    nemesis
// Purpose: This namespace holds all aspects of the Nemesis Simulation Toolkit.
//------------------------------------------------------------------------------
namespace nemesis
{


  //----------------------------------------------------------------------------
  // Name:    File
  // Purpose: This object manages a file.
  //----------------------------------------------------------------------------
  class File
  {
  public:
    // Typedefs
    typedef std::shared_ptr<File> pointer;

    // Constructors
    File();
    File(std::string directory, 
         std::string name);

    // Accessors
    std::string name(void) const;
    std::string directory(void) const;

    // Mutators
    void set_name(std::string name);
    void set_directory(std::string directory);

    // Functionality
    void open(void)
    {
      State->open(this);
    }
    void close(void)
    {
      State->close(this);
    }

  protected:
    FileState::pointer State;
    std::fstream       FileStream;

  private:
    FilePath    Directory;
    std::string Name;

    // Helper Functionality
    void set_state(FileState* new_state)
    {
      State.reset(new_state);
    }

    // Functionality Implementations
    virtual void do_open(void) = 0;
    virtual void do_close(void) = 0;

    // State classes are friends
    friend class FileState;

  }; // !File


} // !nemesis


#endif // !NEMESIS_FILE_H
