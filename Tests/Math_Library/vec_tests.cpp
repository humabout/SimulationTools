// vec_test.cpp


// Inclusinos
#include "../pch.h"
#include "../../Source/Math/vec.h"



// Test Fixtures
struct VecTests : public ::testing::Test
{
  template<class T> using Vec4 = nemesis::Vec<double, 4>;
  Vec4<double> blank;
  Vec4<double> u;
  Vec4<double> v;

  virtual void SetUp()
  {
    u = Vec4<double>({ 1.1, 2.2, 3.3, 4.4 });
    v = Vec4<double>({ 8.8, 7.7, 6.6, 5.5 });
  }

  virtual void TearDown() { }
};


struct Vec3Tests : public ::testing::Test
{
  nemesis::Vec3<double> blank;
  nemesis::Vec3<double> u;
  nemesis::Vec3<double> v;

  virtual void SetUp()
  {
    u = nemesis::Vec3<double>({ 1.1, 2.2, 3.3 });
    v = nemesis::Vec3<double>({ 6.6, 5.5, 4.4 });
  }

  virtual void TearDown() { }
};


struct Vec2Tests : public ::testing::Test
{
  nemesis::Vec2<double> blank;
  nemesis::Vec2<double> u;
  nemesis::Vec2<double> v;

  virtual void SetUp()
  {
    u = nemesis::Vec2<double>({ 1.1, 2.2 });
    v = nemesis::Vec2<double>({ 4.4, 3.3 });
  }

  virtual void TearDown() { }
};


//------------------------------------------------------------------------------
// Constructor Tests
//------------------------------------------------------------------------------
TEST_F(VecTests, ConstructorDefaultTest)
{
  EXPECT_DOUBLE_EQ(blank.e(0), 0);
  EXPECT_DOUBLE_EQ(blank.e(1), 0);
  EXPECT_DOUBLE_EQ(blank.e(2), 0);
  EXPECT_DOUBLE_EQ(blank.e(3), 0);
}
TEST_F(VecTests, ConstructorArrayTest)
{
  Vec4<double> test({ 1.1, 2.2, 3.3, 4.4 });
  EXPECT_DOUBLE_EQ(test.e(0), 1.1);
  EXPECT_DOUBLE_EQ(test.e(1), 2.2);
  EXPECT_DOUBLE_EQ(test.e(2), 3.3);
  EXPECT_DOUBLE_EQ(test.e(3), 4.4);
}
TEST_F(VecTests, ConstructorCopyTest)
{
  Vec4<double> test(u);
  EXPECT_DOUBLE_EQ( test.e(0), u.e(0) );
  EXPECT_DOUBLE_EQ( test.e(1), u.e(1) );
  EXPECT_DOUBLE_EQ( test.e(2), u.e(2) );
  EXPECT_DOUBLE_EQ( test.e(3), u.e(3) );
}

TEST_F(Vec3Tests, ConstructorDefaultTest)
{
  EXPECT_DOUBLE_EQ(blank.e(0), 0);
  EXPECT_DOUBLE_EQ(blank.e(1), 0);
  EXPECT_DOUBLE_EQ(blank.e(2), 0);
}
TEST_F(Vec3Tests, ConstructorArrayTest)
{
  nemesis::Vec3<double> test({ 1.1, 2.2, 3.3 });
  EXPECT_DOUBLE_EQ(test.e(0), 1.1);
  EXPECT_DOUBLE_EQ(test.e(1), 2.2);
  EXPECT_DOUBLE_EQ(test.e(2), 3.3);
}
TEST_F(Vec3Tests, ConstructorCopyTest)
{
  nemesis::Vec3<double> test(u);
  EXPECT_DOUBLE_EQ(test.e(0), u.e(0));
  EXPECT_DOUBLE_EQ(test.e(1), u.e(1));
  EXPECT_DOUBLE_EQ(test.e(2), u.e(2));
}

TEST_F(Vec2Tests, ConstructorDefaultTest)
{
  EXPECT_DOUBLE_EQ(blank.e(0), 0);
  EXPECT_DOUBLE_EQ(blank.e(1), 0);
}
TEST_F(Vec2Tests, ConstructorArrayTest)
{
  nemesis::Vec2<double> test({ 1.1, 2.2 });
  EXPECT_DOUBLE_EQ(test.e(0), 1.1);
  EXPECT_DOUBLE_EQ(test.e(1), 2.2);
}
TEST_F(Vec2Tests, ConstructorCopyTest)
{
  nemesis::Vec2<double> test(u);
  EXPECT_DOUBLE_EQ(test.e(0), u.e(0));
  EXPECT_DOUBLE_EQ(test.e(1), u.e(1));
}


