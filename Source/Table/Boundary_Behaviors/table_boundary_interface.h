// table_boundary_interface.h


#ifndef NEMESIS_TABLE_BOUNDARY_INTERFACE_H
#define NEMESIS_TABLE_BOUNDARY_INTERFACE_H


// Inclusions
#include <memory>
#include <cstddef>
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
  // Name:    TableBoundaryInterface
  // Purpose: This abstract class establishes the interface for all table 
  //          boundary behaviors and enables a strategy pattern.
  //----------------------------------------------------------------------------
  class TableBoundaryInterface
  {
  public:
    // Typedefs
    typedef std::shared_ptr<TableBoundaryInterface> pointer;


    // Constructors
    TableBoundaryInterface();
    TableBoundaryInterface(Table* ptr);


    // Factory
    static pointer create(table::at_boundary behavior,
                          Table*             ptr);


    // Destructor
    ~TableBoundaryInterface();


    // Functionality
    virtual float lookup(std::size_t index,
                         float       key) const = 0;


  protected:
    // Pointer to owning table object
    std::shared_ptr<Table> table;


  }; // !TableBoundaryInterface


} // !nemesis


// Forward Declaration Inclusions
#include "../table.h"


#endif // !NEMESIS_TABLE_BOUNDARY_INTERFACE_H