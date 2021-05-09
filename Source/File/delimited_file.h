// delimited_file.h


#ifndef GUARD_delimited_file_h
#define GUARD_delimited_file_h


// Inclusions
#include "input_file.h"

#include <string>
#include <vector>


//------------------------------------------------------------------------------
// Name:    nemesis
// Purpose: This namespace holds all aspects of the Nemesis Simulation Toolkit.
//------------------------------------------------------------------------------
namespace nemesis
{


  //----------------------------------------------------------------------------
  // Name:    delimiters
  // Purpose: This namespace holds a set of constants used to define delimiters
  //----------------------------------------------------------------------------
  namespace delimiters
  {
    // Static constants for defining special characters
    static const std::string COMMA       = ",";
    static const std::string SPACE       = " ";
    static const std::string TAB         = "\t";
    static const std::string WHITE_SPACE = TAB + SPACE;


  } // !delimiters

  //----------------------------------------------------------------------------
  // Name:    DelimitedInputFile
  // Purpose: This abstract class establishes the interface for all delimited
  //          input files. It stores a list of delimiters and parses a a file
  //          by these delimiters. It stores the content of the file in a vector
  //          of vectors of strings - essentially a 2x2 table of strings, with
  //          rows representing lines and columns representing delimited 
  //          entries.
  //----------------------------------------------------------------------------
  class DelimitedFile : public File
  {
  public:
    // Typedefs
    typedef std::vector< std::string > file_line;
    typedef std::vector < file_line >  file_content;
    typedef std::string                delimiter;

    // Constructors
    DelimitedFile();
    DelimitedFile(delimiter delim);
    DelimitedFile(std::string directory,
                  std::string name);
    DelimitedFile(std::string directory,
                  std::string name,
                  delimiter   delim);

    // Accessors
    file_content content(void) const;
    delimiter delimiters(void) const;

    // Functionality
    void add_delimiter(delimiter delim);
    void reset_delimiters(void);
    void set_delimiter(delimiter delim);

  protected:
    delimiter    Delimiters;
    file_content Content;


  private:
    // Functionality Implementations
    virtual void do_close(void);
    virtual void do_open(void);
    virtual void do_initialize(void);
    virtual void do_read(void);
    virtual void do_write(void);

    // Helper Functions
    file_line parse_line(std::string line) const;

  }; // !DelimitedFile


} // !nemesis


#endif // !GUARD_delimited_file_h