//------------------------------------------------------------------------------
// Setter Tests
//------------------------------------------------------------------------------
TEST_F(VecTests, SetterArrayTest)
{
  u.set({ 8.8, 7.7, 6.6, 5.5 });
  EXPECT_DOUBLE_EQ(u.e(0), v.e(0));
  EXPECT_DOUBLE_EQ(u.e(1), v.e(1));
  EXPECT_DOUBLE_EQ(u.e(2), v.e(2));
  EXPECT_DOUBLE_EQ(u.e(3), v.e(3));
}
TEST_F(VecTests, SetterCopyTest)
{
  u.set(v);
  EXPECT_DOUBLE_EQ(u.e(0), v.e(0));
  EXPECT_DOUBLE_EQ(u.e(1), v.e(1));
  EXPECT_DOUBLE_EQ(u.e(2), v.e(2));
  EXPECT_DOUBLE_EQ(u.e(3), v.e(3));
}

TEST_F(Vec3Tests, SetterArrayTest)
{
  u.set({ 6.6, 5.5, 4.4 });
  EXPECT_DOUBLE_EQ(u.e(0), v.e(0));
  EXPECT_DOUBLE_EQ(u.e(1), v.e(1));
  EXPECT_DOUBLE_EQ(u.e(2), v.e(2));
}
TEST_F(Vec3Tests, SetterCopyTest)
{
  u.set(v);
  EXPECT_DOUBLE_EQ(u.e(0), v.e(0));
  EXPECT_DOUBLE_EQ(u.e(1), v.e(1));
  EXPECT_DOUBLE_EQ(u.e(2), v.e(2));
}

TEST_F(Vec2Tests, SetterArrayTest)
{
  u.set({ 4.4, 3.3 });
  EXPECT_DOUBLE_EQ(u.e(0), v.e(0));
  EXPECT_DOUBLE_EQ(u.e(1), v.e(1));
}
TEST_F(Vec2Tests, SetterCopyTest)
{
  u.set(v);
  EXPECT_DOUBLE_EQ(u.e(0), v.e(0));
  EXPECT_DOUBLE_EQ(u.e(1), v.e(1));
}


//------------------------------------------------------------------------------
// Size Tests
//------------------------------------------------------------------------------
TEST_F(VecTests, LengthTest)
{
  EXPECT_EQ(u.length(), 4);
}
TEST_F(VecTests, SizeTest)
{
  EXPECT_EQ(u.size(), 4);
}
TEST_F(VecTests, DimTest)
{
  EXPECT_EQ(u.dim().first, 4);
  EXPECT_EQ(u.dim().second, 1);
}

TEST_F(Vec3Tests, LengthTest)
{
  EXPECT_EQ(u.length(), 3);
}
TEST_F(Vec3Tests, SizeTest)
{
  EXPECT_EQ(u.size(), 3);
}
TEST_F(Vec3Tests, DimTest)
{
  EXPECT_EQ(u.dim().first, 3);
  EXPECT_EQ(u.dim().second, 1);
}

TEST_F(Vec2Tests, LengthTest)
{
  EXPECT_EQ(u.length(), 2);
}
TEST_F(Vec2Tests, SizeTest)
{
  EXPECT_EQ(u.size(), 2);
}
TEST_F(Vec2Tests, DimTest)
{
  EXPECT_EQ(u.dim().first, 2);
  EXPECT_EQ(u.dim().second, 1);
}


