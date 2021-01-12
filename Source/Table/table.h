// table.h

#ifndef NEMESIS_TABLE_H
#define NEMESIS_TABLE_H


// Inclusions
#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include <unordered_map>


// Forward Declarations
namespace nemesis
{
  class TableBoundaryBehavior;
  class TableLookupBehavior;
}


namespace nemesis
{


  //----------------------------------------------------------------------------
  // Name:    table
  // Purpose: This is responsible for holding all enum values needed by the 
  //          Table class.
  //----------------------------------------------------------------------------
  namespace table
  {
    // Enums and Typedefs
    enum class at_boundary // Need to make these classes
    {
      return_zero,
      cap_at_end_value,
      linear_extrapolation
    };
    enum class lookup // Need to make these classes
    {
      next_lower_value,
      nearest_value,
      exact_value,
      linear_interpolation,
      spline_interpolation,
      next_higher_value
    };


  } // !table
  

  //----------------------------------------------------------------------------
  // Name:    Table
  // Purpose: 
  //----------------------------------------------------------------------------
  template <class key_type, class field_type>
  class Table
  {
    // Aliases & Typedefs
    std::shared_ptr< Table<key_type, field_type> > pointer;

  public:
    // Constructors
    Table();
    Table(const Table& that);
    // Add a constructor that builds the table from a file


    // Destructors
    ~Table();


    // Assignment Operator
    void operator=(const Table<key_type, field_type>& lhs);


    // Setters
    void upper_boundary_behavior(table::at_boundary behavior);
    void lower_boundary_behavior(table::at_boundary behavior);
    void lookup_method(table::lookup method);


    // Accessors
    pointer pointer(void) constexpr;
    // Part of strategy patterns, these forward the call to the appropriate 
    // object for execution
    field_type lookup(std::string                     field,
                      std::initializer_list<key_type> keys);  // uses initializer_list to accept an unknown number of keys to look up
    field_type lookup(std::size_t                     index, 
                      std::initializer_list<key_type> keys); // uses initializer_list to accept an unknown number of keys to look up
    entry_line lookup_entry(std::initializer_list<key_type> keys); // uses initializer_list to accept an unknown number of keys to look up


    // Construction
    //--------------------------------------------------------------------------
    // Add a new entry to the table
    void add_entry(const std::vector<field_type>& new_entry);

    // Add a new field to the table
    void add_field(const std::string& field_name,
                   const std::vector<field_type>& field_values);

  private:
    // Table State
    //--------------------------------------------------------------------------
    std::shared_ptr<TableBoundaryBehavior> Upper_Bound;
    std::shared_ptr<TableBoundaryBehavior> Lower_Bound;
    std::shared_ptr<TableLookupBehavior>   Lookup;

    // Table Data
    //--------------------------------------------------------------------------
    std::vector<key_type>                        Keys;
    std::vector< std::vector<field_type> >       Entries;
    std::unordered_map<std::string, std::size_t> Field_Names;

    // Helper Functions
    //--------------------------------------------------------------------------

  }; // !Table


  //============================================================================
  // Method Definitions
  //============================================================================
  
  //----------------------------------------------------------------------------
  // Name:    Table
  // Purpose: Default Constructor
  //----------------------------------------------------------------------------
  template <class key_type, class field_type>
  nemesis::Table<key_type, field_type>::Table()
  {
    Upper_Bound = nullptr;
    Lower_Bound = nullptr;
    Lookup = nullptr;
  }

  //----------------------------------------------------------------------------
  // Name:    Table
  // Purpose: Copy Constructor
  //----------------------------------------------------------------------------
  template <class key_type, class field_type>
  Table<key_type, field_type>::Table(const Table& that)
  {
    this->Upper_Bound = that.Upper_Bound;
    this->Lower_Bound = that.Lower_Bound;
    this->Lookup = that.Lookup;
  }

  //----------------------------------------------------------------------------
  // Name:    ~Table
  // Purpose: Destructor
  //----------------------------------------------------------------------------
  template <class key_type, class field_type>
  Table<key_type, field_type>::~Table()
  {
    /* Does Nothing */
  }

  //----------------------------------------------------------------------------
  // Name:    operator=
  // Purpose: Copy Assignment Operator
  //----------------------------------------------------------------------------
  template <class key_type, class field_type>
  void Table<key_type, field_type>::operator=(const nemesis::Table<key_type, field_type>& lhs)
  {
    this->Upper_Bound = that.Upper_Bound;
    this->Lower_Bound = that.Lower_Bound;
    this->Lookup = that.Lookup;
  }









  //----------------------------------------------------------------------------
  // Name:    add_entry
  // Purpose: Adds an entry line to the table
  //----------------------------------------------------------------------------
  template <class key_type, class field_type>
  void Table<key_type, field_type>::add_entry(const std::vector<field_type>& new_entry)
  {
    Entries.push_back(new_entry);
  }

  //----------------------------------------------------------------------------
  // Name:    add_field
  // Purpose: Adds a new field to the table
  //----------------------------------------------------------------------------
  template <class key_type, class field_type>
  void Table<key_type, field_type>::add_field(const std::string& field_name,
    const std::vector<field_type>& field_values)
  {
    Field_Names.emplace(field_name);
    for (std::size_t i = 0; i < Entries.size(); i++)
    {
      Entries[i].push_back(field_values[i]);
    }
  }










} // !nemesis


// Forward Declarations
#include "table_boundary_behavior.h"
#include "table_lookup_behavior.h"





#endif // !NEMESIS_TABLE_H
