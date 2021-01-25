// table.cpp


// Inclusions
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include "table.h"
#include "table_type_definitions.h"


//------------------------------------------------------------------------------
// Name:    Table
// Purpose: Default Constructor
//------------------------------------------------------------------------------
nemesis::Table::Table()
{
  Upper_Bound = nullptr;
  Lower_Bound = nullptr;
  Lookup = nullptr;
  is_sorted = false;
}

//------------------------------------------------------------------------------
// Name:    Table
// Purpose: Copy Constructor
//------------------------------------------------------------------------------
nemesis::Table::Table(const Table& that)
{
  this->Upper_Bound = that.Upper_Bound;
  this->Lower_Bound = that.Lower_Bound;
  this->Lookup = that.Lookup;
  is_sorted = false;
}

//------------------------------------------------------------------------------
// Name:    ~Table
// Purpose: Destructor. All pointers are governed by smart pointers and do not
//          require deletion.
//------------------------------------------------------------------------------
nemesis::Table::~Table()
{
  /* Does Nothing */
}

//------------------------------------------------------------------------------
// Name:    operator=
// Purpose: Copy Assignment Operator
//------------------------------------------------------------------------------
void nemesis::Table::operator=(const nemesis::Table& rhs)
{
  this->Upper_Bound = rhs.Upper_Bound;
  this->Lower_Bound = rhs.Lower_Bound;
  this->Lookup = rhs.Lookup;
}


//------------------------------------------------------------------------------
// Name:    add_entry
// Purpose: Adds an entry line to the table. This is a costly process because
//          each time it is called, the entire table must be resorted.
//------------------------------------------------------------------------------
void nemesis::Table::add_entry(double                     new_key,
                               const std::vector<double>& new_entry)
{
  Keys.push_back(new_key);
  Entries.push_back(new_entry);
  is_sorted = false;
  sort();
}


//------------------------------------------------------------------------------
// Name:    add_field
// Purpose: Adds a new field to the table
//------------------------------------------------------------------------------
void nemesis::Table::add_field(const std::string&         field_name,
                               const std::vector<double>& field_values)
{
  // Add the new field's name to the list of field names
  Field_Names.emplace(field_name, Field_Names.size());

  // Add the field values to the table
  for (std::size_t i = 0; i < Entries.size(); i++)
  {
    Entries[i].push_back(field_values[i]);
  }
}


//------------------------------------------------------------------------------
// Name:    lower_boundary_behavior
// Purpose: Sets the the table's behavior when told to look up a value that is
//          off the lower edge of the table.
//------------------------------------------------------------------------------
void nemesis::Table::lower_boundary_behavior(table::at_boundary behavior)
{
  // This must be performed on a sorted table
  this->sort();
  this->Lower_Bound = TableBoundaryInterface::create(behavior, this);
}


//------------------------------------------------------------------------------
// Name:    lookup
// Purpose: Sets the the table's method of returning values that fall within the
//          bounds of the table. These all assume that the table is sorted in
//          ascending order by key value.
//
// Note:    Robustness would suggest that the table always be sorted prior to a
//          lookup. The sort is performed lazily, so this shouldn't add much
//          time to a lookup.
//------------------------------------------------------------------------------
double nemesis::Table::lookup(std::size_t index,
                              double      key)
{
  // All lookup methods rely on the table's data beind sorted. Since the sort is
  // performed lazily, there shouldn't be a major performance hit from making 
  // this call, but it will improve robustness.
  this->sort();

  // Looking up the value based on where it falls related to the table's data.
  if ( (Keys.front() <= key) &&
       (key <= Keys.back())  )
  {
    return Lookup->lookup(index, key);
  }
  else if ( key < Keys.front() )
  {
    return Lower_Bound->lookup(index, key);
  }
  else
  {
    return Upper_Bound->lookup(index, key);
  }
}


double nemesis::Table::lookup(std::string field,
                              double      key)
{
  field_list::const_iterator field_iter = Field_Names.find(field);
  if (field_iter != Field_Names.end())
  {
    size_t field_index = field_iter->second;
    return lookup(field_index, key);
  }
  else
  {
    throw std::runtime_error("Fatal Error: Field name does not exist.");
  }
}