//------------------------------------------------------------------------------
// Access Oeprator Tests
//------------------------------------------------------------------------------
TEST_F(VecTests, AccessorGetTest)
{
  unsigned int zero  = 0;
  unsigned int one   = 1;
  unsigned int two   = 2;
  unsigned int three = 3;
  EXPECT_DOUBLE_EQ(u[zero ], 1.1);
  EXPECT_DOUBLE_EQ(u[one  ], 2.2);
  EXPECT_DOUBLE_EQ(u[two  ], 3.3);
  EXPECT_DOUBLE_EQ(u[three], 4.4);
}
TEST_F(VecTests, AccessorConstGetTest)
{
  const unsigned int zero  = 0;
  const unsigned int one   = 1;
  const unsigned int two   = 2;
  const unsigned int three = 3;
  EXPECT_DOUBLE_EQ(u[zero ], 1.1);
  EXPECT_DOUBLE_EQ(u[one  ], 2.2);
  EXPECT_DOUBLE_EQ(u[two  ], 3.3);
  EXPECT_DOUBLE_EQ(u[three], 4.4);
}
TEST_F(VecTests, AccessorSetTest)
{
  unsigned int zero  = 0;
  unsigned int one   = 1;
  unsigned int two   = 2;
  unsigned int three = 3;
  u[zero ] = v[0];
  u[one  ] = v[1];
  u[two  ] = v[2];
  u[three] = v[3];
  EXPECT_DOUBLE_EQ(u.e(0), v.e(0));
  EXPECT_DOUBLE_EQ(u.e(1), v.e(1));
  EXPECT_DOUBLE_EQ(u.e(2), v.e(2));
  EXPECT_DOUBLE_EQ(u.e(3), v.e(3));
}
TEST_F(VecTests, AccessorConstSetTest)
{
  const unsigned int zero  = 0;
  const unsigned int one   = 1;
  const unsigned int two   = 2;
  const unsigned int three = 3;
  u[zero ] = v[0];
  u[one  ] = v[1];
  u[two  ] = v[2];
  u[three] = v[3];
  EXPECT_DOUBLE_EQ(u.e(0), v.e(0));
  EXPECT_DOUBLE_EQ(u.e(1), v.e(1));
  EXPECT_DOUBLE_EQ(u.e(2), v.e(2));
  EXPECT_DOUBLE_EQ(u.e(3), v.e(3));
}

TEST_F(Vec3Tests, AccessorGetTest)
{
  unsigned int zero = 0;
  unsigned int one  = 1;
  unsigned int two  = 2;
  EXPECT_DOUBLE_EQ(u[zero], 1.1);
  EXPECT_DOUBLE_EQ(u[one ], 2.2);
  EXPECT_DOUBLE_EQ(u[two ], 3.3);
}
TEST_F(Vec3Tests, AccessorConstGetTest)
{
  const unsigned int zero = 0;
  const unsigned int one  = 1;
  const unsigned int two  = 2;
  EXPECT_DOUBLE_EQ(u[zero], 1.1);
  EXPECT_DOUBLE_EQ(u[one ], 2.2);
  EXPECT_DOUBLE_EQ(u[two ], 3.3);
}
TEST_F(Vec3Tests, AccessorSetTest)
{
  unsigned int zero = 0;
  unsigned int one  = 1;
  unsigned int two  = 2;
  u[zero] = v[0];
  u[one ] = v[1];
  u[two ] = v[2];
  EXPECT_DOUBLE_EQ(u.e(0), v.e(0));
  EXPECT_DOUBLE_EQ(u.e(1), v.e(1));
  EXPECT_DOUBLE_EQ(u.e(2), v.e(2));
}
TEST_F(Vec3Tests, AccessorConstSetTest)
{
  const unsigned int zero = 0;
  const unsigned int one  = 1;
  const unsigned int two  = 2;
  u[zero ] = v[0];
  u[one  ] = v[1];
  u[two  ] = v[2];
  EXPECT_DOUBLE_EQ(u.e(0), v.e(0));
  EXPECT_DOUBLE_EQ(u.e(1), v.e(1));
  EXPECT_DOUBLE_EQ(u.e(2), v.e(2));
}
TEST_F(Vec3Tests, AssignmentXGetTest)
{
  EXPECT_DOUBLE_EQ(u.x(), u[0]);
}
TEST_F(Vec3Tests, AssignmentYGetTest)
{
  EXPECT_DOUBLE_EQ(u.y(), u[1]);
}
TEST_F(Vec3Tests, AssignmentZGetTest)
{
  EXPECT_DOUBLE_EQ(u.z(), u[2]);
}
TEST_F(Vec3Tests, AssignmentXSetTest)
{
  u.x() = 9.9;
  EXPECT_DOUBLE_EQ(u[0], 9.9);
}
TEST_F(Vec3Tests, AssignmentYSetTest)
{
  u.y() = 9.9;
  EXPECT_DOUBLE_EQ(u[1], 9.9);
}
TEST_F(Vec3Tests, AssignmentZSetTest)
{
  u.z() = 9.9;
  EXPECT_DOUBLE_EQ(u[2], 9.9);
}

