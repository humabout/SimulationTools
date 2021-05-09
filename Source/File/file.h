// file.h


#ifndef GUARD_file_h
#define GUARD_file_h


// Inclusions
#include <fstream>
#include <memory>
#include <string>

#include "file_path.h"
#include "States/Open States/file_open_state.h"
#include "States/Initialization States/file_init_state.h"


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

    // Destructor
    virtual ~File();

    // Accessors
    std::string name(void) const;
    std::string directory(void) const;

    // Mutators
    void set_name(std::string name);
    void set_directory(std::string directory);

    // Functionality
    void close(void);
    void initialize(void);
    void open(void);
    void read(void);
    void write(void);

  protected:
    std::fstream FileStream;

    // Accessors
    std::ios_base::openmode open_mode(void) const;

    // Mutators
    void set_open_mode(std::ios_base::openmode mode);

    // Functionality Implementations
    virtual void do_initialize(void) = 0;
    virtual void do_open(void) = 0;
    virtual void do_close(void) = 0;
    virtual void do_read(void) = 0;
    virtual void do_write(void) = 0;

    // State Helper Functionality
    virtual void validate_filename(void) {/* TODO: Need to make this */ };
    void set_init_state(FileInitState::type new_state);

  private:
    FilePath                Directory;
    std::string             Name;
    std::ios_base::openmode OpenMode;
    FileOpenState::pointer  OpenState;
    FileInitState::pointer  InitState;

    // State Helper Functionality
    void set_open_state(FileOpenState::type new_state);

    // State classes are friends
    friend class ClosedState;
    friend class FileState;
    friend class OpenedState;
    friend class UninitializedState;

  }; // !File


} // !nemesis


#endif // !GUARD_file_h
