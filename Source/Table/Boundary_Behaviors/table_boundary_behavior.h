// table_boundary_behavior.h


#ifndef NEMESIS_TABLE_BOUNDARY_BEHAVIOR_H
#define NEMESIS_TABLE_BOUNDARY_BEHAVIOR_H


// Inclusions
#include <memory>
#include <cstddef>
#include "../table_type_definitions.h"


// Forward Declarations
namespace nemesis
{
  class Table;
}


//
namespace nemesis
{


  class TableBoundaryBehavior
  {
  public:
    // Aliases & Typedefs
    typedef std::shared_ptr<TableBoundaryBehavior> pointer;

    // Constructor
    TableBoundaryBehavior();

    // Factory
    static pointer create(table::at_boundary behavior,
                          Table*             owning_table);

    // Destructor
    ~TableBoundaryBehavior();

    // Functionality
    virtual float lookup(std::size_t  field,
                         float        key) const = 0;
  protected:
    // Pointer to Owning Table
    Table* table;
  };


// Forward Declaration Inclusion
#include "../table.h"


} // !nemesis

#endif // !NEMESIS_TABLE_BOUNDARY_BEHAVIOR_H