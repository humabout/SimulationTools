// main.cpp

// This just exists for rapid testing

#include <iostream>
#include <string>
#include "Kernel/state.h"
#include "Kernel/block.h"
#include "Kernel/sim_loop.h"

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

  // Instantiating Test Objects
  kernel::State* dX = kernel::State::create(dx, ddx);
  kernel::State* X = kernel::State::create(x, *dX);

  kernel::Block* test = new BlockTest();
  *test << X;
  *test << dX;

  kernel::SimLoop sim(max_time, time_step, kernel::IntegrationMethod::type::RK4);
  sim.add(test);
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