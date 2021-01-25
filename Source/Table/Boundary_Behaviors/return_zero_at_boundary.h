// return_zero_at_boundary.h


#ifndef NEMESIS_RETURN_ZERO_AT_BOUNDARY_H
#define NEMESIS_RETURN_ZERO_AT_BOUNDARY_H


// Inclusions
#include <memory>
#include "table_boundary_interface.h"


//------------------------------------------------------------------------------
// Name:    nemesis
// Purpose: This namespace holds all aspects of the Nemesis Simulation Toolkit.
//------------------------------------------------------------------------------
namespace nemesis
{


  //----------------------------------------------------------------------------
  // Name:    ReturnZeroAtBoundary
  // Purpose: This concretion returns a lookup value of zero when querried.
  //----------------------------------------------------------------------------
  class ReturnZeroAtBoundary : public TableBoundaryInterface
  {
  public:
    // Constructors
    ReturnZeroAtBoundary() = delete;
    ReturnZeroAtBoundary(Table* ptr)
    {
      table = Table::pointer(ptr);
    }


    // Destructor
    ~ReturnZeroAtBoundary()
    {
      // Does Nothing
    }


    // Functionality
    double lookup(std::size_t index,
                  double      key) const
    {
      return 0.0;
    }


  private:
  }; // !ReturnZeroAtBoundary



} // !nemesis


#endif // !NEMESIS_RETURN_ZERO_AT_BOUNDARY_H
