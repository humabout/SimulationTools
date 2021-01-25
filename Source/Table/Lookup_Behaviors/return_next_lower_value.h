// return_next_lower_value.h


#ifndef NEMESIS_RETURN_NEXT_LOWER_VALUE_H
#define NEMESIS_RETURN_NEXT_LOWER_VALUE_H


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
  // Name:    ReturnNextLowerValue
  // Purpose: This concretion only returns the field value for the next lower 
  //          value of the key, or the value of the key, if an exact match 
  //          occurs.
  //----------------------------------------------------------------------------
  class ReturnNextLowerValue : public TableLookupInterface
  {
  public:
    // Constructors
    ReturnNextLowerValue() { 
      // Does Nothing
    }
    ReturnNextLowerValue(Table* ptr)
    {
      this->table = std::shared_ptr<Table>(ptr);
    }


    // Destructor
    ~ReturnNextLowerValue()
    {
      // Does nothing
    }


    // Functionality
    virtual double lookup(std::size_t field_index,
                          double      key) const
    {
      // Getting the index of the next lower, or exact match
      std::size_t key_index = table->find(key);
      return table->Entries[key_index][field_index];      
    }


  }; // !ReturnNextLowerValue


} // !nemesis


// Forward Declaration Inclusions
#include "../table.h"


#endif // !NEMESIS_RETURN_NEXT_LOWER_VALUE_H
