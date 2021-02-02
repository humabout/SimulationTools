// integrator.cpp


// Inclusions
#include <map>
#include <memory>
#include <stdexcept>
#include "integrator.h"
#include "state.h"

#include "euler.h"


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
  this->Sim = sim_;
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
nemesis::Integrator* nemesis::Integrator::create(type     method_,
                                                 SimLoop* sim_)
{
  switch (method_)
  {
  case nemesis::Integrator::type::euler:
    return new Euler(sim_);
  case nemesis::Integrator::type::rk2:
  case nemesis::Integrator::type::rk4:
  default:
    throw std::runtime_error("Warning: Unrecognized Integration::type provided at Integrator::create.  Returning Euler integration.");
    return new Euler(sim_);
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

  // Checking if the new state is the derivative of any of the current states
  // There should be, at most, one other state for whom this is true
  bool needs_update = false;
  for (state_list::iterator state = States.begin();
       state != States.end();
       ++state)
  {
    bool new_state_has_derivative = (&(new_state->dx()) == &((*state).second->x()));
    if (new_state_has_derivative)
    {
      (*state).second->order() += new_state->order();
      needs_update = true;
      break;
    }
    else
    {
      continue;
    }
  }


  // Checking if the new state has a derivative in the current list of states
  for (state_list::iterator state = States.begin();
       state != States.end();
       ++state)
  {
    bool new_state_is_derivative = (&(new_state->x()) == &((*state).second->dx()));

    if (new_state_is_derivative)
    {
      new_state->order() += (*state).second->order();
      break;
    }
    else
    {
      continue;
    }
  }
  // Add the new state to the list where it belongs
  this->States.emplace(new_state->order(), new_state);


  // Update state list, if needed
  if (needs_update)
  {
    state_list temp_list;

    // Reorder the list based on the new state derivative orders
    for (state_list::iterator state = States.begin();
         state != States.end();
         ++state)
    {
      temp_list.emplace((*state).second->order(), (*state).second);
    }
    States = temp_list;
  }
  else
  {
    // No need to reorder
  }
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