TEST_F(Vec2Tests, AccessorGetTest)
{
  unsigned int zero = 0;
  unsigned int one  = 1;
  EXPECT_DOUBLE_EQ(u[zero], 1.1);
  EXPECT_DOUBLE_EQ(u[one ], 2.2);
}
TEST_F(Vec2Tests, AccessorConstGetTest)
{
  const unsigned int zero = 0;
  const unsigned int one  = 1;
  EXPECT_DOUBLE_EQ(u[zero], 1.1);
  EXPECT_DOUBLE_EQ(u[one ], 2.2);
}
TEST_F(Vec2Tests, AccessorSetTest)
{
  unsigned int zero = 0;
  unsigned int one  = 1;
  u[zero] = v[0];
  u[one ] = v[1];
  EXPECT_DOUBLE_EQ(u.e(0), v.e(0));
  EXPECT_DOUBLE_EQ(u.e(1), v.e(1));
}
TEST_F(Vec2Tests, AccessorConstSetTest)
{
  const unsigned int zero = 0;
  const unsigned int one  = 1;
  u[zero] = v[0];
  u[one ] = v[1];
  EXPECT_DOUBLE_EQ(u.e(0), v.e(0));
  EXPECT_DOUBLE_EQ(u.e(1), v.e(1));
}
TEST_F(Vec2Tests, AssignmentXGetTest)
{
  EXPECT_DOUBLE_EQ(u.x(), u[0]);
}
TEST_F(Vec2Tests, AssignmentYGetTest)
{
  EXPECT_DOUBLE_EQ(u.y(), u[1]);
}
TEST_F(Vec2Tests, AssignmentXSetTest)
{
  u.x() = 9.9;
  EXPECT_DOUBLE_EQ(u[0], 9.9);
}
TEST_F(Vec2Tests, AssignmentYSetTest)
{
  u.y() = 9.9;
  EXPECT_DOUBLE_EQ(u[1], 9.9);
}


//------------------------------------------------------------------------------
// Assignment Operator Tests
//------------------------------------------------------------------------------
TEST_F(VecTests, AssignmentArrayTest)
{
  blank = { 1.1, 2.2, 3.3, 4.4 };
  EXPECT_DOUBLE_EQ(blank.e(0), 1.1);
  EXPECT_DOUBLE_EQ(blank.e(1), 2.2);
  EXPECT_DOUBLE_EQ(blank.e(2), 3.3);
  EXPECT_DOUBLE_EQ(blank.e(3), 4.4);
}
TEST_F(VecTests, AssignmentCopyTest)
{
  blank = u;
  EXPECT_DOUBLE_EQ(blank.e(0), u.e(0));
  EXPECT_DOUBLE_EQ(blank.e(1), u.e(1));
  EXPECT_DOUBLE_EQ(blank.e(2), u.e(2));
  EXPECT_DOUBLE_EQ(blank.e(3), u.e(3));
}

TEST_F(Vec3Tests, AssignmentArrayTest)
{
  blank = { 1.1, 2.2, 3.3 };
  EXPECT_DOUBLE_EQ(blank.e(0), 1.1);
  EXPECT_DOUBLE_EQ(blank.e(1), 2.2);
  EXPECT_DOUBLE_EQ(blank.e(2), 3.3);
}
TEST_F(Vec3Tests, AssignmentCopyTest)
{
  blank = u;
  EXPECT_DOUBLE_EQ(blank.e(0), u.e(0));
  EXPECT_DOUBLE_EQ(blank.e(1), u.e(1));
  EXPECT_DOUBLE_EQ(blank.e(2), u.e(2));
}

TEST_F(Vec2Tests, AssignmentArrayTest)
{
  blank = { 1.1, 2.2 };
  EXPECT_DOUBLE_EQ(blank.e(0), 1.1);
  EXPECT_DOUBLE_EQ(blank.e(1), 2.2);
}
TEST_F(Vec2Tests, AssignmentCopyTest)
{
  blank = u;
  EXPECT_DOUBLE_EQ(blank.e(0), u.e(0));
  EXPECT_DOUBLE_EQ(blank.e(1), u.e(1));
}


