// delimited_input_file.cpp


// Inclusions
#include "delimited_input_file.h"


//------------------------------------------------------------------------------
// Name:    DelimitedInputFile
// Purpose: Default Constructor. This defaults to unopened with a blank path and
//          file name, and white space as the delimiter.
//------------------------------------------------------------------------------
nemesis::DelimitedInputFile::DelimitedInputFile()
{
  set_delimiter(delimiters::WHITE_SPACE);
}


//------------------------------------------------------------------------------
// Name:    DelimitedInputFile
// Purpose: Constructor Override. This defaults to unopened with a blank path and
//          file name. The delimiter is set from the arguments.
//------------------------------------------------------------------------------
nemesis::DelimitedInputFile::DelimitedInputFile(delimiter delim)
{
  set_delimiter(delim);
}


//------------------------------------------------------------------------------
// Name:    DelimitedInputFile
// Purpose: Constructor Override. This sets the directory and name for the file
//          and defaults the delimiter to white space.
//------------------------------------------------------------------------------
nemesis::DelimitedInputFile::DelimitedInputFile(std::string directory,
                                                std::string name)
{
  set_directory(directory);
  set_name(name);
}


//------------------------------------------------------------------------------
// Name:    DelimitedInputFile
// Purpose: Constructor Override. This sets the directory and name for the file
//          and sets the delimiter, as well.
//------------------------------------------------------------------------------
nemesis::DelimitedInputFile::DelimitedInputFile(std::string directory,
                                                std::string name,
                                                delimiter   delim)
{
  set_directory(directory);
  set_name(name);
  set_delimiter(delim);
}


//------------------------------------------------------------------------------
// Name:    add_delimiter
// Purpose: This method adds additional delimiters to this file's list of 
//          delimiters.
//------------------------------------------------------------------------------
void nemesis::DelimitedInputFile::add_delimiter(delimiter delim)
{
  Delimiters += delim;
}


//------------------------------------------------------------------------------
// Name:    reset_delimiters
// Purpose: This method clears out all stored delimiters
//------------------------------------------------------------------------------
void nemesis::DelimitedInputFile::reset_delimiters(void)
{
  Delimiters.clear();
}


//------------------------------------------------------------------------------
// Name:    set_delimiter
// Purpose: This method assigns one or more delimtiers as the list of delimiters
//          overwriting whatever is currently stored.
//------------------------------------------------------------------------------
void nemesis::DelimitedInputFile::set_delimiter(delimiter delim)
{
  reset_delimiters();
  add_delimiter(delim);
}


//------------------------------------------------------------------------------
// Name:    parse_line
// Purpose: 
//------------------------------------------------------------------------------
nemesis::DelimitedInputFile::file_line nemesis::DelimitedInputFile::parse_line(std::string line) const
{
  file_line fields_out;
  std::string remaining_line = line;
  while (remaining_line.find_first_of(Delimiters) != std::string::npos)
  {
    std::size_t field_length = remaining_line.find_first_of(Delimiters);

    fields_out.push_back(remaining_line.substr(0, field_length) );
    remaining_line.erase(0, field_length + 1);
  }
  fields_out.push_back(remaining_line);
  
  return fields_out;
}


//------------------------------------------------------------------------------
// Name:    read_file
// Purpose: 
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Name:    do_initialize
// Purpose: Implements initializing the file. In this case, there is nothing to
//          do on initialization.
//------------------------------------------------------------------------------
void nemesis::DelimitedInputFile::do_initialize(void)
{
  // Do Nothing
}


//------------------------------------------------------------------------------
// Name:    do_open
// Purpose: Implements opening the file.
//------------------------------------------------------------------------------
void nemesis::DelimitedInputFile::do_open(void)
{
  FileStream.open(directory() + name());
}


//------------------------------------------------------------------------------
// Name:    do_close
// Purpose: Implements closing the file.
//------------------------------------------------------------------------------
void nemesis::DelimitedInputFile::do_close(void)
{
  FileStream.close();
}


//==============================================================================
// GETTERS
//==============================================================================
nemesis::DelimitedInputFile::file_content nemesis::DelimitedInputFile::content(void) const
{
  return Content;
}
nemesis::DelimitedInputFile::delimiter nemesis::DelimitedInputFile::delimiters(void) const
{
  return Delimiters;
}