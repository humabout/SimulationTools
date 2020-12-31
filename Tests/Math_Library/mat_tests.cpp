// mat_tests.cpp


// Inclusions
#include "../pch.h"
#include "../../Source/Math/mat.h"


// Test Fixtures
struct MatTests : public ::testing::Test
{
  nemesis::Mat<double, 3, 2> A;
  nemesis::Mat<double, 2, 3> B;
  nemesis::Mat<double, 3, 3> C_3x3;
  nemesis::Mat<double, 2, 2> C_2x2;

  virtual void SetUp(void)
  {
    A = nemesis::Mat<double, 3, 2>({ 1, 2,
                                     3, 4,
                                     5, 6 });
    B = nemesis::Mat<double, 2, 3>({ 0, 9, 8,
                                     7, 6, 5 });
    C_3x3 = nemesis::Mat<double, 3, 3>({ 14, 21, 18,
                                         28, 51, 44,
                                         42, 81, 70 });
    C_2x2 = nemesis::Mat<double, 2, 2>({ 67, 84,
                                         50, 68 });
  }

  virtual void TearDown(void) { }
};


//------------------------------------------------------------------------------
// Constructor Tests
//------------------------------------------------------------------------------
TEST_F(MatTests, ConstructorDefaultTest)
{
  nemesis::Mat<double, 2, 3> test;
  EXPECT_DOUBLE_EQ(test.e(0, 0), 0);
  EXPECT_DOUBLE_EQ(test.e(0, 1), 0);
  EXPECT_DOUBLE_EQ(test.e(0, 2), 0);
  EXPECT_DOUBLE_EQ(test.e(1, 0), 0);
  EXPECT_DOUBLE_EQ(test.e(1, 1), 0);
  EXPECT_DOUBLE_EQ(test.e(1, 2), 0);
}
TEST_F(MatTests, ConstructorArrayTest)
{
  nemesis::Mat<double, 2, 3> test({ 1, 2, 3, 4, 5, 6 });
  EXPECT_DOUBLE_EQ(test.e(0, 0), 1);
  EXPECT_DOUBLE_EQ(test.e(0, 1), 2);
  EXPECT_DOUBLE_EQ(test.e(0, 2), 3);
  EXPECT_DOUBLE_EQ(test.e(1, 0), 4);
  EXPECT_DOUBLE_EQ(test.e(1, 1), 5);
  EXPECT_DOUBLE_EQ(test.e(1, 2), 6);
}
TEST_F(MatTests, ConstructRowsTest)
{
  nemesis::Mat<double, 2, 3> test({ nemesis::Vec3<double>({ 1, 2, 3 }), 
                                    nemesis::Vec3<double>({ 4, 5, 6 }) });
  EXPECT_DOUBLE_EQ(test.e(0, 0), 1);
  EXPECT_DOUBLE_EQ(test.e(0, 1), 2);
  EXPECT_DOUBLE_EQ(test.e(0, 2), 3);
  EXPECT_DOUBLE_EQ(test.e(1, 0), 4);
  EXPECT_DOUBLE_EQ(test.e(1, 1), 5);
  EXPECT_DOUBLE_EQ(test.e(1, 2), 6);
}
TEST_F(MatTests, ConstructCopyTest)
{
  nemesis::Mat<double, 3, 2> test(A);
  EXPECT_DOUBLE_EQ(test.e(0, 0), 1);
  EXPECT_DOUBLE_EQ(test.e(0, 1), 2);
  EXPECT_DOUBLE_EQ(test.e(1, 0), 3);
  EXPECT_DOUBLE_EQ(test.e(1, 1), 4);
  EXPECT_DOUBLE_EQ(test.e(2, 0), 5);
  EXPECT_DOUBLE_EQ(test.e(2, 1), 6);
}


