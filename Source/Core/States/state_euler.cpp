// state_euler.cpp


// Inclusions
#include <cstddef>
#include "state_euler.h"
#include "../Clocks/sim_clock.h"
#include "../../Math/vector.h"
#include "../../Math/matrix.h"
#include "../../Math/quaternion.h"


//------------------------------------------------------------------------------
// Name:    StateEuler
// Purpose: Constructor Overload.
//------------------------------------------------------------------------------
template <class T>
core::StateEuler<T>::StateEuler(T& x_,
                                T& dx_)
{
  this->x  = &x_;
  this->dx = &dx_;
}
template core::StateEuler< double           >::StateEuler(double&,           double&);
template core::StateEuler< math::Vector     >::StateEuler(math::Vector&,     math::Vector&);
template core::StateEuler< math::Quaternion >::StateEuler(math::Quaternion&, math::Quaternion&);
template core::StateEuler< math::Matrix     >::StateEuler(math::Matrix&,     math::Matrix&);

//------------------------------------------------------------------------------
// Name:    ~StateEuler
// Purpose: Destructor. This class owns nothing and deletes nothing.
//------------------------------------------------------------------------------
template <class T>
core::StateEuler<T>::~StateEuler()
{
  // Does Nothing
}
template core::StateEuler< double           >::~StateEuler();
template core::StateEuler< math::Vector     >::~StateEuler();
template core::StateEuler< math::Quaternion >::~StateEuler();
template core::StateEuler< math::Matrix     >::~StateEuler();


//------------------------------------------------------------------------------
// Name:    propagate
// Purpose: This propagates the state forward one time step using the Euler's
//          method.
//------------------------------------------------------------------------------
template <class T>
void core::StateEuler<T>::propagate(void)
{
  *(this->x) += core::SimClock::tick() * *(this->dx);
  State::Is_Ready = true;
}
template void core::StateEuler< double           >::propagate(void);
template void core::StateEuler< math::Vector     >::propagate(void);
template void core::StateEuler< math::Quaternion >::propagate(void);
template void core::StateEuler< math::Matrix     >::propagate(void);