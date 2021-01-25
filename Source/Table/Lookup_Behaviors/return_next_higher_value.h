// return_next_higher_value.h


#ifndef NEMESIS_RETURN_NEXT_HIGHER_VALUE_H
#define NEMESIS_RETURN_NEXT_HIGHER_VALUE_H


// Inclusions
#include <cstddef>
#include <memory>
#include <stdexcept>
#include "../table_type_definitions.h"


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
  // Name:    ReturnNextHigherValue
  // Purpose: This concretion only returns the field value for the next higher 
  //          value of the key, or the value of the key, if an exact match 
  //          occurs.
  //----------------------------------------------------------------------------
  class ReturnNextHigherValue : public TableLookupInterface
  {
  public:
    // Constructors
    ReturnNextHigherValue() = delete;
    ReturnNextHigherValue(Table* ptr)
    {
      this->table = std::shared_ptr<Table>(ptr);
    }


    // Destructor
    ~ReturnNextHigherValue()
    {
      // Does Nothing
    }


    // Functionality
    double lookup(std::size_t field_index,
                  double      key) const
    {
      // Getting the index of the next lower, or exact match
      std::size_t key_index = table->find(key);

      // Use this to get the exact or next higher value
      if (table->Keys[key_index] == key)
      {
        return table->Entries[key_index][field_index];
      }
      else
      {
        return table->Entries[key_index + 1][field_index];
      }
    }

  }; // !ReturnNextHigherValue


} // !nemesis


// Forward Declaration Inclusions
#include "../table.h"

#endif // !NEMESIS_RETURN_NEXT_HIGHER_VALUE_H
