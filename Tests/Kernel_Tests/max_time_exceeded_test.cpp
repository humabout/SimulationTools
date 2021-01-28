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
  std::shared_ptr<nemesis::EndCondition> condition;
  std::shared_ptr<nemesis::SimClock> clock;

  virtual void SetUp()
  {
    // Setting up an state for propagating time
    clock = nemesis::SimClock::create(nemesis::SimClock::type::basic, 2);

    // Declaring the unit under test
    condition = std::shared_ptr <nemesis::EndCondition>(new nemesis::MaxTimeExceeded(1));
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
  clock->advance();
  EXPECT_TRUE(condition->met());
}

