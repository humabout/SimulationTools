// state.cpp


// Inclusions
#include <memory>
#include "state.h"


//------------------------------------------------------------------------------
// Name:    State
// Purpose: Default Constructor
//------------------------------------------------------------------------------
nemesis::State::State()
{
  State_Variable   = nullptr;
  State_Derivative = nullptr;
  Order            = 0;
}


//------------------------------------------------------------------------------
// Name:    State
// Purpose: Constructor
//------------------------------------------------------------------------------
nemesis::State::State(double& x_,
                      double& dx_)
{
  this->State_Variable   = &x_;
  this->State_Derivative = &dx_;
  this->Order            = 1;
}


//------------------------------------------------------------------------------
// Name:    State
// Purpose: Copy Constructor
//------------------------------------------------------------------------------
nemesis::State::State(const State& that)
{
  this->State_Variable   = that.State_Variable;
  this->State_Derivative = that.State_Derivative;
  this->Order            = that.Order;
}


//------------------------------------------------------------------------------
// Name:    ~State
// Purpose: Destructor. This object has nothing to deallocate.
//------------------------------------------------------------------------------
nemesis::State::~State()
{
  // Does nothing
}


//------------------------------------------------------------------------------
// Name:    create
// Purpose: Factory method for creating new states.
//------------------------------------------------------------------------------
/*
nemesis::State::pointer nemesis::State::create(double& x_,
                                               double& dx_)
{
  return pointer(new State(x_, dx_));
}
*/


//------------------------------------------------------------------------------
// Name:    x
// Purpose: Returns a reference to the state variable stored in this object.
// Output:  Reference to State_Variable
//------------------------------------------------------------------------------
double& nemesis::State::x(void) const
{
  return *State_Variable;
}


//------------------------------------------------------------------------------
// Name:    dx
// Purpose: Returns a reference to the state derivative stored in this object.
// Output:  Reference to State_Derivative
//------------------------------------------------------------------------------
double& nemesis::State::dx(void) const
{
  return *State_Derivative;
}


//------------------------------------------------------------------------------
// Name:    order
// Purpose: Returns the order of the state derivative stored here.
//------------------------------------------------------------------------------
unsigned int& nemesis::State::order(void)
{
  return Order;
}


//------------------------------------------------------------------------------
// Name:    operator==
// Purpose: Copy Assignment Operator
//------------------------------------------------------------------------------
void nemesis::State::operator=(const State& lhs)
{
  this->State_Variable   = lhs.State_Variable;
  this->State_Derivative = lhs.State_Derivative;
  this->Order            = lhs.Order;
}


//------------------------------------------------------------------------------
// Name:    operator==
// Purpose: Compairs the order of two states, returning true if their orders
//          are equal.
//------------------------------------------------------------------------------
bool nemesis::State::operator==(const State& lhs) const
{
  return this->Order == lhs.Order;
}


//------------------------------------------------------------------------------
// Name:    operator!=
// Purpose: Compairs the order of two states, returning true if their orders
//          are not equal.
//------------------------------------------------------------------------------
bool nemesis::State::operator!=(const State& lhs) const
{
  return this->Order != lhs.Order;
}


//------------------------------------------------------------------------------
// Name:    operator<
// Purpose: Compairs the order of two states, returning true if the right-hand
//          side is less than the left-hand side.
//------------------------------------------------------------------------------
bool nemesis::State::operator<(const State& lhs) const
{
  return this->Order < lhs.Order;
}


//------------------------------------------------------------------------------
// Name:    operator<=
// Purpose: Compairs the order of two states, returning true if the right-hand
//          side is less than or equal to the left-hand side.
//------------------------------------------------------------------------------
bool nemesis::State::operator<=(const State& lhs) const
{
  return this->Order <= lhs.Order;
}


//------------------------------------------------------------------------------
// Name:    operator>
// Purpose: Compairs the order of two states, returning true if the right-hand
//          side is greater than the left-hand side.
//------------------------------------------------------------------------------
bool nemesis::State::operator>(const State& lhs) const
{
  return this->Order > lhs.Order;
}


//------------------------------------------------------------------------------
// Name:    operator>=
// Purpose: Compairs the order of two states, returning true if the right-hand
//          side is greater than or equal to the left-hand side.
//------------------------------------------------------------------------------
bool nemesis::State::operator>=(const State& lhs) const
{
  return this->Order >= lhs.Order;
}