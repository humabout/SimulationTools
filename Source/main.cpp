// main.cpp

// This just exists for rapid testing

#include <iostream>
#include <memory>
#include "nemesis.h"
#include"Models/Examples/position.h"


int main()
{
  // Declaring typedefs for sanity's sake
  typedef nemesis::Block::pointer              block_pointer;
  typedef nemesis::examples::Position          position_block;
  typedef nemesis::examples::Position::pointer position_pointer;

  // Setting test inputs
  double max_time  = 10;
  double time_step = 0.01;

  double position     = 0;
  double velocity     = 0;
  double acceleration = 1;

  // Initial Values
  position_pointer access = position_pointer(new position_block(position, velocity, acceleration));
  block_pointer test = access;

  // Build Sim
  nemesis::SimLoop sim(time_step);
  sim.addEndCondition(nemesis::EndCondition::pointer(new nemesis::MaxTimeExceeded(max_time)));
  sim.addBlock(test);

  // Reporting States Prior to Propagation
  std::cout << "Initial States:\n";
  access->print();

  // Run Sim
  sim.run();

  // Reporting the End Result
  std::cout << "\nFinal States:\n";
  access->print();

  return 0;
}