// table_lookup_interface.h


#ifndef NEMESIS_TABLE_LOOKUP_INTERFACE_H
#define NEMESIS_TABLE_LOOKUP_INTERFACE_H


// Inclusions
#include <cstddef>
#include <memory>
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
  // Name:    TableLookupInterface
  // Purpose: This abstract class establishes the interface for all table 
  //          lookup behaviors and enables a strategy pattern.
  //----------------------------------------------------------------------------
  class TableLookupInterface
  {
  public:
    // Typedefs
    typedef std::shared_ptr<TableLookupInterface> pointer;

    // Constructors
    TableLookupInterface();
    TableLookupInterface(Table* ptr);


    // Factory
    static pointer create(table::lookup behavior,
                          Table*        ptr);


    // Destructor
    ~TableLookupInterface();


    // Functionality
    virtual double lookup(std::size_t index,
                          double      key) const = 0;

  private:
    // Pointer to owning table object
    std::shared_ptr<Table> table;


  }; // !TableLookupInterface


} // !nemesis


// Forward Declaration Inclusions
#include "../table.h"


#endif // !NEMESIS_TABLE_LOOKUP_INTERFACE_H
