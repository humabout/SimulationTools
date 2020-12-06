// max_time_exceeded_test.cpp


// Inclusions
#include "../pch.h"
#include "../../Source/Kernel/End_Conditions/end_condition.h"
#include "../../Source/Kernel/End_Conditions/max_time_exceeded.h"
#include "../../Source/Kernel/End_Conditions/max_time_exceeded.cpp"


// Fixture
struct MaxTimeExceededTests : public ::testing::Test
{
  kernel::EndCondition* condition;
  kernel::StateEuler*   state;
  double* x;
  double* dx;

  virtual void SetUp()
  {
    // Setting up an state for propagating time
    x = new double;
    dx = new double;
    state = new kernel::StateEuler(*x, *dx);
    *x = 0;
    *dx = 1;
    state->initialize();
    state->reset(1);

    // Declaring the unit under test
    condition = new kernel::MaxTimeExceeded(1);
  }

  virtual void TearDown()
  {
    delete x;
    delete dx;
    delete state;
    delete condition;
  }
};


// Testing MaxTimeExceeded
TEST_F(MaxTimeExceededTests, EndConditionNotMetTest)
{
  EXPECT_FALSE(condition->met());
}
TEST_F(MaxTimeExceededTests, EndConditionMetTest)
{
  state->updateClock();
  EXPECT_TRUE(condition->met());
}

