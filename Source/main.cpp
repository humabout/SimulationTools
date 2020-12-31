// main.cpp

// This just exists for rapid testing

#include <iostream>
#include <memory>
#include <string>
#include "nemesis.h"
#include "Math/mat.h"


class BlockTest : public core::Block
{
public:
  double x;
  double dx;
  double ddx;

  BlockTest()
  {
    x = 0;
    dx = 0;
    ddx = 1;
  }

  ~BlockTest() {}

  void doInitialize() override
  {
    addState(x, dx, 1);
    addState(dx, ddx, 2);
  }
  void doUpdate() override {}

};


int main()
{
  /*
  std::cout << "Testing Simulation Kernel...\n\n";

  // Setting test inputs
  double max_time = 10;
  double time_step = 0.01;

  // Initial Values
  BlockTest* btest = new BlockTest();
  core::Block::pointer test = core::Block::pointer(btest);

  // Build Sim
  core::SimLoop sim(time_step, core::State::type::euler);
  sim.addEndCondition(core::EndCondition::pointer(new core::MaxTimeExceeded(max_time)));
  sim.addBlock(test);

  // Run Sim
  sim.run();

  // Reporting the End Result
  std::cout << "x:\t" << std::to_string(btest->x) << "\n";
  std::cout << "dx:\t" << std::to_string(btest->dx) << "\n";
  std::cout << "ddx:\t" << std::to_string(btest->ddx) << "\n";
  */

  nemesis::Mat<int, 2, 3> A({ 1, 2, 3,
                              4, 5, 6 });

  nemesis::Mat<int, 3, 2> B({ 1, 2,
                              3, 4,
                              5, 6 });
  return 0;
}