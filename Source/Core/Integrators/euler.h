// euler.h


#ifndef NEMESIS_INTEGRATOR_EULER_H
#define NEMESIS_INTEGRATOR_EULER_H


// Inclusions
#include <memory>
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
  // Name:    Euler
  // Purpose: This concretion of Integrator implements Euler's integration 
  //          method for propagating states.
  //----------------------------------------------------------------------------
  class Euler : public Integrator
  {
  public:
    // Typdefs
    typedef std::shared_ptr<Euler> pointer;

    // Constructor
    Euler(SimLoop* sim_);
    Euler(const Euler& that);
    Euler() = delete;

    // Destructor
    ~Euler();

  private:
    // Functionality
    void doUpdateStates(void) override;


  }; // !Euler


} // !nemesis


// Forward Declaration Inclusions
#include "../sim_loop.h"


#endif // !NEMESIS_INTEGRATOR_EULER_H
