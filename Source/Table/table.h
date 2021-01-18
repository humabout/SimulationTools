// table.h

#ifndef NEMESIS_TABLE_H
#define NEMESIS_TABLE_H


// Inclusions
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include "table_type_definitions.h"


// Forward Declarations
namespace nemesis
{
  class TableBoundaryInterface;
  class TableLookupInterface;
}


//------------------------------------------------------------------------------
// Name:    nemesis
// Purpose: This namespace holds all aspects of the Nemesis Simulation Toolkit.
//------------------------------------------------------------------------------
namespace nemesis
{
    

  //----------------------------------------------------------------------------
  // Name:    Table
  // Purpose: This class stores numerical tabular data and provides methods for
  //          accessing it, interpolating on it, and extrapolating from it. Key
  //          values are always numerical in nature.
  //
  // Future Work: It can be constructed directly from a file
  //----------------------------------------------------------------------------
  class Table
  {
  public:
    // Aliases & Typedefs
    typedef std::shared_ptr<Table> pointer;


    // Constructors
    Table();
    Table(const Table& that);
    // Add a constructor that builds the table from a file


    // Destructors
    ~Table();


    // Assignment Operator
    void operator=(const Table& rhs);


    // Setters
    void upper_boundary_behavior(table::at_boundary behavior);
    void lower_boundary_behavior(table::at_boundary behavior);
    void lookup_method(table::lookup method);


    // Accessors
    pointer get_pointer(void);
    float lookup(std::string field,
                 float       key) const;
    float lookup(std::size_t index,
                 float       key) const;


    // Mutators
    void add_entry(float                     new_key,
                   const std::vector<float>& new_entry);
    void add_field(const std::string&        field_name,
                   const std::vector<float>& field_values);

  private:
    // Aliases & Typedefs
    typedef std::unordered_map<std::string, std::size_t> field_list;

    // Table State
    std::shared_ptr<TableBoundaryInterface> Upper_Bound;
    std::shared_ptr<TableBoundaryInterface> Lower_Bound;
    std::shared_ptr<TableLookupInterface>   Lookup;

    // Table Data
    std::vector<float>                Keys;
    std::vector< std::vector<float> > Entries;
    field_list                        Field_Names;

    // Helper Functions
    void sort(void);
    void quicksort(std::size_t low,
                   std::size_t high);
    std::size_t partition(std::size_t low,
                          std::size_t high);
  };

  
} // !nemesis


// Forward Declarations
#include "Boundary_Behaviors/table_boundary_interface.h"
#include "Lookup_Behaviors/table_lookup_interface.h"





#endif // !NEMESIS_TABLE_H
