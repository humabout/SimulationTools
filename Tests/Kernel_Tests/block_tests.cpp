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
  ~BlockTest() { core::Block::~Block(); };

private:
  void doInitialize(void) override final
  {
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
  double x;
  double dx;
  double y;
  double dy;
  double ddy;
  double z;
  double dz;
  
  std::shared_ptr<core::State> s1;
  std::shared_ptr<core::State> s2;
  std::shared_ptr<core::SimClock> clock;
  BlockTest* test;

  virtual void SetUp()
  {
    test = new BlockTest;
    clock = core::SimClock::create(core::SimClock::type::basic);
    s1 = core::State::create(dy, ddy);
    s2 = core::State::create(z, dz);
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
  s1->initialize();
  clock->setMaxTick(1);

  x = 0;    dx = 1;
  test->add(x, dx);

  y = 10;   dy = -1;  ddy = 0;
  test->add(y, s1);

  z = 0;    dz = 5;
  test->add(s2);
  test->propagate();

  EXPECT_DOUBLE_EQ(x, 1);
  EXPECT_DOUBLE_EQ(dx, 1);
  EXPECT_DOUBLE_EQ(y, 9);
  EXPECT_DOUBLE_EQ(dy, -1);
  EXPECT_DOUBLE_EQ(z, 5);
}