//------------------------------------------------------------------------------
// Comparison Operator Tests
//------------------------------------------------------------------------------
TEST_F(VecTests, ComparisonEqualsTrueTest)
{
  blank = u;
  EXPECT_TRUE(blank == u);
}
TEST_F(VecTests, ComparisonEqualsFalseTest)
{
  EXPECT_FALSE(u == v);
}
TEST_F(VecTests, ComparisonInequalsTrueTest)
{
  EXPECT_TRUE(u != v);
}
TEST_F(VecTests, ComparisonInequalsFalseTest)
{
  blank = u;
  EXPECT_FALSE(blank != u);
}

TEST_F(Vec3Tests, ComparisonEqualsTrueTest)
{
  blank = u;
  EXPECT_TRUE(blank == u);
}
TEST_F(Vec3Tests, ComparisonEqualsFalseTest)
{
  EXPECT_FALSE(u == v);
}
TEST_F(Vec3Tests, ComparisonInequalsTrueTest)
{
  EXPECT_TRUE(u != v);
}
TEST_F(Vec3Tests, ComparisonInequalsFalseTest)
{
  blank = u;
  EXPECT_FALSE(blank != u);
}

TEST_F(Vec2Tests, ComparisonEqualsTrueTest)
{
  blank = u;
  EXPECT_TRUE(blank == u);
}
TEST_F(Vec2Tests, ComparisonEqualsFalseTest)
{
  EXPECT_FALSE(u == v);
}
TEST_F(Vec2Tests, ComparisonInequalsTrueTest)
{
  EXPECT_TRUE(u != v);
}
TEST_F(Vec2Tests, ComparisonInequalsFalseTest)
{
  blank = u;
  EXPECT_FALSE(blank != u);
}


//------------------------------------------------------------------------------
// Unary Negative Tests
//------------------------------------------------------------------------------
TEST_F(VecTests, UnaryNegativeTest)
{
  v = -u;
  EXPECT_DOUBLE_EQ(v.e(0), -u.e(0));
  EXPECT_DOUBLE_EQ(v.e(1), -u.e(1));
  EXPECT_DOUBLE_EQ(v.e(2), -u.e(2));
  EXPECT_DOUBLE_EQ(v.e(3), -u.e(3));
}

TEST_F(Vec3Tests, UnaryNegativeTest)
{
  v = -u;
  EXPECT_DOUBLE_EQ(v.e(0), -u.e(0));
  EXPECT_DOUBLE_EQ(v.e(1), -u.e(1));
  EXPECT_DOUBLE_EQ(v.e(2), -u.e(2));
}

TEST_F(Vec2Tests, UnaryNegativeTest)
{
  v = -u;
  EXPECT_DOUBLE_EQ(v.e(0), -u.e(0));
  EXPECT_DOUBLE_EQ(v.e(1), -u.e(1));
}


//------------------------------------------------------------------------------
// Addition Operator Tests
//------------------------------------------------------------------------------
TEST_F(VecTests, AdditionTest)
{
  u = u + v;
  EXPECT_DOUBLE_EQ(u[0], 9.9);
  EXPECT_DOUBLE_EQ(u[1], 9.9);
  EXPECT_DOUBLE_EQ(u[2], 9.9);
  EXPECT_DOUBLE_EQ(u[3], 9.9);
}
TEST_F(VecTests, AdditionSelfTest)
{
  u += v;
  EXPECT_DOUBLE_EQ(u[0], 9.9);
  EXPECT_DOUBLE_EQ(u[1], 9.9);
  EXPECT_DOUBLE_EQ(u[2], 9.9);
  EXPECT_DOUBLE_EQ(u[3], 9.9);
}

TEST_F(Vec3Tests, AdditionTest)
{
  u = u + v;
  EXPECT_DOUBLE_EQ(u[0], 7.7);
  EXPECT_DOUBLE_EQ(u[1], 7.7);
  EXPECT_DOUBLE_EQ(u[2], 7.7);
}
TEST_F(Vec3Tests, AdditionSelfTest)
{
  u += v;
  EXPECT_DOUBLE_EQ(u[0], 7.7);
  EXPECT_DOUBLE_EQ(u[1], 7.7);
  EXPECT_DOUBLE_EQ(u[2], 7.7);
}

