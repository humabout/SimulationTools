// table_lookup_interface.cpp


// Inclusions
#include <memory>
#include <cstddef>
#include <stdexcept>
#include "table_lookup_interface.h"
#include "../table_type_definitions.h"




//------------------------------------------------------------------------------
// Name:    Table
// Purpose: Default Constructor
//------------------------------------------------------------------------------
nemesis::TableLookupInterface::TableLookupInterface()
{
  this->table = nullptr;
}


//------------------------------------------------------------------------------
// Name:    Table
// Purpose: Constructor Overload
//------------------------------------------------------------------------------
nemesis::TableLookupInterface::TableLookupInterface(Table* ptr)
{
  this->table = Table::pointer(ptr);
}


//------------------------------------------------------------------------------
// Name:    ~Table
// Purpose: Destructor. This object owns nothing and deletes nothing.
//------------------------------------------------------------------------------
nemesis::TableLookupInterface::~TableLookupInterface()
{
  // Does Nothing
}


//------------------------------------------------------------------------------
// Name:    create
// Purpose: Factory method for obtaining new lookup behaviors.
//------------------------------------------------------------------------------
nemesis::TableLookupInterface::pointer nemesis::TableLookupInterface::create(table::lookup behavior,
                                                                             Table*        ptr)
{
  switch (behavior)
  {
  case table::lookup::exact_value:
  case table::lookup::linear_interpolation:
  case table::lookup::nearest_value:
  case table::lookup::next_higher_value:
  case table::lookup::next_lower_value:
  //case table::lookup::spline_interpolation:
    // This is a future goal to include. Linear interpolation is faster and 
    // usually sufficient given good coverage of data in the table.
  default:
    throw std::runtime_error("");
    return TableLookupInterface::pointer(nullptr);
  }
}