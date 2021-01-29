// simple_integrator.cpp


// Inclusions
#include <iostream>
#include <string>
#include "position.h"


//------------------------------------------------------------------------------
// Name:    SimpleIntegrator
// Purpose: Default Constructor.
//------------------------------------------------------------------------------
nemesis::examples::Position::Position()
{
  this->pos = 0;
  this->vel = 0;
  this->acc = 0;
}


//------------------------------------------------------------------------------
// Name:    SimpleIntegrator
// Purpose: Constructor Overload. Sets values of the state variables.
//------------------------------------------------------------------------------
nemesis::examples::Position::Position(double position_,
                                      double velocity_,
                                      double acceleration_)
{
  this->pos = position_;
  this->vel = velocity_;
  this->acc = acceleration_;
}


//------------------------------------------------------------------------------
// Name:    ~SimpleIntegrator
// Purpose: Destructor. This object owns nothing and deallocates nothing
//------------------------------------------------------------------------------
nemesis::examples::Position::~Position()
{
  // Does nothing
}


//------------------------------------------------------------------------------
// Name:    doInitialize
// Purpose: This model does not need to be initialized. The state values are set
//          on instantiation.
//------------------------------------------------------------------------------
void nemesis::examples::Position::doInitialize(void)
{
  // Does nothing
}


//------------------------------------------------------------------------------
// Name:    doInitialize
// Purpose: This model has two states that require propagation: x and dx.
//------------------------------------------------------------------------------
void nemesis::examples::Position::doRegisterWith(SimLoop* sim_)
{
  sim_->addState(pos, vel);
  sim_->addState(vel, acc);
}


//------------------------------------------------------------------------------
// Name:    doInitialize
// Purpose: This model does not need to update anything between integrations.
//------------------------------------------------------------------------------
void nemesis::examples::Position::doUpdate(void)
{
  // Does nothing
}


//------------------------------------------------------------------------------
// Name:    print
// Purpose: This prints the object's current state to console.
//------------------------------------------------------------------------------
void nemesis::examples::Position::print(void) const
{
  std::cout << "Position:\t" << std::to_string(pos) << "\n";
  std::cout << "Velocity:\t" << std::to_string(vel) << "\n";
  std::cout << "Acceleration: \t" << std::to_string(acc) << "\n";
}


//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
// GETTERS
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
double nemesis::examples::Position::position(void) const
{
  return pos;
}
double nemesis::examples::Position::velocity(void) const
{
  return vel;
}
double nemesis::examples::Position::acceleration(void) const
{
  return acc;
}