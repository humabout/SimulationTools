// return_value_at_boundary.h


#ifndef NEMESIS_RETURN_VALUE_AT_BOUNDARY_H
#define NEMESIS_RETURN_VALUE_AT_BOUNDARY_H


// Inclusion
#include <memory>
#include <vector>
#include "table_boundary_interface.h"


//------------------------------------------------------------------------------
// Name:    nemesis
// Purpose: This namespace holds all aspects of the Nemesis Simulation Toolkit.
//------------------------------------------------------------------------------
namespace nemesis
{


  //----------------------------------------------------------------------------
  // Name:    ReturnValueAtBoundary
  // Purpose: This concretion returns a preset value when querried.
  //----------------------------------------------------------------------------
  class ReturnValueAtBoundary : public TableBoundaryInterface
  {
  public:
    // Constructors
    ReturnValueAtBoundary() = delete;
    ReturnValueAtBoundary(Table* ptr)
    {
      table = Table::pointer(ptr);
    }


    // Destructor
    ~ReturnValueAtBoundary()
    {
      // Does Nothing
    }


    // Functionality
    double lookup(std::size_t index,
                  double      key) const
    {
      std::vector<double> return_data;
      if (key < table->Keys.front())
      {
        return_data = table->Entries.front();
      }
      if (key > table->Keys.back())
      {
        return_data = table->Entries.back();
      }
      else
      {
        throw std::runtime_error("Fatal Error: Non-boundary value requested from boundary behavior class.");
      }

      return return_data[index];
    }


  }; // !ReturnValueAtBoundary


} // !nemesis



#endif // !NEMESIS_RETURN_BOUNDARY_VALUE_H
