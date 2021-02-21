// file.cpp


// Inclusions
#include "file.h"
#include "file_path.h"


//------------------------------------------------------------------------------
// Name:    File
// Purpose: Default Constructor. This defaults to unopened with a blank path and
//          file name.
//------------------------------------------------------------------------------
nemesis::File::File()
{
  this->State = state::unopened;
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
  this->State = state::unopened;
}