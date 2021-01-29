// integrator.cpp


// Inclusions
#include <map>
#include <memory>
#include <stdexcept>
#include "integrator.h"
#include "state.h"


//------------------------------------------------------------------------------
// Name:    Integrator
// Purpose: Default Constructor
//------------------------------------------------------------------------------
nemesis::Integrator::Integrator()
{
  this->Sim = nullptr;
}


//------------------------------------------------------------------------------
// Name:    Integrator
// Purpose: Constructor
//------------------------------------------------------------------------------
nemesis::Integrator::Integrator(SimLoop* sim_)
{
  this->Sim = std::shared_ptr<SimLoop>(sim_);
}


//------------------------------------------------------------------------------
// Name:    Integrator
// Purpose: Copy Constructor
//------------------------------------------------------------------------------
nemesis::Integrator::Integrator(const Integrator& that)
{
  this->Sim    = that.Sim;
  this->States = that.States;
}


//------------------------------------------------------------------------------
// Name:    ~Integrator
// Purpose: Destructor. This object owns nothing and deallocates nothing.
//------------------------------------------------------------------------------
nemesis::Integrator::~Integrator()
{
  // Does Nothing
}


//------------------------------------------------------------------------------
// Name:    create
// Purpose: Factory Method
//------------------------------------------------------------------------------
nemesis::Integrator::pointer nemesis::Integrator::create(Integrator::type method_)
{
  switch (method_)
  {
  case nemesis::Integrator::type::euler:
  case nemesis::Integrator::type::rk2:
  case nemesis::Integrator::type::rk4:
  default:
    throw std::runtime_error("Fatal Error: Unrecognized Integration::type provided at Integrator::create.");
  }
}


//------------------------------------------------------------------------------
// Name:    addState
// Purpose: Adds a new state to the list of states and resorts the list so that
//          it stays in descending derivative order.
//------------------------------------------------------------------------------
void nemesis::Integrator::addState(double& x,
                                   double& dx)
{
  State::pointer new_state = State::create(x, dx);

  // Update the new state's derivative order
  for (state_list::iterator it = this->States.begin();
       it != States.end();
       ++it)
  {
    bool found_state_derivative = (new_state->dx() == (*it).second->x());
    if (found_state_derivative)
    {
      new_state->order() += (*it).second->order();
      break;
    }
    else
    {
      continue;
    }
  }

  // Add the new state to the list where it belongs
  this->States.emplace(new_state->order(), new_state);

}


//------------------------------------------------------------------------------
// Name:    updateStates
// Purpose: Propagates all states in the simulation forward one frame. This is
//          part of a tempalte pattern that forwards the call to doUpdateStates
//          for implementation by child classes.
//------------------------------------------------------------------------------
void nemesis::Integrator::updateStates(void)
{
  this->doUpdateStates();
}