// matrix_tests.cpp


// Inclusions
#include "../pch.h"
#include "../../Source/Utilities/Math/matrix.h"
#include "../../Source/Utilities/Math/matrix.cpp"


// Testing Union
void TestElements(const math::Matrix& test)
{
  for (unsigned int i = 0; i < 9; i++)
  {
    EXPECT_DOUBLE_EQ(test.e[i], i);
  }
}
TEST(MatrixTests, DataArrayRowArrayTest)
{
  math::Matrix test;
  for (unsigned int i = 0; i < 3; i++)
  {
    for (unsigned int j = 0; j < 3; j++)
    {
      test.row[i].e[j] = 3.0 * i + j;
    }
  };

  TestElements(test);
}
TEST(MatrixTests, DataArrayElementTest)
{
  math::Matrix test;
  test.e11 = 0;
  test.e12 = 1;
  test.e13 = 2;
  test.e21 = 3;
  test.e22 = 4;
  test.e23 = 5;
  test.e31 = 6;
  test.e32 = 7;
  test.e33 = 8;
  TestElements(test);
}
TEST(MatrixTests, DataRowArrayElementTest)
{
  math::Matrix test;
  test.e11 = 0;
  test.e12 = 1;
  test.e13 = 2;
  test.e21 = 3;
  test.e22 = 4;
  test.e23 = 5;
  test.e31 = 6;
  test.e32 = 7;
  test.e33 = 8;
  for (unsigned int i = 0; i < 3; i++)
  {
    for (unsigned int j = 0; j < 3; j++)
    {
      EXPECT_DOUBLE_EQ(test.row[i].e[j], 3.0 * i + j);
    }
  };
}


// Testing Constructors
TEST(MatrixTests, ConstructorDefaultTest)
{
  math::Matrix test;
  for (unsigned int i = 0; i < 9; i++)
  {
    EXPECT_DOUBLE_EQ(test.e[i], 0);
  }
}
TEST(MatrixTests, ConstructorElementwiseTest)
{
  math::Matrix test(0, 1, 2, 3, 4, 5, 6, 7, 8);
  TestElements(test);
}
TEST(MatrixTests, ConstructorCopyTest)
{
  math::Matrix that(0, 1, 2, 3, 4, 5, 6, 7, 8);
  math::Matrix test(that);
  TestElements(test);
}


// Accessor Tests
TEST(MatrixTests, OperatorAccessorRowwiseTest)
{
  math::Matrix test(0, 1, 2, 3, 4, 5, 6, 7, 8);
  EXPECT_TRUE(math::Vector(0, 1, 2) == test[0]);
  EXPECT_TRUE(math::Vector(3, 4, 5) == test[1]);
  EXPECT_TRUE(math::Vector(6, 7, 8) == test[2]);

  test[0] = math::Vector(8, 7, 6);
  test[1] = math::Vector(5, 4, 3);
  test[2] = math::Vector(2, 1, 0);
  EXPECT_TRUE(math::Vector(8, 7, 6) == test[0]);
  EXPECT_TRUE(math::Vector(5, 4, 3) == test[1]);
  EXPECT_TRUE(math::Vector(2, 1, 0) == test[2]);
}
TEST(MatrixTests, OperatorAccessorElementwiseTest)
{
  math::Matrix test(0, 1, 2, 3, 4, 5, 6, 7, 8);
  for (unsigned int i = 0; i < 3; i++)
  {
    for (unsigned int j = 0; j < 3; j++)
    {
      EXPECT_DOUBLE_EQ(test[i][j], 3.0 * i + j);
    }
  };

  test[0][0] = 8;
  test[0][1] = 7;
  test[0][2] = 6;
  test[1][0] = 5;
  test[1][1] = 4;
  test[1][2] = 3;
  test[2][0] = 2;
  test[2][1] = 1;
  test[2][2] = 0;

  for (unsigned int i = 0; i < 9; i++)
  {
    EXPECT_DOUBLE_EQ(test.e[i], 8 - i);
  }
}


// Assignment Operator Tests
TEST(MatrixTests, OperatorAssignmentTest)
{
  math::Matrix that(0, 1, 2, 3, 4, 5, 6, 7, 8);
  math::Matrix test = that;
  TestElements(test);
}


// Setter Tests
TEST(MatrixTests, SetterElementwiseTest)
{
  math::Matrix test;
  test.set(0, 1, 2, 3, 4, 5, 6, 7, 8);
  TestElements(test);
}
TEST(MatrixTests, SetterMatrixwiseTest)
{
  math::Matrix that(0, 1, 2, 3, 4, 5, 6, 7, 8);
  math::Matrix test;
  test.set(that);
  TestElements(test);
}
TEST(MatrixTests, SetRowTest)
{
  math::Matrix test;
  test.setRows(math::Vector(0, 1, 2),
               math::Vector(3, 4, 5),
               math::Vector(6, 7, 8)
              );
  TestElements(test);
}
TEST(MatrixTests, SetColumnsTest)
{
  math::Matrix test;
  test.setColumns(math::Vector(0, 3, 6),
                  math::Vector(1, 4, 7),
                  math::Vector(2, 5, 8)
                 );
  TestElements(test);
}