//------------------------------------------------------------------------------
// Setter Tests
//------------------------------------------------------------------------------
TEST_F(MatTests, SetterArrayTest)
{
  nemesis::Mat<double, 2, 3> test;
  test.set({ 1, 2, 3, 4, 5, 6 });
  EXPECT_DOUBLE_EQ(test.e(0, 0), 1);
  EXPECT_DOUBLE_EQ(test.e(0, 1), 2);
  EXPECT_DOUBLE_EQ(test.e(0, 2), 3);
  EXPECT_DOUBLE_EQ(test.e(1, 0), 4);
  EXPECT_DOUBLE_EQ(test.e(1, 1), 5);
  EXPECT_DOUBLE_EQ(test.e(1, 2), 6);
}
TEST_F(MatTests, SetterRowsTest)
{
  nemesis::Mat<double, 3, 2> test;
  test.set({ nemesis::Vec2<double>({ 1, 2 }),
             nemesis::Vec2<double>({ 3, 4 }),
             nemesis::Vec2<double>({ 5, 6 }) });
  EXPECT_DOUBLE_EQ(test.e(0, 0), 1);
  EXPECT_DOUBLE_EQ(test.e(0, 1), 2);
  EXPECT_DOUBLE_EQ(test.e(1, 0), 3);
  EXPECT_DOUBLE_EQ(test.e(1, 1), 4);
  EXPECT_DOUBLE_EQ(test.e(2, 0), 5);
  EXPECT_DOUBLE_EQ(test.e(2, 1), 6);
}
TEST_F(MatTests, SetterCopyTest)
{
  nemesis::Mat<double, 3, 2> test;
  test.set(A);
  EXPECT_DOUBLE_EQ(test.e(0, 0), 1);
  EXPECT_DOUBLE_EQ(test.e(0, 1), 2);
  EXPECT_DOUBLE_EQ(test.e(1, 0), 3);
  EXPECT_DOUBLE_EQ(test.e(1, 1), 4);
  EXPECT_DOUBLE_EQ(test.e(2, 0), 5);
  EXPECT_DOUBLE_EQ(test.e(2, 1), 6);
}


//------------------------------------------------------------------------------
// Size Tests
//------------------------------------------------------------------------------
TEST_F(MatTests, LengthTest)
{
  EXPECT_EQ(A.length(), 3);
}
TEST_F(MatTests, SizeTest)
{
  EXPECT_EQ(A.size(), 6);
}
TEST_F(MatTests, DimTest)
{
  EXPECT_EQ(A.dim().first , 3);
  EXPECT_EQ(A.dim().second, 2);
}


//------------------------------------------------------------------------------
// Access Oeprator Tests
//------------------------------------------------------------------------------
TEST_F(MatTests, AccessorGetTest)
{
  unsigned int zero = 0;
  unsigned int one = 1;
  unsigned int two = 2;
  EXPECT_DOUBLE_EQ(A[zero][zero], 1);
  EXPECT_DOUBLE_EQ(A[zero][one ], 2);
  EXPECT_DOUBLE_EQ(A[one ][zero], 3);
  EXPECT_DOUBLE_EQ(A[one ][one ], 4);
  EXPECT_DOUBLE_EQ(A[two ][zero], 5);
  EXPECT_DOUBLE_EQ(A[two ][one ], 6);
}
TEST_F(MatTests, AccessorGetConstTest)
{
  const unsigned int zero = 0;
  const unsigned int one = 1;
  const unsigned int two = 2;
  EXPECT_DOUBLE_EQ(A[zero][zero], 1);
  EXPECT_DOUBLE_EQ(A[zero][one ], 2);
  EXPECT_DOUBLE_EQ(A[one ][zero], 3);
  EXPECT_DOUBLE_EQ(A[one ][one ], 4);
  EXPECT_DOUBLE_EQ(A[two ][zero], 5);
  EXPECT_DOUBLE_EQ(A[two ][one ], 6);
}
TEST_F(MatTests, AccessorSetTest)
{
  unsigned int zero = 0;
  unsigned int one = 1;
  unsigned int two = 2;
  A[zero][zero] = 9;
  A[zero][one ] = 8;
  A[one ][zero] = 7;
  A[one ][one ] = 6;
  A[two ][zero] = 5;
  A[two ][one ] = 4;
  EXPECT_DOUBLE_EQ(A.e(0, 0), 9);
  EXPECT_DOUBLE_EQ(A.e(0, 1), 8);
  EXPECT_DOUBLE_EQ(A.e(1, 0), 7);
  EXPECT_DOUBLE_EQ(A.e(1, 1), 6);
  EXPECT_DOUBLE_EQ(A.e(2, 0), 5);
  EXPECT_DOUBLE_EQ(A.e(2, 1), 4);
}
TEST_F(MatTests, AccessorSetConstTest)
{
  const unsigned int zero = 0;
  const unsigned int one = 1;
  const unsigned int two = 2;
  A[zero][zero] = 9;
  A[zero][one ] = 8;
  A[one ][zero] = 7;
  A[one ][one ] = 6;
  A[two ][zero] = 5;
  A[two ][one ] = 4;
  EXPECT_DOUBLE_EQ(A.e(0, 0), 9);
  EXPECT_DOUBLE_EQ(A.e(0, 1), 8);
  EXPECT_DOUBLE_EQ(A.e(1, 0), 7);
  EXPECT_DOUBLE_EQ(A.e(1, 1), 6);
  EXPECT_DOUBLE_EQ(A.e(2, 0), 5);
  EXPECT_DOUBLE_EQ(A.e(2, 1), 4);
}
TEST_F(MatTests, AccessorGetRowTest)
{
  EXPECT_EQ(A.row(0), nemesis::Vec2<double>({ 1, 2 }));
  EXPECT_EQ(A.row(1), nemesis::Vec2<double>({ 3, 4 }));
  EXPECT_EQ(A.row(2), nemesis::Vec2<double>({ 5, 6 }));
}
TEST_F(MatTests, AccessorGetColumnTest)
{
  EXPECT_EQ(A.column(0), nemesis::Vec3<double>({ 1, 3, 5 }));
  EXPECT_EQ(A.column(1), nemesis::Vec3<double>({ 2, 4, 6 }));
}


