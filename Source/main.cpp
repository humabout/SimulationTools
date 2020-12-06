// main.cpp

// This just exists for rapid testing

#include <iostream>
#include <string>
#include "Kernel/state.h"
#include "Kernel/block.h"
#include "Kernel/sim_loop.h"
#include "Kernel/End_Conditions/max_time_exceeded.h"

#include "Utilities/Math/quaternion.h"
#include "Utilities/Math/math_constants.h"

class BlockTest : public kernel::Block
{
public:
  BlockTest() {}
  ~BlockTest() {}

  void doInitialize() override {}
  void doUpdate() override {}

};


int main()
{

  std::cout << "Testing Simulation Kernel...\n\n";

  // Setting test inputs
  double max_time = 10;
  double time_step = 0.01;

  double& x = *new double;
  double& dx = *new double;
  double& ddx = *new double;

  // Initial Values
  x = 0;
  dx = 0;
  ddx = 1;
  kernel::State::setIntegrationMethod(kernel::State::type::euler);

  // Instantiating Test Objects
  kernel::State* dX = kernel::State::create(dx, ddx);
  kernel::State* X = kernel::State::create(x, *dX);

  kernel::Block* test = new BlockTest();
  // Note that the order of adding matters here! The derrivative must be added before the state.
  // TODO: Find a way to remove this sensitivity.
  *test << dX;
  *test << X;

  // Build Sim
  kernel::SimLoop sim(time_step, kernel::State::type::euler);
  sim.addEndCondition(new kernel::MaxTimeExceeded(max_time));
  sim.addBlock(test);

  // Run Sim
  sim.run();

  // Reporting the End Result
  std::cout << "x:\t" << std::to_string(x) << "\n";
  std::cout << "dx:\t" << std::to_string(dx) << "\n";
  std::cout << "ddx:\t" << std::to_string(ddx) << "\n";

  // Cleanup
  delete X;
  delete dX;
  delete test;

  return 0;
}