// Comparison Operators
TEST(MatrixTests, OperatorIsEqualTest1)
{
  math::Matrix A(0, 1, 2, 3, 4, 5, 6, 7, 8);
  math::Matrix B = A;
  EXPECT_TRUE(A == B);
}
TEST(MatrixTests, OperatorIsEqualTest2)
{
  math::Matrix A(0, 1, 2, 3, 4, 5, 6, 7, 8);
  math::Matrix B(8, 7, 6, 5, 4, 3, 2, 1, 0);
  EXPECT_FALSE(A == B);
}
TEST(MatrixTests, OperatorIsNotEqualTest1)
{
  math::Matrix A(0, 1, 2, 3, 4, 5, 6, 7, 8);
  math::Matrix B(8, 7, 6, 5, 4, 3, 2, 1, 0);
  EXPECT_TRUE(A != B);
}
TEST(MatrixTests, OperatorIsNotEqualTest2)
{
  math::Matrix A(0, 1, 2, 3, 4, 5, 6, 7, 8);
  math::Matrix B = A;
  EXPECT_FALSE(A != B);
}


// Unary Negative Test
TEST(MatrixTests, OperatorUnaryTest)
{
  math::Matrix A(0, -1, -2, -3, -4, -5, -6, -7, -8);
  math::Matrix test = -A;
  TestElements(test);
}


// Addition Tests
TEST(MatrixTests, AdditionTest1)
{
  math::Matrix A(1, 1, 1, 1, 1, 1, 1, 1, 1);
  math::Matrix B(2, 2, 2, 2, 2, 2, 2, 2, 2);
  EXPECT_TRUE((A + B) == math::Matrix(3, 3, 3, 3, 3, 3, 3, 3, 3));
}
TEST(MatrixTests, AdditionTest2)
{
  math::Matrix A(1, 1, 1, 1, 1, 1, 1, 1, 1);
  math::Matrix test(2, 2, 2, 2, 2, 2, 2, 2, 2);
  test += A;
  EXPECT_TRUE(test == math::Matrix(3, 3, 3, 3, 3, 3, 3, 3, 3));
}


// Subtraction Tests
TEST(MatrixTests, SubtractionTest1)
{
  math::Matrix A(0, 2, 4, 6, 8, 10, 12, 14, 16);
  math::Matrix B(0, 1, 2, 3, 4, 5, 6, 7, 8);
  math::Matrix test = A - B;
  TestElements(test);
}
TEST(MatrixTests, SubtractionTest2)
{
  math::Matrix test(0, 2, 4, 6, 8, 10, 12, 14, 16);
  math::Matrix A(0, 1, 2, 3, 4, 5, 6, 7, 8);
  test -= A;
  TestElements(test);
}

// Scalar Multiplication Tests
TEST(MatrixTests, MultiplicationScalarTest1)
{
  math::Matrix A(0, 2, 4, 6, 8, 10, 12, 14, 16);
  math::Matrix test = A * 0.5;
  TestElements(test);
}
TEST(MatrixTests, MultiplicationScalarTest2)
{
  math::Matrix A(0, 2, 4, 6, 8, 10, 12, 14, 16);
  math::Matrix test = 0.5 * A;
  TestElements(test);
}
TEST(MatrixTests, MultiplicationScalarTest3)
{
  math::Matrix test(0, 2, 4, 6, 8, 10, 12, 14, 16);
  test *= 0.5;
  TestElements(test);
}


// Scalar Division Tests
TEST(MatrixTests, DivisionScalarTest1)
{
  math::Matrix A(0, 2, 4, 6, 8, 10, 12, 14, 16);
  math::Matrix test = A / 2;
  TestElements(test);
}
TEST(MatrixTests, DivisionScalarTest2)
{
  math::Matrix test(0, 2, 4, 6, 8, 10, 12, 14, 16);
  test /= 2;
  TestElements(test);
}
TEST(MatrixTests, DivisionScalarTest3)
{
  math::Matrix A(1, 2, 3, 4, 5, 6, 7, 8, 9);
  double s = 0;
  EXPECT_THROW(A / s, std::runtime_error);
}


// Matrix-Vector Multiplication Tests
// Matrix-Matrix Multiplication Tests


// Transpose Test
TEST(MatrixTests, TransposeTest)
{
  math::Matrix test(0, 1, 2, 3, 4, 5, 6, 7, 8);
  math::Matrix trans = test.transpose();
  EXPECT_TRUE(trans == math::Matrix(0, 3, 6, 1, 4, 7, 2, 5, 8));
}


// Trace Test
TEST(MatrixTests, TraceTest)
{
  math::Matrix test(0, 1, 2,
                    3, 4, 5,
                    6, 7, 8);
  EXPECT_DOUBLE_EQ(test.trace(), 12);
}


// Determinant Tests
TEST(MatrixTests, DeterminantTest)
{
  math::Matrix test(-2, 3, -1, 5, -1, 4, 4, -8, 2);
  EXPECT_DOUBLE_EQ(test.determinant(), -6);
}


// Inverse Tests
TEST(MatrixTests, InverseTest)
{
  math::Matrix test(0, -3, -2, 1, -4, -2, -3, 4, 1);
  EXPECT_TRUE(test.inverse() == math::Matrix(4, -5, -2, 5, -6, -2, -8, 9, 3));
}
TEST(MatrixTests, InvertTest)
{
  math::Matrix test(0, -3, -2, 1, -4, -2, -3, 4, 1);
  test.invert();
  EXPECT_TRUE(test == math::Matrix(4, -5, -2, 5, -6, -2, -8, 9, 3));
}


// Zeroize Test
TEST(MatrixTests, ZeroizeTest)
{
  math::Matrix zero(0, 0, 0, 0, 0, 0, 0, 0, 0);
  math::Matrix test(0, 1, 2, 3, 4, 5, 6, 7, 8);
  test.zeroize();
  EXPECT_TRUE(test == zero);
}


// Identity Test
TEST(MatrixTests, IdentityTest)
{
  math::Matrix I(1, 0, 0, 0, 1, 0, 0, 0, 1);
  math::Matrix test = math::Matrix::identity();
  EXPECT_TRUE(test == I);
}