// state_euler_tests.cpp


// Inclusions
#include <cstddef>
#include <memory>
#include "../pch.h"
#include "../../Source/Kernel/state.h"
#include "../../Source/Kernel/state.cpp"
#include "../../Source/Kernel/States/state_euler.h"
#include "../../Source/Kernel/States/state_euler.cpp"


// Test Fixture
struct StateEulerTests : public ::testing::Test
{
  std::shared_ptr<kernel::StateEuler> test;
  std::shared_ptr<kernel::SimClock> clock;
  double x;
  double dx;

  virtual void SetUp()
  {
    x  = 0;
    dx = 1;
    test = std::shared_ptr<kernel::StateEuler>(new kernel::StateEuler(x, dx));
    clock = kernel::SimClock::create(kernel::SimClock::type::simple_synchronous);
  }

  virtual void TearDown()
  {
  }
};



// Initialization Tests
TEST_F(StateEulerTests, InitializationTest)
{
  test->initialize();
  EXPECT_TRUE(kernel::State::isReady());
}


// UpdateState Tests
TEST_F(StateEulerTests, UpdateStateTest)
{
  test->initialize();
  clock->initialize();
  clock->reset(1);

  test->updateState();
  EXPECT_DOUBLE_EQ(x, 1);
  EXPECT_DOUBLE_EQ(dx, 1);
  EXPECT_TRUE(kernel::State::isReady());

  test->updateState();
  EXPECT_DOUBLE_EQ(x, 2);
  EXPECT_DOUBLE_EQ(dx, 1);
  EXPECT_TRUE(kernel::State::isReady());
}