//------------------------------------------------------------------------------
// Name:    lookup_method
// Purpose: Sets the the table's behavior when told to look up a value.
//------------------------------------------------------------------------------
void nemesis::Table::lookup_method(table::lookup behavior)
{
  this->Lookup = TableLookupInterface::create(behavior, this);
}


//------------------------------------------------------------------------------
// Name:    pointer
// Purpose: Returns a shared pointer to this table.
//------------------------------------------------------------------------------
nemesis::Table::pointer nemesis::Table::get_pointer(void)
{
  return std::shared_ptr<Table>(this);
}


//------------------------------------------------------------------------------
// Name:    upper_boundary_behavior
// Purpose: Sets the the table's behavior when told to look up a value that is
//          off the upper edge of the table.
//------------------------------------------------------------------------------
void nemesis::Table::upper_boundary_behavior(table::at_boundary behavior)
{
  // This must be performed on a sorted table
  this->sort();
  this->Upper_Bound = TableBoundaryInterface::create(behavior, this);
}


//------------------------------------------------------------------------------
// Name:    sort
// Purpose: This uses a quick sort to sort the table by key in ascending order, 
//          and must be done before using the table. It is a costly procedure 
//          and should be executed as rarely as possible while still ensuring 
//          that entries appear in ascending order by key. The assumption is 
//          that the table will be accessed far more often than it will be 
//          modified, and thus spending time presorting the table will enable 
//          faster and more robust lookups.
//------------------------------------------------------------------------------
void nemesis::Table::sort(void)
{
  // Lazy Evaluation of sort
  if (!is_sorted)
  {
    quicksort(0, Keys.size());
  }
  else
  {
    // Be lazy and do nothing.
  }
}


//------------------------------------------------------------------------------
// Name:    quicksort
// Purpose: This performs a quicksort on the keys and fields, making sure that
//          whenever a key's position changes, the corresponding field's changes
//          similarly.
//------------------------------------------------------------------------------
void nemesis::Table::quicksort(std::size_t low,
                               std::size_t high)
{
  if (low < high)
  {
    // Placing the partitioning index in the correct place
    std::size_t pi = partition(low, high);

    // Separately sort elements before partition and after partition  
    quicksort(low, pi - 1);
    quicksort(pi + 1, high);
  }
}


//------------------------------------------------------------------------------
// Name:    qsPartition
// Purpose: This assists with the quicksort
//------------------------------------------------------------------------------
std::size_t nemesis::Table::partition(std::size_t low,
                                      std::size_t high)
{
  double pivot = Keys[high];
  std::size_t i = low - 1;
  for (std::size_t j = low; j <= high - 1; j++)
  {
    // If current element is smaller than the pivot
    if (Keys[j] < pivot)
    {
      // Increment index of smaller element
      i++;

      // Swap both the key value and entries
      std::swap(Keys[i], Keys[j]);
      std::swap(Entries[i], Entries[j]);
    }
  }
  std::swap(Keys[i + 1], Keys[high]);
  std::swap(Entries[i + 1], Entries[high]);
  return (i + 1);
}


//------------------------------------------------------------------------------
// Name:    getLowerIndex
// Purpose: This returns the index of the closest value to the key that is less
//          than or equal to the key. It does so by checking the midpoint on the
//          table of Keys, and if this isn't the correct value, it sets that as
//          a bound for the next search. This is repeated until the correct key
//          value is found.
//------------------------------------------------------------------------------
std::size_t nemesis::Table::find(double key) const
{
  // Checking if the key is bounded within the list of keys
  if (Keys.back() < key ||
    Keys.front() > key)
  {
    throw std::runtime_error("Invalid key encountered. Key does not exist on the table.");
  }
  else
  {
    // Continue
  }

  // Finding the index of the appropriate value
  std::size_t upper = Keys.size();
  std::size_t lower = 0;
  std::size_t guess = static_cast<std::size_t>(0.5 * (upper + lower));
  while (true)
  {
    if (Keys[guess] == key)
    {
      return guess;
    }
    else if (Keys[guess] > key)
    {
      upper = guess;
      guess = static_cast<std::size_t>(0.5 * (upper + lower));
    }
    else
    {
      lower = guess;
      guess = static_cast<std::size_t>(0.5 * (upper + lower));
    }
  }
}