TEST_F(Vec2Tests, AdditionTest)
{
  u = u + v;
  EXPECT_DOUBLE_EQ(u[0], 5.5);
  EXPECT_DOUBLE_EQ(u[1], 5.5);
}
TEST_F(Vec2Tests, AdditionSelfTest)
{
  u += v;
  EXPECT_DOUBLE_EQ(u[0], 5.5);
  EXPECT_DOUBLE_EQ(u[1], 5.5);
}


//------------------------------------------------------------------------------
// Subtraction Operator Tests
//------------------------------------------------------------------------------
TEST_F(VecTests, SubtractionTest)
{
  u = u - v;
  EXPECT_DOUBLE_EQ(u[0], -7.7);
  EXPECT_DOUBLE_EQ(u[1], -5.5);
  EXPECT_DOUBLE_EQ(u[2], -3.3);
  EXPECT_DOUBLE_EQ(u[3], -1.1);
}
TEST_F(VecTests, SubtractionSelfTest)
{
  u -= v;
  EXPECT_DOUBLE_EQ(u[0], -7.7);
  EXPECT_DOUBLE_EQ(u[1], -5.5);
  EXPECT_DOUBLE_EQ(u[2], -3.3);
  EXPECT_DOUBLE_EQ(u[3], -1.1);
}

TEST_F(Vec3Tests, SubtractionTest)
{
  u = u - v;
  EXPECT_DOUBLE_EQ(u[0], -5.5);
  EXPECT_DOUBLE_EQ(u[1], -3.3);
  EXPECT_DOUBLE_EQ(u[2], -1.1);
}
TEST_F(Vec3Tests, SubtractionSelfTest)
{
  u -= v;
  EXPECT_DOUBLE_EQ(u[0], -5.5);
  EXPECT_DOUBLE_EQ(u[1], -3.3);
  EXPECT_DOUBLE_EQ(u[2], -1.1);
}

TEST_F(Vec2Tests, SubtractionTest)
{
  u = u - v;
  EXPECT_DOUBLE_EQ(u[0], -3.3);
  EXPECT_DOUBLE_EQ(u[1], -1.1);
}
TEST_F(Vec2Tests, SubtractionSelfTest)
{
  u -= v;
  EXPECT_DOUBLE_EQ(u[0], -3.3);
  EXPECT_DOUBLE_EQ(u[1], -1.1);
}


//------------------------------------------------------------------------------
// Scalar Product Tests
//------------------------------------------------------------------------------
TEST_F(VecTests, ProductScalarTest1)
{
  double s = 2;
  u = u * s;
  EXPECT_DOUBLE_EQ(u[0], 2.2);
  EXPECT_DOUBLE_EQ(u[1], 4.4);
  EXPECT_DOUBLE_EQ(u[2], 6.6);
  EXPECT_DOUBLE_EQ(u[3], 8.8);
}
TEST_F(VecTests, ProductScalarTest2)
{
  double s = 2;
  u = s * u;
  EXPECT_DOUBLE_EQ(u[0], 2.2);
  EXPECT_DOUBLE_EQ(u[1], 4.4);
  EXPECT_DOUBLE_EQ(u[2], 6.6);
  EXPECT_DOUBLE_EQ(u[3], 8.8);
}
TEST_F(VecTests, ProductSelfScalarTest)
{
  double s = 2;
  u *= s;
  EXPECT_DOUBLE_EQ(u[0], 2.2);
  EXPECT_DOUBLE_EQ(u[1], 4.4);
  EXPECT_DOUBLE_EQ(u[2], 6.6);
  EXPECT_DOUBLE_EQ(u[3], 8.8);
}

TEST_F(Vec3Tests, ProductScalarTest1)
{
  double s = 2;
  u = u * s;
  EXPECT_DOUBLE_EQ(u[0], 2.2);
  EXPECT_DOUBLE_EQ(u[1], 4.4);
  EXPECT_DOUBLE_EQ(u[2], 6.6);
}
TEST_F(Vec3Tests, ProductScalarTest2)
{
  double s = 2;
  u = s * u;
  EXPECT_DOUBLE_EQ(u[0], 2.2);
  EXPECT_DOUBLE_EQ(u[1], 4.4);
  EXPECT_DOUBLE_EQ(u[2], 6.6);
}
TEST_F(Vec3Tests, ProductSelfScalarTest)
{
  double s = 2;
  u *= s;
  EXPECT_DOUBLE_EQ(u[0], 2.2);
  EXPECT_DOUBLE_EQ(u[1], 4.4);
  EXPECT_DOUBLE_EQ(u[2], 6.6);
}

