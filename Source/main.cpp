// main.cpp

// This just exists for rapid testing

#include <iostream>
#include <memory>
#include <string>
#include "Core/state.h"
#include "Core/block.h"
#include "Core/sim_loop.h"
#include "Core/Clocks/sim_clock.h"
#include "Core/End_Conditions/max_time_exceeded.h"


class BlockTest : public core::Block
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
  core::State::setIntegrationMethod(core::State::type::euler);

  // Instantiating Test Objects
  std::shared_ptr<core::State> dX = core::State::create(dx, ddx);
  std::shared_ptr<core::State> X  = core::State::create(x, dX);

  std::shared_ptr <core::Block> test = std::shared_ptr <core::Block>(new BlockTest());
  // Note that the order of adding matters here! The derrivative must be added before the state.
  // TODO: Find a way to remove this sensitivity.
  *test << dX;
  *test << X;

  // Build Sim
  core::SimLoop sim(time_step, core::State::type::euler);
  sim.addEndCondition(std::shared_ptr<core::EndCondition>(new core::MaxTimeExceeded(max_time)));
  sim.addBlock(test);

  // Run Sim
  sim.run();

  // Reporting the End Result
  std::cout << "x:\t" << std::to_string(x) << "\n";
  std::cout << "dx:\t" << std::to_string(dx) << "\n";
  std::cout << "ddx:\t" << std::to_string(ddx) << "\n";  

  return 0;
}