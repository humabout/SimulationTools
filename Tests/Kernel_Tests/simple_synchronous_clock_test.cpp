// simple_synchronous_clock_test.cpp


// Inclusion
#include <memory>
#include "../pch.h"
#include "../../Source/Core/Clocks/simple_synchronous_clock.h"
#include "../../Source/Core/Clocks/simple_synchronous_clock.cpp"


struct SimpleSynchronousClockTests : public ::testing::Test
{
  std::shared_ptr<core::SimClock> clock;

  virtual void SetUp()
  {
    clock = core::SimClock::create(core::SimClock::type::simple_synchronous);
  }

  virtual void TearDown()
  {
  }
};



// Correct Instantiation
TEST_F(SimpleSynchronousClockTests, CorrectInstantiationTest)
{
  EXPECT_DOUBLE_EQ(core::SimClock::time(), 0.0);
  EXPECT_DOUBLE_EQ(core::SimClock::timestep(), 0.0);
}

// Reset
TEST_F(SimpleSynchronousClockTests, SetMaxTimestepTest)
{
  EXPECT_DOUBLE_EQ(core::SimClock::timestep(), 0.0);

  clock->reset(1);
  EXPECT_DOUBLE_EQ(core::SimClock::timestep(), 1.0);

  clock->reset(5.5);
  EXPECT_DOUBLE_EQ(core::SimClock::timestep(), 5.5);
}

// Advance
TEST_F(SimpleSynchronousClockTests, AdvanceClockTest)
{
  clock->initialize();
  EXPECT_DOUBLE_EQ(core::SimClock::time(), 0.0);
    
  clock->reset(1);
  clock->advance();
  EXPECT_DOUBLE_EQ(core::SimClock::time(), 1.0);

  clock->advance();
  EXPECT_DOUBLE_EQ(core::SimClock::time(), 2.0);

  clock->reset(2);
  clock->advance();
  EXPECT_DOUBLE_EQ(core::SimClock::time(), 4.0);
}


// Initialize
TEST_F(SimpleSynchronousClockTests, InitializeClockTest)
{
  clock->reset(1);
  clock->advance();
  clock->advance();
  clock->advance();
  clock->advance();
  EXPECT_DOUBLE_EQ(core::SimClock::time(), 4.0);


  clock->initialize();
  EXPECT_DOUBLE_EQ(core::SimClock::time(), 0.0);
}