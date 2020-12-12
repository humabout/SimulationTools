// block_tests.cpp


// Inclusions
#include "../pch.h"
#include "../../Source/Kernel/block.h"
#include "../../Source/Kernel/block.cpp"


// Making a Test Block
class BlockTest : public kernel::Block
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
  double y;
  double dx;
  double dy;

  kernel::State* s1;
  kernel::State* s2;
  BlockTest* test;

  virtual void SetUp()
  {
    x = 0;
    y = 10;
    dx = 1;
    dy = -1;
    s1 = kernel::State::create(x, dx);
    s2 = kernel::State::create(y, dy);
    test = new BlockTest;
  }

  virtual void TearDown()
  {
    if (test != NULL) { delete test; }
    if (s1   != NULL) { delete s1; }
    if (s2   != NULL) { delete s2; }
  }
};