//------------------------------------------------------------------------------
// Assignment Operator Tests
//------------------------------------------------------------------------------
TEST_F(MatTests, AssignmentArrayTest)
{
  A = { 9, 8, 7, 6, 5, 4 };
  EXPECT_DOUBLE_EQ(A.e(0, 0), 9);
  EXPECT_DOUBLE_EQ(A.e(0, 1), 8);
  EXPECT_DOUBLE_EQ(A.e(1, 0), 7);
  EXPECT_DOUBLE_EQ(A.e(1, 1), 6);
  EXPECT_DOUBLE_EQ(A.e(2, 0), 5);
  EXPECT_DOUBLE_EQ(A.e(2, 1), 4);
}
TEST_F(MatTests, AssignmentRowsTest)
{
  A = { nemesis::Vec2<double>({9, 8}),
        nemesis::Vec2<double>({7, 6 }),
        nemesis::Vec2<double>({5, 4}) };
  EXPECT_DOUBLE_EQ(A.e(0, 0), 9);
  EXPECT_DOUBLE_EQ(A.e(0, 1), 8);
  EXPECT_DOUBLE_EQ(A.e(1, 0), 7);
  EXPECT_DOUBLE_EQ(A.e(1, 1), 6);
  EXPECT_DOUBLE_EQ(A.e(2, 0), 5);
  EXPECT_DOUBLE_EQ(A.e(2, 1), 4);
}
TEST_F(MatTests, AssignmentMatrixTest)
{
  nemesis::Mat<double, 3, 2> that({ 9, 8, 7, 6, 5, 4 });
  A = that;
  EXPECT_DOUBLE_EQ(A.e(0, 0), 9);
  EXPECT_DOUBLE_EQ(A.e(0, 1), 8);
  EXPECT_DOUBLE_EQ(A.e(1, 0), 7);
  EXPECT_DOUBLE_EQ(A.e(1, 1), 6);
  EXPECT_DOUBLE_EQ(A.e(2, 0), 5);
  EXPECT_DOUBLE_EQ(A.e(2, 1), 4);
}


//------------------------------------------------------------------------------
// Comparison Operator Tests
//------------------------------------------------------------------------------
TEST_F(MatTests, ComparisonEqualTrueTest)
{
  nemesis::Mat<double, 3, 2> that(A);
  EXPECT_TRUE(A == that);
}
TEST_F(MatTests, ComparisonEqualFalseSizeTest)
{
  EXPECT_FALSE(A == B);
}
TEST_F(MatTests, ComparisonEqualFalseValueTest)
{
  nemesis::Mat<double, 2, 3> that;
  EXPECT_FALSE(A == that);
}
TEST_F(MatTests, ComparisonInequalTrueSizeTest)
{
  EXPECT_TRUE(A != B);
}
TEST_F(MatTests, ComparisonInequalTrueValueTest)
{
  nemesis::Mat<double, 2, 3> that;
  EXPECT_TRUE(A != that);
}
TEST_F(MatTests, ComparisonInequalFalseTest)
{
  nemesis::Mat<double, 3, 2> that(A);
  EXPECT_FALSE(A != that);
}