TEST_F(Vec2Tests, ProductScalarTest1)
{
  double s = 2;
  u = u * s;
  EXPECT_DOUBLE_EQ(u[0], 2.2);
  EXPECT_DOUBLE_EQ(u[1], 4.4);
}
TEST_F(Vec2Tests, ProductScalarTest2)
{
  double s = 2;
  u = s * u;
  EXPECT_DOUBLE_EQ(u[0], 2.2);
  EXPECT_DOUBLE_EQ(u[1], 4.4);
}
TEST_F(Vec2Tests, ProductSelfScalarTest)
{
  double s = 2;
  u *= s;
  EXPECT_DOUBLE_EQ(u[0], 2.2);
  EXPECT_DOUBLE_EQ(u[1], 4.4);
}


//------------------------------------------------------------------------------
// Scalar Division Tests
//------------------------------------------------------------------------------
TEST_F(VecTests, QuotientScalarTest)
{
  double s = 2;
  u = u / s;
  EXPECT_DOUBLE_EQ(u[0], 0.55);
  EXPECT_DOUBLE_EQ(u[1], 1.1);
  EXPECT_DOUBLE_EQ(u[2], 1.65);
  EXPECT_DOUBLE_EQ(u[3], 2.2);
}
TEST_F(VecTests, QuotientSelfScalarTest)
{
  double s = 2;
  u /= s;
  EXPECT_DOUBLE_EQ(u[0], 0.55);
  EXPECT_DOUBLE_EQ(u[1], 1.1);
  EXPECT_DOUBLE_EQ(u[2], 1.65);
  EXPECT_DOUBLE_EQ(u[3], 2.2);
}
TEST_F(VecTests, QuotientDiByZeroTest)
{
  double s = 0;
  EXPECT_THROW(u = u / 0, std::runtime_error);
}

TEST_F(Vec3Tests, QuotientScalarTest)
{
  double s = 2;
  u = u / s;
  EXPECT_DOUBLE_EQ(u[0], 0.55);
  EXPECT_DOUBLE_EQ(u[1], 1.1);
  EXPECT_DOUBLE_EQ(u[2], 1.65);
}
TEST_F(Vec3Tests, QuotientSelfScalarTest)
{
  double s = 2;
  u /= s;
  EXPECT_DOUBLE_EQ(u[0], 0.55);
  EXPECT_DOUBLE_EQ(u[1], 1.1);
  EXPECT_DOUBLE_EQ(u[2], 1.65);
}
TEST_F(Vec3Tests, QuotientDiByZeroTest)
{
  double s = 0;
  EXPECT_THROW(u = u / 0, std::runtime_error);
}

TEST_F(Vec2Tests, QuotientScalarTest)
{
  double s = 2;
  u = u / s;
  EXPECT_DOUBLE_EQ(u[0], 0.55);
  EXPECT_DOUBLE_EQ(u[1], 1.1);
}
TEST_F(Vec2Tests, QuotientSelfScalarTest)
{
  double s = 2;
  u /= s;
  EXPECT_DOUBLE_EQ(u[0], 0.55);
  EXPECT_DOUBLE_EQ(u[1], 1.1);
}
TEST_F(Vec2Tests, QuotientDiByZeroTest)
{
  double s = 0;
  EXPECT_THROW(u = u / 0, std::runtime_error);
}


//------------------------------------------------------------------------------
// Dot Product Tests
//------------------------------------------------------------------------------
TEST_F(VecTests, ProductDotTest)
{
  EXPECT_DOUBLE_EQ(u * v, 72.6);
}

TEST_F(Vec3Tests, ProductDotTest)
{
  EXPECT_DOUBLE_EQ(u * v, 33.88);
}

TEST_F(Vec2Tests, ProductDotTest)
{
  EXPECT_DOUBLE_EQ(u * v, 12.1);
}


