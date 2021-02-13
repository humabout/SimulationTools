// rk2.h


#ifndef NEMESIS_INTEGRATOR_RK2_H
#define NEMESIS_INTEGRATOR_RK2_H


// Inclusions
#include <memory>
#include <vector>
#include "integrator.h"


// Forward Declarations
namespace nemesis
{
  class SimLoop;
}


//------------------------------------------------------------------------------
// Name:    nemesis
// Purpose: This namespace holds all aspects of the Nemesis Simulation Toolkit.
//------------------------------------------------------------------------------
namespace nemesis
{


  //----------------------------------------------------------------------------
  // Name:    RK2
  // Purpose: This concretion of Integrator implements the rK2 integration 
  //          method for propagating states.
  //----------------------------------------------------------------------------
  class RK2 : public Integrator
  {
  public:
    // Typdefs
    typedef std::shared_ptr<RK2> pointer;

    // Constructor
    RK2(SimLoop*   sim);
    RK2(const RK2& that);
    RK2() = delete;

    // Destructor
    ~RK2();

  private:
    // Member Variables
    std::vector< std::vector<double> > x;  //
    std::vector< std::vector<double> > dx; //

    // Functionality
    void doUpdateStates(void) override;


  }; // !RK2


} // !nemesis




#endif // !NEMESIS_INTEGRATOR_RK2_H
