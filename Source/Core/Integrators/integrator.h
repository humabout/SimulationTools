// integrator.h


#ifndef NEMESIS_INTEGRATOR_H
#define NEMESIS_INTEGRATOR_H


// Inclusions
#include <map>
#include <memory>
#include "state.h"


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
  // Name:    Integrator
  // Purpose: This abstract class declares the interface for integrator objects,
  //          and is responsible for providing basic services to all children.
  //          These services are limited to maintaining an ordered list of 
  //          states, adding new states, and providing access to the Sim via a
  //          pointer. This interface uses a template pattern to enforce the 
  //          interface for all children.
  //----------------------------------------------------------------------------
  class Integrator
  {
  public:
    // Enums & Typedefs
    enum class type
    {
      euler = 1,
      rk2   = 2,
      rk4   = 3
    }; // !type
    typedef std::shared_ptr<Integrator> pointer;
    typedef std::multimap< unsigned int, 
                           nemesis::State::pointer, 
                           std::greater<unsigned int> > state_list;

    // Constructors
    Integrator();
    Integrator(SimLoop* sim_);
    Integrator(const Integrator& that);

    // Destructor
    ~Integrator();

    // Factory
    static Integrator* create(type     method_,
                              SimLoop* sim_);

    // Functionality
    void addState(double& x,
                  double& dx);
    void updateStates(void);


  protected:
    // Owning Simulation
    SimLoop* Sim;

    // Data
    state_list States;

    // Functionality Implementation
    virtual void doUpdateStates(void) = 0;


  }; // !Integrator


} // !nemesis


// Forward Declaration Inclusions
#include "../sim_loop.h"


#endif // !NEMESIS_INTEGRATOR_H
