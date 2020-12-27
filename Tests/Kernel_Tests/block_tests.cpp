// block_tests.cpp


// Inclusions
#include "../pch.h"
#include "../../Source/core/Clocks/sim_clock.h"
#include "../../Source/core/Clocks/sim_clock.cpp"
#include "../../Source/core/block.h"
#include "../../Source/core/block.cpp"


// Making a Test Block
class BlockTest : public core::Block
{
public:
  double x;
  double dx;
  double y;
  double dy;
  double ddy;
  double z;
  double dz;
  bool isInitialized;
  bool isUpdated;

  BlockTest()
  {
    isInitialized = false;
    isUpdated = false;
  }
  BlockTest(const BlockTest& that)
  {
    this->States = that.States;
  }
  ~BlockTest()
  {
    // Does Nothing
  };

private:
  void doInitialize(void) override final
  {
    x = 0;    dx = 1;
    this->addState(x, dx, 1);

    y = 10;   dy = -1;  ddy = 0;
    this->addState(dy, ddy, 2);
    this->addState(y, dy, 1);

    z = 0;    dz = 5;
    this->addState(z, dz, 1);
    isInitialized = true;
  }
  void doUpdate(void) override final
  {
    isUpdated = true;
  }
};

// Fixture
struct BlockTests : public ::testing::Test
{
  std::shared_ptr<core::SimClock> clock;
  std::shared_ptr<BlockTest> test;

  virtual void SetUp()
  {
    test = std::shared_ptr<BlockTest>(new BlockTest);
    clock = core::SimClock::create(core::SimClock::type::basic, 1.0);
  }

  virtual void TearDown()
  {
    // Does Nothing
  }
};


// Initialize Test
TEST_F(BlockTests, InitializeTest)
{
  test->initialize();
  EXPECT_TRUE(test->isInitialized);
}


// Update Test
TEST_F(BlockTests, UpdateTest)
{
  test->update();
  EXPECT_TRUE(test->isUpdated);
}


// Propagate Tests
TEST_F(BlockTests, PropagateTest)
{
  clock->initialize();

  test->initialize();
  test->propagate();

  EXPECT_DOUBLE_EQ(test->x, 1);
  EXPECT_DOUBLE_EQ(test->dx, 1);
  EXPECT_DOUBLE_EQ(test->y, 9);
  EXPECT_DOUBLE_EQ(test->dy, -1);
  EXPECT_DOUBLE_EQ(test->z, 5);
}