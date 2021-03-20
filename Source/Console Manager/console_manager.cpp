// console_manager.cpp


// Inclusions
#include "console_manager.h"

#include <iostream>


//------------------------------------------------------------------------------
// Name:    print_message
// Purpose: This function prints a message to the console.
//------------------------------------------------------------------------------
void nemesis::ConsoleManager::print_message(std::string message)
{
  std::cout << message;
}


//------------------------------------------------------------------------------
// Name:    new_line
// Purpose: This function starts a new line on the console.
//------------------------------------------------------------------------------
void nemesis::ConsoleManager::new_line(void)
{
  std::cout << "\n";
}


//------------------------------------------------------------------------------
// Name:    menu
// Purpose: This function creates a menu of options and requests the user choose
//          one by selecting the corresponding number. It returns this number as
//          its output.
//------------------------------------------------------------------------------
int nemesis::ConsoleManager::menu(std::string              message,
                                  std::vector<std::string> menu_options)
{
  // Build list of valid inputs
  std::vector<int> valid_inputs(menu_options.size());
  std::string menu = "\nChoose one of the following:";
  for (std::size_t i = 0; i < valid_inputs.size(); i++)
  {
    valid_inputs[i] = (int)(i + 1);
    menu = menu + "\n(" + std::to_string(valid_inputs[i]) + ") " + menu_options[i];
  }
  std::cout << "\n" << message << menu;

  // Accept, validate and return input
  int input = INVALID_INPUT;
  bool is_valid = false;
  do
  {
    std::cout << "\n> ";
    std::cin  >> input;
    // Validate input
    std::size_t i = 0;
    while ( !is_valid && 
            (i < valid_inputs.size()) )
    {
      is_valid = (input == valid_inputs[i]);
      i++;
    }
  } while (!is_valid);

  return input;
}