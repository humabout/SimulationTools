// sim_loop_tests.cpp


// Inclusions
#include <memory>
#include "../pch.h"
#include "../../Source/Core/sim_loop.cpp"
#include "../../Source/Core/sim_loop.h"
#include "../../Source/Core/End_Conditions/max_time_exceeded.h"

// Making a Test Block
class LoopBlockTest : public core::Block
{
public:
  double* x;
  double* dx;
  double* ddx;
  bool isInitialized;
  bool isUpdated;

  LoopBlockTest(double& x_, double& dx_, double& ddx_)
  {
    this->x = &x_;
    this->dx = &dx_;
    this->ddx = &ddx_;

    isInitialized = false;
    isUpdated = false;
  }
  ~LoopBlockTest()
  {
    // Does Nothing
  };

private:
  void doInitialize(void) override final
  {

    *x = 0;
    *dx = 0;
    *ddx = 1;

    core::State::pointer state = core::State::create(*dx, *ddx);
    this->addState(*x, *dx, 1);
    this->addState(*dx, *ddx, 2);

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
  core::Block::pointer        block;
  std::shared_ptr<LoopBlockTest>  access;
  core::SimLoop::pointer      sim;
  double                      max_tick;
  double x;
  double dx;
  double ddx;

  virtual void SetUp()
  {
    max_tick = 0.01;

    core::Block* block_ptr = new LoopBlockTest(x, dx, ddx);
    block = core::Block::pointer(block_ptr);

    clock = core::SimClock::create( core::SimClock::type::basic, 1.0 );

    core::EndCondition* max_time_ptr = new core::MaxTimeExceeded(10.0);
    max_time = core::EndCondition::pointer(max_time_ptr);

    sim = nullptr;
  }

  virtual void TearDown() { }
};


TEST_F(SimLoopTests, SetupWithAddFooTest)
{
  core::SimLoop* sim_ptr = new core::SimLoop(max_tick);
  sim = core::SimLoop::pointer( sim_ptr );
  sim->addBlock(block);
  sim->addEndCondition(max_time);

  sim->run();

  EXPECT_DOUBLE_EQ(ddx, 1);
  EXPECT_NEAR(dx, 10, 1e-6);
  EXPECT_NEAR(x, 50, 0.1);
}


TEST_F(SimLoopTests, SetupWithOperatorsTest)
{
  core::SimLoop* sim_ptr = new core::SimLoop(max_tick);
  sim = core::SimLoop::pointer(sim_ptr);
  *sim << block;
  *sim << max_time;

  sim->run();

  EXPECT_DOUBLE_EQ(ddx, 1);
  EXPECT_NEAR(dx, 10, 1e-6);
  EXPECT_NEAR(x, 50, 0.1);
}