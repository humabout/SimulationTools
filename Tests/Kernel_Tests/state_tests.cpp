// state_tests.cpp


// Inclusions
#include "../pch.h"
#include "../../Source/Core/Integrators/state.h"
#include "../../Source/Core/Integrators/state.cpp"


// Fixture
struct StateTests : public ::testing::Test
{
  double x;
  double dx;
  nemesis::State a;
  nemesis::State b;

  virtual void SetUp()
  {
    x  = 3;
    dx = 2;

    a = nemesis::State::State(x, dx);
    b = nemesis::State::State(dx, x);
  }

  virtual void TearDown() {}
};


// Verifying Correct Construction
TEST_F(StateTests, FactoryTest)
{
  EXPECT_DOUBLE_EQ(a.x(), x);
  EXPECT_DOUBLE_EQ(a.dx(), dx);
  EXPECT_DOUBLE_EQ(a.order(), 1);
}

// Veryifying Access
TEST_F(StateTests, AccessTest)
{
  a.x()     = 1;
  a.dx()    = 2;
  a.order() = 3;

  EXPECT_DOUBLE_EQ(a.x(),     1);
  EXPECT_DOUBLE_EQ(a.dx(),    2);
  EXPECT_DOUBLE_EQ(a.order(), 3);
}

// Equality Test
TEST_F(StateTests, ComparisonEqualityTest1)
{
  a.order() = 1;
  b.order() = 1;
  EXPECT_TRUE(a == b);
}
TEST_F(StateTests, ComparisonEqualityTest2)
{
  a.order() = 1;
  b.order() = 2;
  EXPECT_FALSE(a == b);
}

// Inequality Test
TEST_F(StateTests, ComparisonInequalityTest1)
{
  a.order() = 1;
  b.order() = 2;
  EXPECT_TRUE(a != b);
}
TEST_F(StateTests, ComparisonInequalityTest2)
{
  a.order() = 1;
  b.order() = 1;
  EXPECT_FALSE(a != b);
}

// Greater Than Test
TEST_F(StateTests, ComparisonGreaterThanTest1)
{
  a.order() = 1;
  b.order() = 1;
  EXPECT_FALSE(a > b);
}
TEST_F(StateTests, ComparisonGreaterThanTest2)
{
  a.order() = 1;
  b.order() = 2;
  EXPECT_FALSE(a > b);
}
TEST_F(StateTests, ComparisonGreaterThanTest3)
{
  a.order() = 2;
  b.order() = 1;
  EXPECT_TRUE(a > b);
}

// Greater Than or Equal Test
TEST_F(StateTests, ComparisonGreaterEqualTest1)
{
  a.order() = 1;
  b.order() = 1;
  EXPECT_TRUE(a >= b);
}
TEST_F(StateTests, ComparisonGreaterEqualTest2)
{
  a.order() = 1;
  b.order() = 2;
  EXPECT_FALSE(a >= b);
}
TEST_F(StateTests, ComparisonGreaterEqualTest3)
{
  a.order() = 2;
  b.order() = 1;
  EXPECT_TRUE(a >= b);
}

// Less Than Test
TEST_F(StateTests, ComparisonLessThanTest1)
{
  a.order() = 1;
  b.order() = 1;
  EXPECT_FALSE(a < b);
}
TEST_F(StateTests, ComparisonLessThanTest2)
{
  a.order() = 1;
  b.order() = 2;
  EXPECT_TRUE(a < b);
}
TEST_F(StateTests, ComparisonLessThanTest3)
{
  a.order() = 2;
  b.order() = 1;
  EXPECT_FALSE(a < b);
}

// Less Than or Equal Test
TEST_F(StateTests, ComparisonLessEqualTest1)
{
  a.order() = 1;
  b.order() = 1;
  EXPECT_TRUE(a <= b);
}
TEST_F(StateTests, ComparisonLessEqualTest2)
{
  a.order() = 1;
  b.order() = 2;
  EXPECT_TRUE(a <= b);
}
TEST_F(StateTests, ComparisonLessEqualTest3)
{
  a.order() = 2;
  b.order() = 1;
  EXPECT_FALSE(a <= b);
}