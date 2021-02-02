// sim_loop_tests.cpp


// Inclusions
#include <memory>
#include "../pch.h"
#include "../../Source/Core/sim_loop.cpp"
#include "../../Source/Core/sim_loop.h"
#include "../../Source/Core/End_Conditions/max_time_exceeded.h"
#include "../../Source/Models/Examples/position.h"
#include "../../Source/Models/Examples/position.cpp"

#include "../../Source/Core/block.h"
#include "../../Source/Core/block.cpp"

#include "../../Source/Core/Integrators/integrator.h"
#include "../../Source/Core/Integrators/integrator.cpp"
#include "../../Source/Core/Integrators/state.h"
#include "../../Source/Core/Integrators/state.cpp"
#include "../../Source/Core/Integrators/euler.h"
#include "../../Source/Core/Integrators/euler.cpp"


// Fixture
struct SimLoopTests : public ::testing::Test
{
  nemesis::SimLoop::pointer sim;

  double max_tick;
  double max_time;
  double time_step;
  double x;
  double dx;
  double ddx;

  virtual void SetUp()
  {
    max_tick = 0.01;
    max_time = 10.0;

    sim.reset(new nemesis::SimLoop(max_tick));
  }

  virtual void TearDown() {}
};


TEST_F(SimLoopTests, SetupWithAddFooTest)
{
  sim->addBlock(nemesis::Block::pointer(new nemesis::examples::Position(x, dx, ddx)));
  sim->addEndCondition(nemesis::EndCondition::pointer(new nemesis::MaxTimeExceeded(max_time)));

  sim->run();

  EXPECT_DOUBLE_EQ(ddx, 1);
  EXPECT_NEAR(dx, 10, 1e-6);
  EXPECT_NEAR(x, 50, 0.1);
}