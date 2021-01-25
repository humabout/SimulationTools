// table_lookup_interface.cpp


// Inclusions
#include <memory>
#include <cstddef>
#include <stdexcept>
#include "table_lookup_interface.h"
#include "../table_type_definitions.h"
#include "return_exact_value.h"
#include "return_next_lower_value.h"
#include "return_next_higher_value.h"
#include "return_nearest_value.h"
#include "return_linear_interpolation.h"




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
    return pointer(new ReturnExactValue(ptr));
  case table::lookup::linear_interpolation:
    return pointer(new ReturnLinearInterpolation(ptr));
  case table::lookup::nearest_value:
    return pointer(new ReturnNearestValue(ptr));
  case table::lookup::next_higher_value:
    return pointer(new ReturnNextHigherValue(ptr));
  case table::lookup::next_lower_value:
    return pointer(new ReturnNextLowerValue(ptr));
  //case table::lookup::spline_interpolation:
    // This is a future goal to include. Linear interpolation is faster and 
    // usually sufficient given good coverage of data in the table.
  default:
    throw std::runtime_error("");
    return TableLookupInterface::pointer(nullptr);
  }
}