//------------------------------------------------------------------------------
// Unary Negative Tests
//------------------------------------------------------------------------------
TEST_F(MatTests, UnaryNegativeTest)
{
  A = -A;
  EXPECT_DOUBLE_EQ(A.e(0, 0), -1);
  EXPECT_DOUBLE_EQ(A.e(0, 1), -2);
  EXPECT_DOUBLE_EQ(A.e(1, 0), -3);
  EXPECT_DOUBLE_EQ(A.e(1, 1), -4);
  EXPECT_DOUBLE_EQ(A.e(2, 0), -5);
  EXPECT_DOUBLE_EQ(A.e(2, 1), -6);
}


//------------------------------------------------------------------------------
// Addition Operator Tests
//------------------------------------------------------------------------------
TEST_F(MatTests, AdditionTest)
{
  A = A + A;
  EXPECT_DOUBLE_EQ(A.e(0, 0), 2);
  EXPECT_DOUBLE_EQ(A.e(0, 1), 4);
  EXPECT_DOUBLE_EQ(A.e(1, 0), 6);
  EXPECT_DOUBLE_EQ(A.e(1, 1), 8);
  EXPECT_DOUBLE_EQ(A.e(2, 0), 10);
  EXPECT_DOUBLE_EQ(A.e(2, 1), 12);
}
TEST_F(MatTests, AdditionSelfTest)
{
  A += A;
  EXPECT_DOUBLE_EQ(A.e(0, 0), 2);
  EXPECT_DOUBLE_EQ(A.e(0, 1), 4);
  EXPECT_DOUBLE_EQ(A.e(1, 0), 6);
  EXPECT_DOUBLE_EQ(A.e(1, 1), 8);
  EXPECT_DOUBLE_EQ(A.e(2, 0), 10);
  EXPECT_DOUBLE_EQ(A.e(2, 1), 12);
}


//------------------------------------------------------------------------------
// Subtraction Operator Tests
//------------------------------------------------------------------------------
TEST_F(MatTests, SubtractionTest)
{
  A = A - A;
  EXPECT_DOUBLE_EQ(A.e(0, 0), 0);
  EXPECT_DOUBLE_EQ(A.e(0, 1), 0);
  EXPECT_DOUBLE_EQ(A.e(0, 2), 0);
  EXPECT_DOUBLE_EQ(A.e(1, 0), 0);
  EXPECT_DOUBLE_EQ(A.e(1, 1), 0);
  EXPECT_DOUBLE_EQ(A.e(1, 2), 0);
}
TEST_F(MatTests, SubtractionSelfTest)
{
  A -= A;
  EXPECT_DOUBLE_EQ(A.e(0, 0), 0);
  EXPECT_DOUBLE_EQ(A.e(0, 1), 0);
  EXPECT_DOUBLE_EQ(A.e(0, 2), 0);
  EXPECT_DOUBLE_EQ(A.e(1, 0), 0);
  EXPECT_DOUBLE_EQ(A.e(1, 1), 0);
  EXPECT_DOUBLE_EQ(A.e(1, 2), 0);
}


//------------------------------------------------------------------------------
// Scalar Mutiplication Tests
//------------------------------------------------------------------------------
TEST_F(MatTests, ProductScalarTest1)
{
  A = A * 2.0;
  EXPECT_DOUBLE_EQ(A.e(0, 0), 2);
  EXPECT_DOUBLE_EQ(A.e(0, 1), 4);
  EXPECT_DOUBLE_EQ(A.e(1, 0), 6);
  EXPECT_DOUBLE_EQ(A.e(1, 1), 8);
  EXPECT_DOUBLE_EQ(A.e(2, 0), 10);
  EXPECT_DOUBLE_EQ(A.e(2, 1), 12);
}
TEST_F(MatTests, ProductScalarTest2)
{
  A = 2.0 * A;
  EXPECT_DOUBLE_EQ(A.e(0, 0), 2);
  EXPECT_DOUBLE_EQ(A.e(0, 1), 4);
  EXPECT_DOUBLE_EQ(A.e(1, 0), 6);
  EXPECT_DOUBLE_EQ(A.e(1, 1), 8);
  EXPECT_DOUBLE_EQ(A.e(2, 0), 10);
  EXPECT_DOUBLE_EQ(A.e(2, 1), 12);
}
TEST_F(MatTests, ProductSelfScalarTest)
{
  A *= 2.0;
  EXPECT_DOUBLE_EQ(A.e(0, 0), 2);
  EXPECT_DOUBLE_EQ(A.e(0, 1), 4);
  EXPECT_DOUBLE_EQ(A.e(1, 0), 6);
  EXPECT_DOUBLE_EQ(A.e(1, 1), 8);
  EXPECT_DOUBLE_EQ(A.e(2, 0), 10);
  EXPECT_DOUBLE_EQ(A.e(2, 1), 12);
}


