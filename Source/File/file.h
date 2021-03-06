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
  // Purpose: This abstract class manages a file. It is responsible for 
  //          validating file paths and names and maintaining an appropriate 
  //          file stream to the file. It uses a template pattern to defer 
  //          implementation details to child classes, who are expected to 
  //          define exactly what it means to open, close, and validate files.
  //          It also has opened/closed/failed state that governs how calls get 
  //          executed. This is to avoid crashing the sim while still retaining 
  //          a log that something happened.
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
    void close(void);
    void open(void);

  protected:
    FileState::pointer State;
    std::fstream       FileStream;

    // Accessors
    std::ios_base::openmode open_mode(void) const;

    // Mutators
    void set_open_mode(std::ios_base::openmode mode);

  private:
    FilePath                Directory;
    std::string             Name;
    std::ios_base::openmode OpenMode;

    // Helper Functionality
    void set_state(FileState::type new_state);

    // Functionality Implementations
    virtual void do_open(void) = 0;
    virtual void do_close(void) = 0;

    // Helper Functionality
    virtual void validate_filename(void) = 0;

    // State classes are friends
    friend class FileState;

  }; // !File


} // !nemesis


#endif // !NEMESIS_FILE_H
