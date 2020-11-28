#include "../pch.h"
#include "../../Source/Utilities/Math/vector.h"
#include "../../Source/Utilities/Math/vector.cpp"


// Testing Union
TEST(VectorTests, DataArrayLetterTest)
{
  math::Vector test;
  test.e[0] = 1;
  test.e[1] = 2;
  test.e[2] = 3;
  EXPECT_DOUBLE_EQ(test.e[0], test.x);
  EXPECT_DOUBLE_EQ(test.e[1], test.y);
  EXPECT_DOUBLE_EQ(test.e[2], test.z);
}

TEST(VectorTests, DataArrayElementTest)
{
  math::Vector test;
  test.e[0] = 1;
  test.e[1] = 2;
  test.e[2] = 3;
  EXPECT_DOUBLE_EQ(test.e[0], test.e1);
  EXPECT_DOUBLE_EQ(test.e[1], test.e2);
  EXPECT_DOUBLE_EQ(test.e[2], test.e3);
}

TEST(VectorTests, DataLetterElementTest)
{
  math::Vector test;
  test.e[0] = 1;
  test.e[1] = 2;
  test.e[2] = 3;
  EXPECT_DOUBLE_EQ(test.x, test.e1);
  EXPECT_DOUBLE_EQ(test.y, test.e2);
  EXPECT_DOUBLE_EQ(test.z, test.e3);
}


// Testing Constructors
TEST(VectorTests, ConstructorDefaultTest)
{
  math::Vector test;
  EXPECT_DOUBLE_EQ(test.x, 0);
  EXPECT_DOUBLE_EQ(test.y, 0);
  EXPECT_DOUBLE_EQ(test.z, 0);
}

TEST(VectorTests, ConstructorElementwiseTest)
{
  math::Vector test(1, 2, 3);
  EXPECT_DOUBLE_EQ(test.x, 1);
  EXPECT_DOUBLE_EQ(test.y, 2);
  EXPECT_DOUBLE_EQ(test.z, 3);
}

TEST(VectorTests, ConstructorCopyTest)
{
  math::Vector copy(1, 2, 3);
  math::Vector test(copy);
  EXPECT_DOUBLE_EQ(test.x, 1);
  EXPECT_DOUBLE_EQ(test.y, 2);
  EXPECT_DOUBLE_EQ(test.z, 3);
}


// Accessor Tests
TEST(VectorTests, OperatorAccessorTest)
{
  math::Vector test(1, 2, 3);
  EXPECT_DOUBLE_EQ(test[0], 1);
  EXPECT_DOUBLE_EQ(test[1], 2);
  EXPECT_DOUBLE_EQ(test[2], 3);

  double e1 = 4;
  double e2 = 5;
  double e3 = 6;
  test[0] = e1;
  test[1] = e2; 
  test[2] = e3;
  EXPECT_DOUBLE_EQ(test.e1, e1);
  EXPECT_DOUBLE_EQ(test.e2, e2);
  EXPECT_DOUBLE_EQ(test.e3, e3);
}


// Assignment Operator Tests
TEST(VectorTests, OperatorAssignmentTest)
{
  math::Vector a(1, 2, 3);
  math::Vector b;
  b = a;
  EXPECT_DOUBLE_EQ(b.x, a.x);
  EXPECT_DOUBLE_EQ(b.y, a.y);
  EXPECT_DOUBLE_EQ(b.z, a.z);
}


// Setter Tests
TEST(VectorTests, SetterElementwiseTest)
{
  math::Vector test;
  test.set(1, 2, 3);
  EXPECT_DOUBLE_EQ(test.x, 1);
  EXPECT_DOUBLE_EQ(test.y, 2);
  EXPECT_DOUBLE_EQ(test.z, 3);
}


TEST(VectorTests, SetterVectorwiseTest)
{
  math::Vector values(1, 2, 3);
  math::Vector test;
  test.set(values);
  EXPECT_DOUBLE_EQ(test.x, 1);
  EXPECT_DOUBLE_EQ(test.y, 2);
  EXPECT_DOUBLE_EQ(test.z, 3);
}


// Comparison Operator Tests
// Unary Negative Test
// Addition Test
// Subtraction Test
// Scalar Multiplication Test
// Scalar Division Test
// Dot Product Test
// Cross Product Test
// Magnitude Test
// Normalization Test
// Zeroize Test