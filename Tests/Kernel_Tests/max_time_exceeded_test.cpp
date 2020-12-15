// max_time_exceeded_test.cpp


// Inclusions
#include <memory>
#include "../pch.h"
#include "../../Source/Core/End_Conditions/end_condition.h"
#include "../../Source/Core/End_Conditions/max_time_exceeded.h"
#include "../../Source/Core/End_Conditions/max_time_exceeded.cpp"


// Fixture
struct MaxTimeExceededTests : public ::testing::Test
{
  std::shared_ptr<core::EndCondition> condition;
  std::shared_ptr<core::SimClock> clock;

  virtual void SetUp()
  {
    // Setting up an state for propagating time
    clock = core::SimClock::create(core::SimClock::type::basic);

    // Declaring the unit under test
    condition = std::shared_ptr <core::EndCondition>(new core::MaxTimeExceeded(1));
  }

  virtual void TearDown()
  {
  }
};


// Testing MaxTimeExceeded
TEST_F(MaxTimeExceededTests, EndConditionNotMetTest)
{
  EXPECT_FALSE(condition->met());
}
TEST_F(MaxTimeExceededTests, EndConditionMetTest)
{
  clock->initialize();
  clock->reset(2);
  clock->advance();
  EXPECT_TRUE(condition->met());
}

