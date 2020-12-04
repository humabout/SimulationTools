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
  math::Vector b = a;
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
TEST(VectorTests, OperatorIsEqualTest1)
{
  math::Vector a(1, 2, 3);
  math::Vector b(a);
  EXPECT_TRUE(a == b);
}
TEST(VectorTests, OperatorIsEqualTest2)
{
  math::Vector a(1, 2, 3);
  math::Vector b(a);
  b.e1 = 9;
  EXPECT_FALSE(a == b);
}
TEST(VectorTests, OperatorIsEqualTest3)
{
  math::Vector a(1, 2, 3);
  math::Vector b(a);
  b.e2 = 9;
  EXPECT_FALSE(a == b);
}
TEST(VectorTests, OperatorIsEqualTest4)
{
  math::Vector a(1, 2, 3);
  math::Vector b(a);
  b.e3 = 9;
  EXPECT_FALSE(a == b);
}


// Unary Negative Test
TEST(VectorTests, OperatorUnaryMinusTest)
{
  math::Vector test(1, 2, 3);
  test = -test;
  EXPECT_DOUBLE_EQ(test.x, -1);
  EXPECT_DOUBLE_EQ(test.y, -2);
  EXPECT_DOUBLE_EQ(test.z, -3);
}


// Addition Test
TEST(VectorTests, AdditionTest1)
{
  math::Vector u(1, 2, 3);
  math::Vector v(4, 5, 6);
  math::Vector w(5, 7, 9);
  EXPECT_TRUE((u + v) == w);
}
TEST(VectorTests, AdditionTest2)
{
  math::Vector u(1, 2, 3);
  math::Vector v(4, 5, 6);
  math::Vector w = u + v;
  u += v;
  EXPECT_TRUE(u == w);
}
TEST(VectorTests, AdditionTest3)
{
  math::Vector u(1, 2, 3);
  math::Vector v(4, 5, 6);
  EXPECT_TRUE((u + v) == (v + u));
}


// Subtraction Test
TEST(VectorTests, SubtractionTest1)
{
  math::Vector u(1, 2, 3);
  math::Vector v(4, 5, 6);
  math::Vector w(-3, -3, -3);
  EXPECT_TRUE((u - v) == w);
}
TEST(VectorTests, SubtractionTest2)
{
  math::Vector u(1, 2, 3);
  math::Vector v(4, 5, 6);
  math::Vector w = u - v;
  u -= v;
  EXPECT_TRUE(u == w);
}


// Scalar Multiplication Test
TEST(VectorTests, ScalarMultiplicationTest1)
{
  math::Vector u(1, 2, 3);
  math::Vector v(2, 4, 6);
  double s = 2;
  EXPECT_TRUE(u * s == v);
}
TEST(VectorTests, ScalarMultiplicationTest2)
{
  math::Vector u(1, 2, 3);
  math::Vector v(2, 4, 6);
  double s = 2;
  EXPECT_TRUE(s * u == v);
}
TEST(VectorTests, ScalarMultiplicationTest3)
{
  math::Vector u(1, 2, 3);
  math::Vector v(2, 4, 6);
  double s = 2;
  u *= s;
  EXPECT_TRUE(u == v);
}


// Scalar Division Test
TEST(VectorTests, ScalarDivisionTest1)
{
  math::Vector u(2, 4, 6);
  math::Vector v(1, 2, 3);
  double s = 2;
  EXPECT_TRUE(u / s == v);
}
TEST(VectorTests, ScalarDivisionTest2)
{
  math::Vector u(2, 4, 6);
  math::Vector v(1, 2, 3);
  double s = 2;
  u /= s;
  EXPECT_TRUE(u == v);
}
TEST(VectorTests, DivideByZeroTest)
{
  math::Vector u(1, 2, 3);
  double s = 0;
  EXPECT_THROW(u / s, std::runtime_error);
}

// Dot Product Test
TEST(VectorTests, DotProductTest1)
{
  math::Vector u(1, 2, 3);
  math::Vector v(4, 5, 6);
  EXPECT_DOUBLE_EQ(u.dot(v), 32);
}
TEST(VectorTests, DotProductTest2)
{
  math::Vector u(1, 2, 3);
  math::Vector v(4, 5, 6);
  EXPECT_DOUBLE_EQ(u * v, 32);
}
TEST(VectorTests, DotProductTest3)
{
  math::Vector u(1, 2, 3);
  math::Vector v(4, 5, 6);
  EXPECT_DOUBLE_EQ(u * -v, -32);
}
TEST(VectorTests, DotProductTest4)
{
  math::Vector u(1, 2, 3);
  math::Vector v(4, 5, 6);
  EXPECT_DOUBLE_EQ(-u * v, -32);
}
TEST(VectorTests, DotProductTest5)
{
  math::Vector u(1, 2, 3);
  math::Vector v(4, 5, 6);
  EXPECT_DOUBLE_EQ(u.dot(v), (u * v));
}


