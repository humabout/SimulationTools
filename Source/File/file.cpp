// file.cpp


// Inclusions
#include "file.h"

#include "file_path.h"
#include "States/file_state.h"


//------------------------------------------------------------------------------
// Name:    File
// Purpose: Default Constructor. This defaults to unopened with a blank path and
//          file name.
//------------------------------------------------------------------------------
nemesis::File::File()
{
  this->State = FileState::create(FileState::type::unopened);
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
  this->State = FileState::create(FileState::type::unopened);
}


//------------------------------------------------------------------------------
// Name:    open
// Purpose: This method opens the file. It is part of a state pattern and passes
//          the call to the file's state for execution.
//------------------------------------------------------------------------------
void nemesis::File::open(void)
{
  State->open(this);
}


//------------------------------------------------------------------------------
// Name:    close
// Purpose: This method closes the file. It is part of a state pattern and 
//          passes the call to the file's state for execution.
//------------------------------------------------------------------------------
void nemesis::File::close(void)
{
  State->close(this);
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
void nemesis::File::set_state(FileState::type new_state)
{
  State = FileState::create(new_state);
}

void nemesis::File::set_open_mode(std::ios_base::openmode mode)
{
  OpenMode = mode;
}

void nemesis::File::set_name(std::string name)
{
  Name = name;
  validate_filename();
}

void nemesis::File::set_directory(std::string directory)
{
  Directory.set(directory);
}