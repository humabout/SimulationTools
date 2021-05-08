// main.cpp

// This just exists for rapid testing

#include <iostream>
//#include <memory>
//#include "nemesis.h"
//#include"Models/Examples/position.h"
#include "File/delimited_input_file.h"
#include <string>

int main()
{

  /*
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

  // Creating Block to Propagate
  // NOTE:  The block pointer is held separately so we can access its methods. 
  //        Eventually, data output will be added to the library to avoid 
  //        needing this sort of thing.

  position_block* access = new position_block(position, velocity, acceleration);
  block_pointer test = block_pointer(access);

  // Build Sim
  nemesis::SimLoop sim(time_step, nemesis::Integrator::type::euler);
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
  */

  return 0;
}