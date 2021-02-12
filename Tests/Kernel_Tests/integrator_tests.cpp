// integrator_tests.cpp


// Inclusions
#include <vector>
#include "../pch.h"
#include "../../Source/Core/Integrators/euler.h"
#include "../../Source/Core/Integrators/euler.cpp"
#include "../../Source/Core/Integrators/integrator.h"
#include "../../Source/Core/Integrators/integrator.cpp"
#include "../../Source/Core/sim_loop.h"
#include "../../Source/Core/sim_loop.cpp"

#include "../../Source/Core/block.h"
#include "../../Source/Core/block.cpp"


// Sample Integrator Class to Test Internals
namespace nemesis
{
  class IntegratorTest : public Integrator
  {
  public:
    // Required Functions
    IntegratorTest() {}
    ~IntegratorTest() {}
    void doUpdateStates(void) {}

    // Access to Integrator Internals
    std::vector<unsigned int>  getStateOrders(void)
    {
      std::vector<unsigned int> out;
      for (state_list::iterator state = States.begin();
        state != States.end();
        ++state)
      {
        out.push_back((*state).second.order());
      }
      return out;
    }

  };
}


// Test Fixture
struct IntegratorTests : public ::testing::Test 
{
  nemesis::IntegratorTest test;
  nemesis::SimLoop::pointer sim;

  virtual void SetUp()
  {
    sim = nemesis::SimLoop::pointer( new nemesis::SimLoop(1) );
  }
  virtual void TearDown() {}
};


// Testing Factory Method
TEST_F(IntegratorTests, FactoryEulerTest)
{
  nemesis::Integrator* euler = nemesis::Integrator::create(nemesis::Integrator::type::euler, sim.get());
  bool fail = (dynamic_cast<nemesis::Euler*>(euler) == NULL);
  EXPECT_TRUE(!fail);
}

// AddState Test
TEST_F(IntegratorTests, AddStateTest)
{
  double a = 0;
  double b = 1;
  double c = 2;
  double d = 3;

  // 2nd Order Derivative
  test.addState(b, c);
  // 3rd Order Derivative
  test.addState(c, d);
  // 1st Order Derivative
  test.addState(a, b);

  // Testing order of state orders
  std::vector<unsigned int> orders = test.getStateOrders();
  EXPECT_EQ(orders[0], 3); // expected 3
  EXPECT_EQ(orders[1], 2); // expected 2
  EXPECT_EQ(orders[2], 1); // expected 1
}
