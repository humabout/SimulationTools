// sim_loop_tests.cpp


// Inclusions
#include <memory>
#include "../pch.h"
#include "../../Source/Core/sim_loop.cpp"
#include "../../Source/Core/sim_loop.h"


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
    s1 = core::State::create(dy, ddy);
    s2 = core::State::create(z, dz);
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
    this->addState(y, s1);

    z = 0;    dz = 5;
    this->addState(s2);
    isInitialized = true;
  }
  void doUpdate(void) override final
  {
    isUpdated = true;
  }
};


// Fixture
struct SimLoopTests : public ::testing::Test
{
  core::EndCondition::pointer max_time;
  core::SimClock::pointer     clock;
  core::SimLoop::pointer      sim;

  virtual void SetUp()
  {
    clock = core::SimClock::create(core::SimClock::type::basic, 1.0);
    max_time = core::EndCondition::
  }

  virtual void TearDown() { }
};


