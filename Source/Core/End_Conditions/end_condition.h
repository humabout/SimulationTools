// end_condition.h


#ifndef END_CONDITION_H
#define END_CONDITION_H


// Inclusions
#include <memory>


//------------------------------------------------------------------------------
// Name:    core
// Purpose: This namespace holds all parts of the simulation core.
//------------------------------------------------------------------------------
namespace core
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
    enum class type
    {
      max_time = 1
    }; // !type

    // Destructor
    virtual ~EndCondition() { /* TODO: I am far too lazy to write this in a source file */ }

    // Factory
    pointer create(type type_);

    // Functionality
    virtual bool met(void) = 0;

  }; // !EndCondition


} // !core
#endif // !END_CONDITION_H
