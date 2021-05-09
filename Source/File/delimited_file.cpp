// delimited_file.cpp


// Inclusions
#include "delimited_file.h"


//------------------------------------------------------------------------------
// Name:    DelimitedFile
// Purpose: Default Constructor. This defaults to unopened with a blank path and
//          file name, and white space as the delimiter.
//------------------------------------------------------------------------------
nemesis::DelimitedFile::DelimitedFile()
{
  set_delimiter(delimiters::WHITE_SPACE);
}


//------------------------------------------------------------------------------
// Name:    DelimitedFile
// Purpose: Constructor Override. This defaults to unopened with a blank path and
//          file name. The delimiter is set from the arguments.
//------------------------------------------------------------------------------
nemesis::DelimitedFile::DelimitedFile(delimiter delim)
{
  set_delimiter(delim);
}


//------------------------------------------------------------------------------
// Name:    DelimitedFile
// Purpose: Constructor Override. This sets the directory and name for the file
//          and defaults the delimiter to white space.
//------------------------------------------------------------------------------
nemesis::DelimitedFile::DelimitedFile(std::string directory,
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
nemesis::DelimitedFile::DelimitedFile(std::string directory,
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
void nemesis::DelimitedFile::add_delimiter(delimiter delim)
{
  Delimiters += delim;
}


//------------------------------------------------------------------------------
// Name:    reset_delimiters
// Purpose: This method clears out all stored delimiters
//------------------------------------------------------------------------------
void nemesis::DelimitedFile::reset_delimiters(void)
{
  Delimiters.clear();
}


//------------------------------------------------------------------------------
// Name:    set_delimiter
// Purpose: This method assigns one or more delimtiers as the list of delimiters
//          overwriting whatever is currently stored.
//------------------------------------------------------------------------------
void nemesis::DelimitedFile::set_delimiter(delimiter delim)
{
  reset_delimiters();
  add_delimiter(delim);
}


//------------------------------------------------------------------------------
// Name:    parse_line
// Purpose: 
//------------------------------------------------------------------------------
nemesis::DelimitedFile::file_line nemesis::DelimitedFile::parse_line(std::string line) const
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
// Name:    do_initialize
// Purpose: Implements initializing the file. In this case, there is nothing to
//          do on initialization.
//------------------------------------------------------------------------------
void nemesis::DelimitedFile::do_initialize(void)
{
  // Do Nothing
}


//------------------------------------------------------------------------------
// Name:    do_close
// Purpose: Implements closing the file.
//------------------------------------------------------------------------------
void nemesis::DelimitedFile::do_close(void)
{
  FileStream.close();
}


//------------------------------------------------------------------------------
// Name:    do_open
// Purpose: Implements opening the file.
//------------------------------------------------------------------------------
void nemesis::DelimitedFile::do_open(void)
{
  FileStream.open(directory() + name());
}


//------------------------------------------------------------------------------
// Name:    do_read
// Purpose: Implements reading the file's contents into memory.
//------------------------------------------------------------------------------
void nemesis::DelimitedFile::do_close(void)
{
  // TODO: Make this funciton
}


//------------------------------------------------------------------------------
// Name:    do_write
// Purpose: Implements writing to the file.
//------------------------------------------------------------------------------
void nemesis::DelimitedFile::do_close(void)
{
  // TODO: Make this funciton
}


//==============================================================================
// GETTERS
//==============================================================================
nemesis::DelimitedFile::file_content nemesis::DelimitedFile::content(void) const
{
  return Content;
}
nemesis::DelimitedFile::delimiter nemesis::DelimitedFile::delimiters(void) const
{
  return Delimiters;
}