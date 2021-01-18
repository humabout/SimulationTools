// table_boundary_interface.h


// Inclusions
#include <memory>
#include <cstddef>
#include <stdexcept>
#include "table_boundary_interface.h"
#include "../table_type_definitions.h"

#include "return_zero_at_boundary.h"
#include "return_value_at_boundary.h"


//------------------------------------------------------------------------------
// Name:    Table
// Purpose: Default Constructor
//------------------------------------------------------------------------------
nemesis::TableBoundaryInterface::TableBoundaryInterface()
{
  this->table = nullptr;
}


//------------------------------------------------------------------------------
// Name:    Table
// Purpose: Constructor Overload
//------------------------------------------------------------------------------
nemesis::TableBoundaryInterface::TableBoundaryInterface(Table* ptr)
{
  this->table = Table::pointer(ptr);
}


//------------------------------------------------------------------------------
// Name:    ~Table
// Purpose: Destructor. This object owns nothing and deletes nothing.
//------------------------------------------------------------------------------
nemesis::TableBoundaryInterface::~TableBoundaryInterface()
{
  // Does Nothing
}


//------------------------------------------------------------------------------
// Name:    create
// Purpose: Factory method for obtaining new boundary behaviors.
//------------------------------------------------------------------------------
nemesis::TableBoundaryInterface::pointer nemesis::TableBoundaryInterface::create(table::at_boundary behavior,
                                                                                 Table*             ptr)
{
  switch (behavior)
  {
  case table::at_boundary::cap_at_end_value:
    return TableBoundaryInterface::pointer( new ReturnValueAtBoundary(ptr) );
  case table::at_boundary::return_zero:
    return TableBoundaryInterface::pointer( new ReturnZeroAtBoundary(ptr) );
  case table::at_boundary::linear_extrapolation:
  default:
    throw std::runtime_error("Fatal Error: Invalid boundary behavior provided.");
    return TableBoundaryInterface::pointer( nullptr );
  }
}