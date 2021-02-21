// file_path.h


#ifndef FILE_PATH_H
#define FILE_PATH_H


// Inclusions
#include <string>
#include <vector>
#include <Windows.h>



namespace nemesis
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
      inaccessible   = 2,
      does_not_exist = 3
    }; // !validity

    // Constructor
    FilePath();
    FilePath(std::string path);

    // Accessor
    std::string get(void) const;
    bool is_valid(void) const;
    validity path_validity(void) const;

    // Mutator
    void set(std::string path);

    // Functionality
    void create_path(void);
    void validate(void);

  private:
    // Path
    std::string Path;

    // Metadata
    validity Validity_Flag;

    // Functionality
    std::string fix_slashes(const std::string& path) const;
    std::vector<std::string> get_subdirectories(const std::string& path) const;


  }; // !FilePath


} // !file


#endif // !FILE_PATH_H
