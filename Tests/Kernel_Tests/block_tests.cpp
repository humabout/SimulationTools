// block_tests.cpp


// Inclusions
#include "../pch.h"
#include "../../Source/core/block.h"
#include "../../Source/core/block.cpp"
#include "../../Source/core/Clocks/sim_clock.h"
#include "../../Source/core/Clocks/sim_clock.cpp"


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
  std::shared_ptr<core::State> s1;
  std::shared_ptr<core::State> s2;

  BlockTest()
  {
    isInitialized = false;
    isUpdated = false;
  }
  BlockTest(const BlockTest& that)
  {
    this->States = that.States;
  }
  ~BlockTest() { core::Block::~Block(); };

private:
  void doInitialize(void) override final
  {
    x = 0;    dx = 1;
    this->addState(x, dx);

    y = 10;   dy = -1;  ddy = 0;
    this->addState(dy, ddy);
    this->addState(y, dy);

    z = 0;    dz = 5;
    this->addState(z, dz);
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
  BlockTest* test;

  virtual void SetUp()
  {
    test = new BlockTest;
    clock = core::SimClock::create(core::SimClock::type::basic, 1.0);
  }

  virtual void TearDown()
  {
    if (test != nullptr) { delete test; }
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