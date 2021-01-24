// return_exact_value.h


#ifndef NEMESIS_RETURN_EXACT_VALUE_H
#define NEMESIS_RETURN_EXACT_VALUE_H


// Inclusions
#include <cstddef>
#include <memory>
#include <stdexcept>
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
  // Name:    ReturnExactValue
  // Purpose: This concretion only returns data for the exact key matches and
  //          throws an error otherwise.
  //----------------------------------------------------------------------------
  class ReturnExactValue : public TableLookupInterface
  {
  public:
    // Constructors
    ReturnExactValue() {  }
    ReturnExactValue(Table* ptr);


    // Destructor
    ~ReturnExactValue()
    {
      // Does Nothing.
    }


    // Functionality
    double lookup(std::size_t index,
                  double      key) const
    {

    }


  }; // !ReturnExactValue


} // !nemesis


// Forward Declaration Inclusions
#include "../table.h"


#endif // !NEMESIS_RETURN_EXACT_VALUE_H
