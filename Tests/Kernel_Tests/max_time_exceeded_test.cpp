// max_time_exceeded_test.cpp


// Inclusions
#include <memory>
#include "../pch.h"
#include "../../Source/Kernel/End_Conditions/end_condition.h"
#include "../../Source/Kernel/End_Conditions/max_time_exceeded.h"
#include "../../Source/Kernel/End_Conditions/max_time_exceeded.cpp"


// Fixture
struct MaxTimeExceededTests : public ::testing::Test
{
  std::shared_ptr<kernel::EndCondition> condition;
  std::shared_ptr<kernel::SimClock> clock;

  virtual void SetUp()
  {
    // Setting up an state for propagating time
    clock = kernel::SimClock::create(kernel::SimClock::type::simple_synchronous);

    // Declaring the unit under test
    condition = std::shared_ptr <kernel::EndCondition>(new kernel::MaxTimeExceeded(1));
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

