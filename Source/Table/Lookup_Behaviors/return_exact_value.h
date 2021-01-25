// return_exact_value.h


#ifndef NEMESIS_RETURN_EXACT_VALUE_H
#define NEMESIS_RETURN_EXACT_VALUE_H


// Inclusions
#include <cstddef>
#include <memory>
#include <stdexcept>
#include "table_lookup_interface.h"


// Forward Declarations
namespace nemesis
{
  class Table;
}


//------------------------------------------------------------------------------
// Name:    nemesis
// Purpose: This namespace holds all aspects of the Nemesis Simulation Toolkit.
//------------------------------------------------------------------------------
namespace nemesis
{


  //----------------------------------------------------------------------------
  // Name:    ReturnExactValue
  // Purpose: This concretion only returns data for the exact key matches and
  //          throws an error otherwise.
  //----------------------------------------------------------------------------
  class ReturnExactValue : public TableLookupInterface
  {
  public:
    // Constructors
    ReturnExactValue() {  }
    ReturnExactValue(Table* ptr)
    {
      this->table = std::shared_ptr<Table>(ptr);
    }


    // Destructor
    ~ReturnExactValue()
    {
      // Does Nothing.
    }


    // Functionality
    double lookup(std::size_t field_index,
                  double      key) const
    {
      // Getting the key index
      std::size_t key_index = table->find(key);

      // Returning the exact value requested or throwing an error if no exact
      // value was provided
      if (table->Keys[key_index] != key)
      {
        return table->Entries[key_index][field_index];
      }
      else
      {
        throw std::runtime_error("Fatal Error: Lookup value provided was not an exact value.");
      }
    }


  }; // !ReturnExactValue


} // !nemesis


// Forward Declaration Inclusions
#include "../table.h"


#endif // !NEMESIS_RETURN_EXACT_VALUE_H
