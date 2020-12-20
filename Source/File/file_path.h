// file_path.h


#ifndef FILE_PATH_H
#define FILE_PATH_H


// Inclusions
#include <string>
#include <Windows.h>


//------------------------------------------------------------------------------
// Name:    file
// Purpose: This namespace holds all classes, functions, and variables related
//          to creating, opening, reading, writing, or otherwise manipulating
//          files.
//------------------------------------------------------------------------------
namespace file
{


  //----------------------------------------------------------------------------
  // Name:    FilePath
  // Purpose: This class encapsulates a file path and pairs it with functions
  //          that check and validate it.
  // Notes:   This class only functions in a Windows environment. Future plans
  //          are to make it work in linux, as well. OSX functionality is 
  //          extremely low priority.
  //----------------------------------------------------------------------------
  class FilePath
  {
  public:
    // Validity Enum Class
    enum class validity
    {
      valid          = 0,
      invalid        = 1,
      does_not_exist = 2
    }; // !validity

    // Constructor
    FilePath(std::string path)
    {
      this->Path = fixSlashes(path);
      this->validate();
    }

    // Destructor

    // Accessor
    std::string operator() (void) const
    {
      return Path;
    }

    bool is_valid(void) const
    {
      switch (validity_flag)
      {
      case validity::valid:
        return true;
      default:
        return false;
      }
    }

    validity path_validity(void) const
    {
      return validity_flag;
    }

    // Validation
    void validate(void);

  private:
    // Path
    std::string Path;

    // Metadata
    validity validity_flag;

    // Functionality
    std::string fixSlashes(const std::string& path) const
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


    void createPath(void); // MAKE NEW DIRECTORIES SO PATH IS VALID

  }; // !FilePath


} // !file


#endif // !FILE_PATH_H
