// table_lookup_behavior.h


#ifndef NEMESIS_TABLE_LOOKUP_BEHAVIOR_H
#define NEMESIS_TABLE_LOOKUP_BEHAVIOR_H


// Inclusions
#include <memory>
#include "../table_type_definitions.h"

//
namespace nemesis
{


  class TableLookupBehavior
  {
  public:
    // Aliases & Typedefs
    typedef std::shared_ptr<TableLookupBehavior> pointer;

    // Constructors
    TableLookupBehavior();

    // Factory
    static pointer create(table::lookup behavior, 
                          Table*        owning_table);

    // Destructors
    ~TableLookupBehavior();

    // Functionality
    float lookup(std::size_t index,
                 float       key) const;

  protected:
    // Pointer to Owning Table
    Table* table;

  };


  // Forward Declaration Inclusion
#include "table.h"



} // !nemesis

#endif // !NEMESIS_TABLE_LOOKUP_BEHAVIOR_H