// Cross Product Test
TEST(VectorTests, CrossProductTest1)
{
  math::Vector i(1, 0, 0);
  math::Vector j(0, 1, 0);
  math::Vector k(0, 0, 1);
  
  EXPECT_TRUE(i.cross(j) == k);
}
TEST(VectorTests, CrossProductTest2)
{
  math::Vector i(1, 0, 0);
  math::Vector j(0, 1, 0);
  math::Vector k(0, 0, 1);

  EXPECT_TRUE(j.cross(k) == i);
}
TEST(VectorTests, CrossProductTest3)
{
  math::Vector i(1, 0, 0);
  math::Vector j(0, 1, 0);
  math::Vector k(0, 0, 1);

  EXPECT_TRUE(k.cross(i) == j);
}
TEST(VectorTests, CrossProductTest4)
{
  math::Vector i(1, 0, 0);
  math::Vector j(0, 1, 0);
  math::Vector k(0, 0, 1);

  EXPECT_TRUE(k.cross(j) == -i);
}
TEST(VectorTests, CrossProductTest5)
{
  math::Vector i(1, 0, 0);
  math::Vector j(0, 1, 0);
  math::Vector k(0, 0, 1);

  EXPECT_TRUE(i.cross(k) == -j);
}
TEST(VectorTests, CrossProductTest6)
{
  math::Vector i(1, 0, 0);
  math::Vector j(0, 1, 0);
  math::Vector k(0, 0, 1);

  EXPECT_TRUE(j.cross(i) == -k);
}
TEST(VectorTests, CrossProductTest7)
{
  math::Vector u(1, 2, 3);
  math::Vector v(4, 5, 6);

  EXPECT_TRUE(u.cross(v) == (u % v));
}
TEST(VectorTests, CrossProductTest8)
{
  math::Vector u(1, 2, 3);
  math::Vector v(4, 5, 6);
  math::Vector w;
  w = u % v;
  u %= v;

  EXPECT_TRUE(u == w);
}


// Magnitude Test
TEST(VectorTests, MagnitudeTest1)
{
  math::Vector test;
  EXPECT_DOUBLE_EQ(test.magnitude(), 0);
}
TEST(VectorTests, MagnitudeTest2)
{
  math::Vector test(10, 0, 0);
  EXPECT_DOUBLE_EQ(test.magnitude(), 10);
}
TEST(VectorTests, MagnitudeTest3)
{
  math::Vector test(0, 10, 0);
  EXPECT_DOUBLE_EQ(test.magnitude(), 10);
}
TEST(VectorTests, MagnitudeTest4)
{
  math::Vector test(0, 0, 10);
  EXPECT_DOUBLE_EQ(test.magnitude(), 10);
}


// Normalization Test
TEST(VectorTests, UnitizeTest1)
{
  math::Vector test(2, 0, 0);
  test.unitize();
  EXPECT_DOUBLE_EQ(test.x, 1);
  EXPECT_DOUBLE_EQ(test.y, 0);
  EXPECT_DOUBLE_EQ(test.z, 0);
}
TEST(VectorTests, UnitizeTest2)
{
  math::Vector test(0, 2, 0);
  test.unitize();
  EXPECT_DOUBLE_EQ(test.x, 0);
  EXPECT_DOUBLE_EQ(test.y, 1);
  EXPECT_DOUBLE_EQ(test.z, 0);
}
TEST(VectorTests, UnitizeTest3)
{
  math::Vector test(0, 0, 2);
  test.unitize();
  EXPECT_DOUBLE_EQ(test.x, 0);
  EXPECT_DOUBLE_EQ(test.y, 0);
  EXPECT_DOUBLE_EQ(test.z, 1);
}TEST(VectorTests, UnitVectorTest1)
{
  math::Vector test(2, 0, 0);
  math::Vector unit = test.unit();
  EXPECT_DOUBLE_EQ(unit.x, 1);
  EXPECT_DOUBLE_EQ(unit.y, 0);
  EXPECT_DOUBLE_EQ(unit.z, 0);
}
TEST(VectorTests, UnitVectorTest2)
{
  math::Vector test(0, 2, 0);
  math::Vector unit = test.unit();
  EXPECT_DOUBLE_EQ(unit.x, 0);
  EXPECT_DOUBLE_EQ(unit.y, 1);
  EXPECT_DOUBLE_EQ(unit.z, 0);
}
TEST(VectorTests, UnitVectorTest3)
{
  math::Vector test(0, 0, 2);
  math::Vector unit = test.unit();
  EXPECT_DOUBLE_EQ(unit.x, 0);
  EXPECT_DOUBLE_EQ(unit.y, 0);
  EXPECT_DOUBLE_EQ(unit.z, 1);
}


// Zeroize Test
TEST(VectorTests, ZeroizeTest)
{
  math::Vector test(1, 2, 3);
  test.zeroize();
  EXPECT_DOUBLE_EQ(test.x, 0);
  EXPECT_DOUBLE_EQ(test.y, 0);
  EXPECT_DOUBLE_EQ(test.z, 0);
}