// return_linear_interpolation


// Inclusions
#include <cstddef>
#include <memory>
#include <stdexcept>
#include "../table_type_definitions.h"
#include "table_lookup_interface.h"


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
  // Name:    ReturnLinearInterpolation
  // Purpose: This concretion returns the linearly interpolatied value between
  //          two key values.
  //----------------------------------------------------------------------------
  class ReturnLinearInterpolation : public TableLookupInterface
  {
  public:
    // Constructors
    ReturnLinearInterpolation() = delete;
    ReturnLinearInterpolation(Table* ptr)
    {
      this->table = std::shared_ptr<Table>(ptr);
    }


    // Destructor
    ~ReturnLinearInterpolation()
    {
      // Does Nothing
    }


    // Functionality
    double lookup(std::size_t field_index,
                  double      key) const
    {
      // Getting the index of the next lower, or exact match
      std::size_t key_index = table->find(key);

      // Performing linear interpolation
      double x1 = table->Keys[key_index];
      double x2 = table->Keys[key_index + 1];
      double y1 = table->Entries[key_index][field_index];
      double y2 = table->Entries[key_index + 1][field_index];

      return y1 + (key - x1) * (y2 - y1) / (x2 - x1);
    }


  }; // !ReturnLinearInterpolation


} // !nemesis
