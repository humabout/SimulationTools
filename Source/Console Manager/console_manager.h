// console_manager.h


#ifndef GUARD_console_manager_h
#define GUARD_console_manager_h


// Inclusions
#include <iostream>
#include <string>
#include <vector>


//------------------------------------------------------------------------------
// Name:    nemesis
// Purpose: This namespace holds all aspects of the Nemesis Simulation Toolkit.
//------------------------------------------------------------------------------
namespace nemesis
{


  //----------------------------------------------------------------------------
  // Name:    ConsoleManager
  // Purpose: This is a collection of globally available functions that govern
  //          how the simulation sends and recieves information to and from the 
  //          console AKA the user.
  //
  //          These are contained in a namespace that is named like a class to
  //          denote that these are conceptually grouped and related, and may
  //          rely on "private" functions and variables. Privacy is attained by
  //          using anonymous namespaces within ConsoleManager.
  //
  // Usage:   Use these functions the way you would use any static method:
  //              nemesis::ConsoleManager::print_message("foo");
  //----------------------------------------------------------------------------
  namespace ConsoleManager
  {
// Public:
    // Functionality
    static void print_message(std::string message);
    static void new_line(void);
    static int menu(std::string              message,
                    std::vector<std::string> menu_options);
// Private:
    namespace
    {
      int INVALID_INPUT = -666;
    }
  } // !ConsoleManager


} // !nemesis


#endif // !GUARD_console_manager_h