//------------------------------------------------------------------------------
// Cross Product Test
//------------------------------------------------------------------------------
TEST_F(Vec3Tests, ProductCrossTest)
{
  nemesis::Vec3<double> cross = u % v;
  EXPECT_DOUBLE_EQ(cross[0], -8.47);
  EXPECT_DOUBLE_EQ(cross[1], 16.94);
  EXPECT_DOUBLE_EQ(cross[2], -8.47);
}
TEST_F(Vec3Tests, ProductSelfCrossTest)
{
  u %= v;
  EXPECT_DOUBLE_EQ(u[0], -8.47);
  EXPECT_DOUBLE_EQ(u[1], 16.94);
  EXPECT_DOUBLE_EQ(u[2], -8.47);
}


//------------------------------------------------------------------------------
// Magnitude Tests
//------------------------------------------------------------------------------
TEST_F(VecTests, MagnitudeTest)
{
  double mag = sqrt(1.1 * 1.1 + 2.2 * 2.2 + 3.3 * 3.3 + 4.4 * 4.4);
  EXPECT_DOUBLE_EQ(u.magnitude(), mag);
}

TEST_F(Vec3Tests, MagnitudeTest)
{
  double mag = sqrt(1.1 * 1.1 + 2.2 * 2.2 + 3.3 * 3.3);
  EXPECT_DOUBLE_EQ(u.magnitude(), mag);
}

TEST_F(Vec2Tests, MagnitudeTest)
{
  double mag = sqrt(1.1 * 1.1 + 2.2 * 2.2);
  EXPECT_DOUBLE_EQ(u.magnitude(), mag);
}


//------------------------------------------------------------------------------
// Unit Vector Tests
//------------------------------------------------------------------------------
TEST_F(VecTests, UnitVectorTest)
{
  Vec4<double> unit = u.unit();
  EXPECT_NEAR(unit[0], 0.182574, 1e-6);
  EXPECT_NEAR(unit[1], 0.365148, 1e-6);
  EXPECT_NEAR(unit[2], 0.547723, 1e-6);
  EXPECT_NEAR(unit[3], 0.730297, 1e-6);
}
TEST_F(VecTests, UnitizeTest)
{
  u.unitize();
  EXPECT_NEAR(u[0], 0.182574, 1e-6);
  EXPECT_NEAR(u[1], 0.365148, 1e-6);
  EXPECT_NEAR(u[2], 0.547723, 1e-6);
  EXPECT_NEAR(u[3], 0.730297, 1e-6);
}

TEST_F(Vec3Tests, UnitVectorTest)
{
  nemesis::Vec3<double> unit = u.unit();
  EXPECT_NEAR(unit[0], 0.267261, 1e-6);
  EXPECT_NEAR(unit[1], 0.534522, 1e-6);
  EXPECT_NEAR(unit[2], 0.801784, 1e-6);
}
TEST_F(Vec3Tests, UnitizeTest)
{
  u.unitize();
  EXPECT_NEAR(u[0], 0.267261, 1e-6);
  EXPECT_NEAR(u[1], 0.534522, 1e-6);
  EXPECT_NEAR(u[2], 0.801784, 1e-6);
}

TEST_F(Vec2Tests, UnitVectorTest)
{
  nemesis::Vec2<double> unit = u.unit();
  EXPECT_NEAR(unit[0], 0.447214, 1e-6);
  EXPECT_NEAR(unit[1], 0.894427, 1e-6);
}
TEST_F(Vec2Tests, UnitizeTest)
{
  u.unitize();
  EXPECT_NEAR(u[0], 0.447214, 1e-6);
  EXPECT_NEAR(u[1], 0.894427, 1e-6);
}


//------------------------------------------------------------------------------
// Zeroize Tests
//------------------------------------------------------------------------------
TEST_F(VecTests, ZeroizeTest)
{
  u.zeroize();
  EXPECT_DOUBLE_EQ(u[0], 0);
  EXPECT_DOUBLE_EQ(u[1], 0);
  EXPECT_DOUBLE_EQ(u[2], 0);
  EXPECT_DOUBLE_EQ(u[3], 0);
}

TEST_F(Vec3Tests, ZeroizeTest)
{
  u.zeroize();
  EXPECT_DOUBLE_EQ(u[0], 0);
  EXPECT_DOUBLE_EQ(u[1], 0);
  EXPECT_DOUBLE_EQ(u[2], 0);
}

TEST_F(Vec2Tests, ZeroizeTest)
{
  u.zeroize();
  EXPECT_DOUBLE_EQ(u[0], 0);
  EXPECT_DOUBLE_EQ(u[1], 0);
}