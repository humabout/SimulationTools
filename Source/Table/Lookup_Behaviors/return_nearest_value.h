// return_nearest_value.h


#ifndef NEMESIS_RETURN_NEAREST_VALUE_H
#define NEMESIS_RETURN_NEAREST_VALUE_H


// Inclusions
#include <cstddef>
#include <memory>
#include <stdexcept>
#include "../table_type_definitions.h"
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
  // Name:    ReturnNearestValue
  // Purpose: This concretion only returns the field value for the closest value
  //          of the key, or the value of the key, if an exact match occurs.
  //----------------------------------------------------------------------------
  class ReturnNearestValue : public TableLookupInterface
  {
  public:
    // Constructors
    ReturnNearestValue() = delete;
    ReturnNearestValue(Table* ptr)
    {
      this->table = std::shared_ptr<Table>(ptr);
    }


    // Destructor
    ~ReturnNearestValue()
    {
      // Does Nothing
    }


    // Functionality
    double lookup(std::size_t field_index,
                  double      key) const
    {
      // Getting the index of the next lower, or exact match
      std::size_t key_index = table->find(key);

      // Check if this is exact. If so just return this.
      if (table->Keys[key_index] == key)
      {
        return table->Entries[key_index][field_index];
      }

      // Since the returned value was the next lower value, we need to next 
      // higher value so we can find which is closer to the key provided. If
      // The key is halfway between two values, return the lower one.
      double key_lo = table->Keys[key_index];
      double key_hi = table->Keys[key_index + 1];
      if (abs(key - key_lo) <= abs(key - key_hi))
      {
        return table->Entries[key_index][field_index];
      }
      else
      {
        return table->Entries[key_index + 1][field_index];
      }
    }


  }; // !ReturnClosestValue


} // !nemesis


// Forward Declaration Inclusions
#include "../table.h"


#endif // !NEMESIS_RETURN_NEAREST_VALUE_H