//------------------------------------------------------------------------------
// Scalar Division Tests
//------------------------------------------------------------------------------
TEST_F(MatTests, QuotientScalarTest)
{
  A *= 2;
  A = A / 2;
  EXPECT_DOUBLE_EQ(A.e(0, 0), 1);
  EXPECT_DOUBLE_EQ(A.e(0, 1), 2);
  EXPECT_DOUBLE_EQ(A.e(1, 0), 3);
  EXPECT_DOUBLE_EQ(A.e(1, 1), 4);
  EXPECT_DOUBLE_EQ(A.e(2, 0), 5);
  EXPECT_DOUBLE_EQ(A.e(2, 1), 6);
}
TEST_F(MatTests, QuotientSelfScalarTest)
{
  A *= 2;
  A /= 2;
  EXPECT_DOUBLE_EQ(A.e(0, 0), 1);
  EXPECT_DOUBLE_EQ(A.e(0, 1), 2);
  EXPECT_DOUBLE_EQ(A.e(1, 0), 3);
  EXPECT_DOUBLE_EQ(A.e(1, 1), 4);
  EXPECT_DOUBLE_EQ(A.e(2, 0), 5);
  EXPECT_DOUBLE_EQ(A.e(2, 1), 6);
}
TEST_F(MatTests, QuotientScalarDivByZeroTest)
{
  EXPECT_THROW(A = A / 0, std::runtime_error);
}


//------------------------------------------------------------------------------
// Vector Product Tests
//------------------------------------------------------------------------------
TEST_F(MatTests, ProductVectorTest)
{
  nemesis::Vec<double, 2> x({ 1, 2 });
  nemesis::Mat<double, 3, 2> a({ 1, 2, 3, 4, 5, 6 });
  nemesis::Vec<double, 3> b;

  b = a * x;
  EXPECT_DOUBLE_EQ(b[0], 5);
  EXPECT_DOUBLE_EQ(b[1], 11);
  EXPECT_DOUBLE_EQ(b[2], 17);
}


//------------------------------------------------------------------------------
// Matrix Product Tests
//------------------------------------------------------------------------------
TEST_F(MatTests, ProductMatrixTest1)
{
  EXPECT_EQ(A * B, C_3x3);
}
TEST_F(MatTests, ProductMatrixTest2)
{
  EXPECT_EQ(B * A, C_2x2);
}


//------------------------------------------------------------------------------
// Transpose Tests
//------------------------------------------------------------------------------
TEST_F(MatTests, TransposeTest)
{
   nemesis::Mat<double, 2, 3> A_T = A.transpose();
}


//------------------------------------------------------------------------------
// Zeroize Tests
//------------------------------------------------------------------------------
TEST_F(MatTests, ZeorizeTest)
{
  A.zeroize();
  EXPECT_DOUBLE_EQ(A[0][0], 0);
  EXPECT_DOUBLE_EQ(A[0][1], 0);
  EXPECT_DOUBLE_EQ(A[1][0], 0);
  EXPECT_DOUBLE_EQ(A[1][0], 0);
  EXPECT_DOUBLE_EQ(A[2][0], 0);
  EXPECT_DOUBLE_EQ(A[2][1], 0);
}


//------------------------------------------------------------------------------
// Constructor Tests
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Constructor Tests
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Constructor Tests
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Constructor Tests
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Constructor Tests
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Constructor Tests
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Constructor Tests
//------------------------------------------------------------------------------