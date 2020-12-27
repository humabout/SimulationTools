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
  core::State::pointer test;
  std::shared_ptr<core::SimClock> clock;
  double x;
  double dx;

  virtual void SetUp()
  {
    x  = 0;
    dx = 1;
    test = core::State::pointer(new core::StateEuler<double>(x, dx));
    clock = core::SimClock::create(core::SimClock::type::basic, 1.0);
  }

  virtual void TearDown()
  {
  }
};

// UpdateState Tests
TEST_F(StateEulerTests, UpdateStateTest)
{
  clock->initialize();

  test->propagate();
  EXPECT_DOUBLE_EQ(x, 1);
  EXPECT_DOUBLE_EQ(dx, 1);
  EXPECT_TRUE(core::State::isReady());

  test->propagate();
  EXPECT_DOUBLE_EQ(x, 2);
  EXPECT_DOUBLE_EQ(dx, 1);
  EXPECT_TRUE(core::State::isReady());
}
