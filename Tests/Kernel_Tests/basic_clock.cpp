// simple_synchronous_clock_test.cpp


// Inclusion
#include <memory>
#include "../pch.h"
#include "../../Source/Core/Clocks/basic_clock.h"
#include "../../Source/Core/Clocks/basic_clock.cpp"


struct BasicClockClockTests : public ::testing::Test
{
  std::shared_ptr<nemesis::SimClock> clock;
  double tick;

  virtual void SetUp()
  {
    tick = 1.0;
    clock = nemesis::SimClock::create(nemesis::SimClock::type::basic, tick);
  }

  virtual void TearDown()
  {
  }
};



// Correct Instantiation
TEST_F(BasicClockClockTests, CorrectInstantiationTest)
{
  EXPECT_DOUBLE_EQ(nemesis::SimClock::time(), 0.0);
  EXPECT_DOUBLE_EQ(nemesis::SimClock::tick(), 1.0);
}

// Reset
TEST_F(BasicClockClockTests, SetMaxTimestepTest)
{
  EXPECT_DOUBLE_EQ(nemesis::SimClock::tick(), 1.0);

  nemesis::SimClock::pointer test_5_5 = nemesis::SimClock::create(nemesis::SimClock::type::basic, 5.5);
  EXPECT_DOUBLE_EQ(nemesis::SimClock::tick(), 5.5);
}

// Advance
TEST_F(BasicClockClockTests, AdvanceClockTest)
{
  clock->initialize();
  EXPECT_DOUBLE_EQ(nemesis::SimClock::time(), 0.0);
    
  clock->advance();
  EXPECT_DOUBLE_EQ(nemesis::SimClock::time(), 1.0);

  clock->advance();
  EXPECT_DOUBLE_EQ(nemesis::SimClock::time(), 2.0);

  clock->advance();
  clock->advance();
  EXPECT_DOUBLE_EQ(nemesis::SimClock::time(), 4.0);
}


// Initialize
TEST_F(BasicClockClockTests, InitializeClockTest)
{
  clock->advance();
  clock->advance();
  clock->advance();
  clock->advance();
  clock->initialize();
  EXPECT_DOUBLE_EQ(nemesis::SimClock::time(), 0.0);
}