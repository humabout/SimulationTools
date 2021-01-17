// table_boundary_behavior.cpp


// Inclusions
#include <memory>
#include <stdexcept>
#include "../table_type_definitions.h"
#include "table_boundary_behavior.h"

//------------------------------------------------------------------------------
// Name:    Table
// Purpose: Default Constructor
//------------------------------------------------------------------------------
nemesis::TableBoundaryBehavior::TableBoundaryBehavior()
{
  table = nullptr;
}


//------------------------------------------------------------------------------
// Name:    ~Table
// Purpose: Destructor. This object owns nothing and deletes nothing.
//------------------------------------------------------------------------------
nemesis::TableBoundaryBehavior::~TableBoundaryBehavior()
{
  // Does Nothing
}


//------------------------------------------------------------------------------
// Name:    create
// Purpose: Factory method for creating specific boundary behavior types.
//------------------------------------------------------------------------------
nemesis::TableBoundaryBehavior::pointer nemesis::TableBoundaryBehavior::create(table::at_boundary behavior,
                                                                               Table*             owning_table)
{
  switch (behavior)
  {
  case table::at_boundary::cap_at_end_value:
  case table::at_boundary::return_zero:
  case table::at_boundary::linear_extrapolation:
  default:
    throw std::runtime_error("Fatal Error: Unknown boundary behavior type encountered.");
  };
}