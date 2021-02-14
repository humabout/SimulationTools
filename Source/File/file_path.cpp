// file_path.cpp


// Inclusions
#include <string>
#include <Windows.h>
#include "file_path.h"


//------------------------------------------------------------------------------
// Name:    FilePath
// Purpose: Constructor. This creates a filepath object from a string containing
//          the file path. In doing os, it ensure that the correct slashes are 
//          used and determines the validity of the path itself.
//------------------------------------------------------------------------------
nemesis::FilePath::FilePath(std::string path)
{
  this->Path = fix_slashes(path);
  this->validate();
}


//------------------------------------------------------------------------------
// Name:    createPath
// Purpose: This method creates all directories to needed to make the path valid
//          if the path itself has no syntactical errors and the path does not
//          yet exist. If it does exist, nothing happens.
//
//          There is an implicit assumption that the path is either valid or 
//          does not exist. This should be checked before calling, and can be 
//          used for error handling.
//------------------------------------------------------------------------------
void nemesis::FilePath::create_path(void)
{
  bool successfully_created = CreateDirectoryA(Path.c_str(), NULL);
  if (successfully_created)
  {
    // No need to do anything special
  }
  else
  {
    // Directory creation failed. Let's see why
    DWORD last_err = GetLastError();
    std::vector<std::string> subdirectories;
    switch (last_err)
    {
    case ERROR_ALREADY_EXISTS:
      // No need to do anything special, since this was called to create the
      // directory and it is present.

      // TODO:  Consider passing a warning to an error logger. Beware of 
      //        feedback loops if the error is coming from the log file 
      //        path!
      break;
    case ERROR_PATH_NOT_FOUND:
      // One or more intermediate directories are not found. We need to find
      // and make those paths.
      subdirectories = get_subdirectories(Path);
      for (std::vector<std::string>::iterator dir = subdirectories.begin();
           dir != subdirectories.end();
           ++dir)
      {
        CreateDirectoryA((*dir).c_str(), NULL);
      }
      break;
    default:
      // How did we even get here? THROW AN ERROR AND RUN AWAY SCREEMING
    }
  }

  // Update validity status
  validate();
}


//------------------------------------------------------------------------------
// Name:    fix_slashes
// Purpose: This method goes through a path name and makes sure that all slashes
//          are correct for Windows to recognize them. This means backslashes
//          and not forward slashes, plus the trailing slash on the last 
//          directory.
//------------------------------------------------------------------------------
std::string nemesis::FilePath::fix_slashes(const std::string& path) const
{
  std::string working_path(path);

  // Change any forward slashes to backslashes
  while (working_path.find("/") != std::string::npos)
  {
    size_t position = working_path.find("/");
    working_path.replace(position, 1, "\\");
  }

  // Ensure the path ends in a backslash
  if (path.back() != *"\\")
  {
    working_path.append("\\");
  }

  return working_path;
}


//------------------------------------------------------------------------------
// Name:    get_subdirectories
// Purpose: This method goes through a path name, extracts each subdirectory's
//          name, and returns them all in a vector of strings.
//------------------------------------------------------------------------------
std::vector<std::string> nemesis::FilePath::get_subdirectories(const std::string& path) const
{
  // Splice the path by backslashes 
  std::vector<std::string> dirs;
  while (path.find("\\") != std::string::npos)
  {
    // Gets all but last directory
    size_t position = path.find("\\");
    dirs.push_back(path.substr(0, position));
  }
  // Get last directory
  size_t position = path.find_last_of("\\");
  dirs.push_back(path.substr(position + 1, std::string::npos));

  return dirs;
}


//------------------------------------------------------------------------------
// Name:    is_valid
// Purpose: Checks if the path's validity flag and returns true only if it is 
//          valid. All other validity states, including does_not_exist, return
//          false.
// TODO:    Check if it should return true when the path is valid but does not
//          exist.
//------------------------------------------------------------------------------
bool nemesis::FilePath::is_valid(void) const
{
  switch (validity_flag)
  {
  case validity::valid:
    return true;
  default:
    return false;
  }
}


//------------------------------------------------------------------------------
// Name:    validate
// Purpose: This method updates the filepath's validity flag. It does this by
//          checking if the path is valid according to the Windows OS.
// NOTE:    Eventually, the plan is to include working with Linux, as well.
//------------------------------------------------------------------------------
void nemesis::FilePath::validate(void)
{
  DWORD dwAttrib = GetFileAttributesA(Path.c_str());

  if (dwAttrib & FILE_ATTRIBUTE_DIRECTORY)
  {
    // The directory exists and the path is valid
    validity_flag = validity::valid;
  }
  else if (dwAttrib == INVALID_FILE_ATTRIBUTES)
  {
    // Something is wrong with the path. Let's see what it is
    DWORD last_err = GetLastError();
    switch (last_err)
    {
    case ERROR_FILE_NOT_FOUND:
    case ERROR_PATH_NOT_FOUND:
    case ERROR_BAD_NETPATH:
      validity_flag = validity::does_not_exist;
      break;
    case ERROR_INVALID_NAME:
      validity_flag = validity::invalid;
      break;
    default:
      // Something else is wrong and the path cannot be accessed
      validity_flag = validity::inaccessible;
    }
  }
  else
  {
    // The directory does not exist
    validity_flag = validity::does_not_exist;
  }
}





//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
// GETTERS
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
std::string nemesis::FilePath::get(void) const
{
  return Path;
}
nemesis::FilePath::validity nemesis::FilePath::path_validity(void) const
{
  return validity_flag;
}
