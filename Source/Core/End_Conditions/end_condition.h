// end_condition.h


#ifndef END_CONDITION_H
#define END_CONDITION_H


// Inclusions
#include <memory>


//------------------------------------------------------------------------------
// Name:    nemesis
// Purpose: This namespace holds all aspects of the Nemesis Simulation Toolkit.
//------------------------------------------------------------------------------
namespace nemesis
{


  //----------------------------------------------------------------------------
  // Name:    EndCondition
  // Purpose: This abstract class establishes the interface for end condition
  //          child classes. These are responsible for deciding whether or not
  //          to end the simulation, and if so, why.
  //----------------------------------------------------------------------------
  class EndCondition
  {
  public:
    // Typedefs
    typedef std::shared_ptr<EndCondition> pointer;

    // Destructor
    virtual ~EndCondition() { /* TODO: I am far too lazy to write this in a source file */ }

    // Functionality
    virtual bool met(void) = 0;

  }; // !EndCondition


} // !core
#endif // !END_CONDITION_H
