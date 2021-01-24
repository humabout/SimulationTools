// main.cpp

// This just exists for rapid testing

#include <iostream>
#include <memory>
#include <string>
#include "nemesis.h"

/*
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
    core::State::pointer dX = core::State::create(dx, ddx);
    addState(dX);
    addState(x, dX);

  }
  void doUpdate() override {}

};
*/



//------------------------------------------------------------------------------
// Name:    getLowerIndex
// Purpose: This returns the index of the closest value to the key that is less
//          than or equal to the key.
//------------------------------------------------------------------------------
std::size_t getLowerIndex(double key, std::vector<double> Keys)
{
  // Checking if the key is bounded within the list of keys
  if (Keys.back()  < key ||
      Keys.front() > key)
  {
    throw std::runtime_error("Invalid key encountered. Key does not exist on the table.");
  }
  else
  {
    // Continue
  }

  // Finding the index of the appropriate value
  std::size_t upper = Keys.size();
  std::size_t lower = 0;
  std::size_t guess = static_cast<std::size_t>(0.5 * (upper + lower));
  while (true)
  {
    if (Keys[guess] == key)
    {
      return guess;
    }
    else if (Keys[guess] > key)
    {
      upper = guess;
      guess = static_cast<std::size_t>(0.5 * (upper + lower));
    }
    else
    {
      lower = guess;
      guess = static_cast<std::size_t>(0.5 * (upper + lower));
    }
  }
}


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

  std::vector<double> KeyTable({ 1,2,3,4,5,6,7,8,9,10,11,12 });
  double key = 1;

  std::size_t index;
  try
  {
    index = getLowerIndex(key, KeyTable);
    std::cout << "Lookup:\t" << key;
    std::cout << "\nIndex:\t" << index;
    std::cout << "\nValue:\t" << KeyTable[index];
    std::cout << std::endl;
  }
  catch (std::exception& e)
  {
    std::cout << e.what() << std::endl;
  }


  return 0;
}