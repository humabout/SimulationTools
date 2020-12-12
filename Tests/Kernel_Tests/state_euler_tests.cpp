// state_euler_tests.cpp


// Inclusions
#include <cstddef>
#include "../pch.h"
#include "../../Source/Kernel/state.h"
#include "../../Source/Kernel/state.cpp"
#include "../../Source/Kernel/States/state_euler.h"
#include "../../Source/Kernel/States/state_euler.cpp"


// Test Fixture
struct StateEulerTests : public ::testing::Test
{
  kernel::StateEuler* test;
  double* x;
  double* dx;

  virtual void SetUp()
  {
    x  = new double;
    dx = new double;
    test = new kernel::StateEuler(*x, *dx);
    *x  = 0;
    *dx = 1;
  }

  virtual void TearDown()
  {
    delete x;
    delete dx;
    delete test;
  }
};


// Reset Tests
TEST_F(StateEulerTests, ResetTest)
{
  test->reset(0.1);
  EXPECT_DOUBLE_EQ(kernel::State::timestep(), 0.1);
}



// UpdateClock Tests
TEST_F(StateEulerTests, UpdateClockTest)
{
  test->reset(0.1);
  test->initialize();
  EXPECT_DOUBLE_EQ(kernel::State::time(), 0.0);

  test->updateClock();
  EXPECT_DOUBLE_EQ(kernel::State::time(), 0.1);

  test->updateClock();
  EXPECT_DOUBLE_EQ(kernel::State::time(), 0.2);

  test->updateClock();
  EXPECT_DOUBLE_EQ(kernel::State::time(), 0.3);
}


// Initialization Tests
TEST_F(StateEulerTests, InitializationTest)
{
  test->reset(0.1);
  test->updateClock();

  test->initialize();
  EXPECT_TRUE(kernel::State::isReady());
  EXPECT_DOUBLE_EQ(kernel::State::time(), 0.0);
}


// UpdateState Tests
TEST_F(StateEulerTests, UpdateStateTest)
{
  test->initialize();
  test->reset(1);

  test->updateState();
  EXPECT_DOUBLE_EQ(*x, 1);
  EXPECT_DOUBLE_EQ(*dx, 1);
  EXPECT_TRUE(kernel::State::isReady());

  test->updateState();
  EXPECT_DOUBLE_EQ(*x, 2);
  EXPECT_DOUBLE_EQ(*dx, 1);
  EXPECT_TRUE(kernel::State::isReady());
}