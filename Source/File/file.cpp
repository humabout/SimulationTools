// file.cpp


// Inclusions
#include "file.h"

#include "file_path.h"
#include "States/Open States/file_open_state.h"
#include "States/Initialization States/file_init_state.h"


//------------------------------------------------------------------------------
// Name:    File
// Purpose: Default Constructor. This defaults to unopened with a blank path and
//          file name.
//------------------------------------------------------------------------------
nemesis::File::File()
{
  set_open_state(FileOpenState::type::closed);
}


//------------------------------------------------------------------------------
// Name:    File
// Purpose: Constructor. This defaults to unopened and sets the path and file
//          name. The path is validated in this process.
//------------------------------------------------------------------------------
nemesis::File::File(std::string directory,
                    std::string name)
{
  this->Directory = FilePath(directory);
  this->Name      = name;

  set_open_state(FileOpenState::type::closed);
}


//------------------------------------------------------------------------------
// Name:    ~File
// Purpose: Destructor. This closes the file.
// 
//------------------------------------------------------------------------------
nemesis::File::~File()
{
  close();
}


//------------------------------------------------------------------------------
// Name:    close
// Purpose: This method closes the file. It is part of a state pattern and 
//          passes the call to the file's state for execution.
//------------------------------------------------------------------------------
void nemesis::File::close(void)
{
  OpenState->close(this);
}


//------------------------------------------------------------------------------
// Name:    initialize
// Purpose: This method prepares a file for use. It is part of a state pattern 
//          and passes the call to the file's init state for execution.
//------------------------------------------------------------------------------
void nemesis::File::initialize(void)
{
  InitState->initialize(this);
}


//------------------------------------------------------------------------------
// Name:    open
// Purpose: This method opens the file. It is part of a state pattern and passes
//          the call to the file's open state for execution.
//------------------------------------------------------------------------------
void nemesis::File::open(void)
{
  OpenState->open(this);
}


//------------------------------------------------------------------------------
// Name:    read
// Purpose: This method reads the contents of the file into memory.
//------------------------------------------------------------------------------
void nemesis::File::read(void)
{
  OpenState->read(this);
}


//------------------------------------------------------------------------------
// Name:    write
// Purpose: This method writes a string to the file
//------------------------------------------------------------------------------
void nemesis::File::write(void)
{
  OpenState->write(this);
}


//==============================================================================
// GETTERS
//==============================================================================
std::string nemesis::File::name(void) const
{
  return Name;
}

std::string nemesis::File::directory(void) const
{
  return Directory.get();
}

std::ios_base::openmode nemesis::File::open_mode(void) const
{
  return OpenMode;
}


//==============================================================================
// SETTERS
//==============================================================================
void nemesis::File::set_directory(std::string directory)
{
  Directory.set(directory);
}

void nemesis::File::set_name(std::string name)
{
  Name = name;
  validate_filename();
}

void nemesis::File::set_open_mode(std::ios_base::openmode mode)
{
  OpenMode = mode;
}

void nemesis::File::set_init_state(FileInitState::type new_state)
{
  InitState = FileInitState::create(new_state);
}

void nemesis::File::set_open_state(FileOpenState::type new_state)
{
  OpenState = FileOpenState::create(new_state);
}