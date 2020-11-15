// end_condition.h


#ifndef END_CONDITION_H
#define END_CONDITION_H


//------------------------------------------------------------------------------
// Name:    kernel
// Purpose: This namespace holds all parts of the simulation kernel.
//------------------------------------------------------------------------------
namespace kernel
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
    // Destructor
    ~EndCondition() { /* TODO: I am far too lazy to write this in a source file */ }

    // Functionality
    virtual bool met(void) = 0;

  }; // !EndCondition


} // !kernel
#endif // !END_CONDITION_H
