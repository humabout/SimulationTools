// main.cpp

// This just exists for rapid testing

#include <iostream>
#include <memory>
#include <string>
#include "Kernel/state.h"
#include "Kernel/block.h"
#include "Kernel/sim_loop.h"
#include "Kernel/Clocks/sim_clock.h"
#include "Kernel/End_Conditions/max_time_exceeded.h"


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

  // Initial Values
  double x = 0;
  double dx = 0;
  double ddx = 1;
  kernel::State::setIntegrationMethod(kernel::State::type::euler);

  // Instantiating Test Objects
  std::shared_ptr<kernel::State> dX = kernel::State::create(dx, ddx);
  std::shared_ptr<kernel::State> X  = kernel::State::create(x, dX);

  std::shared_ptr <kernel::Block> test = std::shared_ptr <kernel::Block>(new BlockTest());
  // Note that the order of adding matters here! The derrivative must be added before the state.
  // TODO: Find a way to remove this sensitivity.
  *test << dX;
  *test << X;

  // Build Sim
  kernel::SimLoop sim(time_step, kernel::State::type::euler);
  sim.addEndCondition(std::shared_ptr<kernel::EndCondition>(new kernel::MaxTimeExceeded(max_time)));
  sim.addBlock(test);

  // Run Sim
  sim.run();

  // Reporting the End Result
  std::cout << "x:\t" << std::to_string(x) << "\n";
  std::cout << "dx:\t" << std::to_string(dx) << "\n";
  std::cout << "ddx:\t" << std::to_string(ddx) << "\n";  

  return 0;
}