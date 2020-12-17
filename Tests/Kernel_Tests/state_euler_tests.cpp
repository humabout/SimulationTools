// state_euler_tests.cpp


// Inclusions
#include <cstddef>
#include <memory>
#include "../pch.h"
#include "../../Source/Core/state.h"
#include "../../Source/Core/state.cpp"
#include "../../Source/Core/States/state_euler.h"
#include "../../Source/Core/States/state_euler.cpp"


// Test Fixture
struct StateEulerTests : public ::testing::Test
{
  std::shared_ptr<core::StateEuler> test;
  std::shared_ptr<core::SimClock> clock;
  double x;
  double dx;

  virtual void SetUp()
  {
    x  = 0;
    dx = 1;
    test = std::shared_ptr<core::StateEuler>(new core::StateEuler(x, dx));
    clock = core::SimClock::create(core::SimClock::type::basic);
  }

  virtual void TearDown()
  {
  }
};



// Initialization Tests
TEST_F(StateEulerTests, InitializationTest)
{
  test->initialize();
  EXPECT_TRUE(core::State::isReady());
}


// UpdateState Tests
TEST_F(StateEulerTests, UpdateStateTest)
{
  test->initialize();
  clock->initialize();
  clock->setMaxTick(1);

  test->updateState();
  EXPECT_DOUBLE_EQ(x, 1);
  EXPECT_DOUBLE_EQ(dx, 1);
  EXPECT_TRUE(core::State::isReady());

  test->updateState();
  EXPECT_DOUBLE_EQ(x, 2);
  EXPECT_DOUBLE_EQ(dx, 1);
  EXPECT_TRUE(core::State::isReady());
}
