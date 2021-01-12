// table_boundary_behavior.h


#ifndef NEMESIS_TABLE_BOUNDARY_BEHAVIOR_H
#define NEMESIS_TABLE_BOUNDARY_BEHAVIOR_H


// Inclusions
#include <initializer_list>
#include <stdexcept>
#include <string>
#include <vector>
#include <unordered_map>


// Forward Declarations
namespace nemesis
{
  template <class key_type, class field_type> class Table;
}


//
namespace nemesis
{
  template <class key_type, class field_type> class Table;


  class TableBoundaryBehavior
  {
  public:
    // Constructor
    // Destructor

    // Functionality
    template <class key_type, class field_type>
    field_type do_lookup(std::string                                    field,
                         std::initializer_list<key_type>                keys,
                         const Table<class key_type, class field_type>& table);

  private:
  };


// Forward Declaration Inclusion
#include "table.h"


} // !nemesis
 
#endif // !NEMESIS_TABLE_BOUNDARY_BEHAVIOR_H
