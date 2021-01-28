// state.cpp


// Inclusions
#include <cstddef>
#include <memory>
#include "state.h"

// Static Variables
bool                 nemesis::State::Is_Ready = true;
nemesis::State::type nemesis::State::Method   = nemesis::State::type::euler;


//----------------------------------------------------------------------------
// Name:    ~State
// Purpose: This object does not own its own state or state derrivative. These
//          are merely linked to via reference for the sake of propagating 
//          them. The values' owners are responsible for deleting them, if
//          they live on heap. As a result, this object owns nothing and does
//          not need to delete anything.
//----------------------------------------------------------------------------
nemesis::State::~State()
{
  // Does nothing.
}


//----------------------------------------------------------------------------
// Name:    setMethod
// Purpose: This clears the old integration instance and sets a new method so
//          that the next time an instance is requested, the new method will
//          generated and returned.
//----------------------------------------------------------------------------
void nemesis::State::setIntegrationMethod(nemesis::State::type method_)
{
  State::Method = method_;
}


//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
// GETTERS
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
bool nemesis::State::isReady(void)
{
  return Is_Ready;
}