// quaternion_tests.cpp


// Inclusions
#include "../pch.h"
#include "../../Source/Utilities/Math/quaternion.h"
#include "../../Source/Utilities/Math/quaternion.cpp"


// Union Tests
TEST(QuaternionTests, DataArrayElementwiseTest)
{
  math::Quaternion test;
  test.e[0] = 1;
  test.e[1] = 2;
  test.e[2] = 3;
  test.e[3] = 4;
  EXPECT_DOUBLE_EQ(test.w, 1);
  EXPECT_DOUBLE_EQ(test.x, 2);
  EXPECT_DOUBLE_EQ(test.y, 3);
  EXPECT_DOUBLE_EQ(test.z, 4);

}
TEST(QuaternionTests, DataArrayScalarversorTest)
{
  math::Quaternion test;
  test.e[0] = 1;
  test.e[1] = 2;
  test.e[2] = 3;
  test.e[3] = 4;
  EXPECT_DOUBLE_EQ(test.s, 1);
  EXPECT_TRUE(test.v == math::Vector(2,3,4));
}
TEST(QuaternionTests, DataScalarversorElementwiseTest)
{
  math::Quaternion test;
  test.s = 1;
  test.v = math::Vector(2, 3, 4);
  EXPECT_DOUBLE_EQ(test.w, 1);
  EXPECT_DOUBLE_EQ(test.x, 2);
  EXPECT_DOUBLE_EQ(test.y, 3);
  EXPECT_DOUBLE_EQ(test.z, 4);
}


// Constructor Tests
TEST(QuaternionTests, ConstructorDefaultTest)
{
  math::Quaternion test;
  EXPECT_DOUBLE_EQ(test.w, 0);
  EXPECT_DOUBLE_EQ(test.x, 0);
  EXPECT_DOUBLE_EQ(test.y, 0);
  EXPECT_DOUBLE_EQ(test.z, 0);
}
TEST(QuaternionTests, ConstructorElementwiseTest)
{
  math::Quaternion test(1, 2, 3, 4);
  EXPECT_DOUBLE_EQ(test.w, 1);
  EXPECT_DOUBLE_EQ(test.x, 2);
  EXPECT_DOUBLE_EQ(test.y, 3);
  EXPECT_DOUBLE_EQ(test.z, 4);
}
TEST(QuaternionTests, ConstructorScalarversorTest)
{
  math::Quaternion test(1, math::Vector(2, 3, 4));
  EXPECT_DOUBLE_EQ(test.w, 1);
  EXPECT_DOUBLE_EQ(test.x, 2);
  EXPECT_DOUBLE_EQ(test.y, 3);
  EXPECT_DOUBLE_EQ(test.z, 4);
}
TEST(QuaternionTests, ConstructorEuleraxisTest)
{
  // TODO: Find a suitable example to trust and make this test
}
TEST(QuaternionTests, ConstructorDCMTest)
{
  // TODO: Find a suitable example to trust and make this test
}
TEST(QuaternionTests, ConstructorVectorTest)
{
  math::Vector v_(1, 2, 3);
  math::Quaternion test(v_);
  EXPECT_DOUBLE_EQ(test.s, 0);
  EXPECT_TRUE(test.v == v_);
}
TEST(QuaternionTests, ConstructorCopyTest)
{
  math::Quaternion that(1, 2, 3, 4);
  math::Quaternion test(that);
  EXPECT_DOUBLE_EQ(test.w, 1);
  EXPECT_DOUBLE_EQ(test.x, 2);
  EXPECT_DOUBLE_EQ(test.y, 3);
  EXPECT_DOUBLE_EQ(test.z, 4);
}


// Accessor Tests
TEST(QuaternionTests, OperatorAccessorTest1)
{
  math::Quaternion test(1, 2, 3, 4);
  EXPECT_DOUBLE_EQ(test[0], 1);
  EXPECT_DOUBLE_EQ(test[1], 2);
  EXPECT_DOUBLE_EQ(test[2], 3);
  EXPECT_DOUBLE_EQ(test[3], 4);
}
TEST(QuaternionTests, OperatorAccessorTest2)
{
  math::Quaternion test;
  test[0] = 1;
  test[1] = 2;
  test[2] = 3;
  test[3] = 4;
  EXPECT_DOUBLE_EQ(test.w, 1);
  EXPECT_DOUBLE_EQ(test.x, 2);
  EXPECT_DOUBLE_EQ(test.y, 3);
  EXPECT_DOUBLE_EQ(test.z, 4);
}


// Assignment Operator Tests
TEST(QuaternionTests, OperatorAssignmentTest)
{
  math::Quaternion that(1, 2, 3, 4);
  math::Quaternion test = that;
  EXPECT_DOUBLE_EQ(test.w, 1);
  EXPECT_DOUBLE_EQ(test.x, 2);
  EXPECT_DOUBLE_EQ(test.y, 3);
  EXPECT_DOUBLE_EQ(test.z, 4);
}


// Conversion Operator Tests
TEST(QuaternionTests, OperatorConvertVecToQuatTest)
{
  // TODO: Find a suitable example to trust and make this test
}
TEST(QuaternionTests, OperatorConvertDcmToQuatTest)
{
  // TODO: Find a suitable example to trust and make this test
}


// Setter Tests
TEST(QuaternionTests, SetterElementwiseTest)
{
  math::Quaternion test;
}
TEST(QuaternionTests, SetterscalarvectorTest)
{
  math::Quaternion test;
}
TEST(QuaternionTests, SetterVectorTest)
{
  math::Quaternion test;
}
TEST(QuaternionTests, SetterEulerAxesTest)
{
  // TODO: Find a suitable example to trust and make this test
}
TEST(QuaternionTests, SetterDcmTest)
{
  // TODO: Find a suitable example to trust and make this test
}


// Comparison Operator Tests
TEST(QuaternionTests, ComparisonIsEqualTest1)
{
  math::Quaternion p(1, 2, 3, 4);
  math::Quaternion q = p;
  EXPECT_TRUE(p == q);
}
TEST(QuaternionTests, ComparisonIsEqualTest2)
{
  math::Quaternion p(1, 2, 3, 4);
  math::Quaternion q = p;
  q.w = 9;
  EXPECT_FALSE(p == q);
}
TEST(QuaternionTests, ComparisonIsNotEqualTest1)
{
  math::Quaternion p(1, 2, 3, 4);
  math::Quaternion q = p;
  q.w = 9;
  EXPECT_TRUE(p != q);
}
TEST(QuaternionTests, ComparisonIsNotEqualTest2)
{
  math::Quaternion p(1, 2, 3, 4);
  math::Quaternion q = p;
  EXPECT_FALSE(p != q);
}


// Unary Negative Tests
TEST(QuaternionTests, UnaryNegativeTest)
{
  math::Quaternion q(1, 2, 3, 4);
  math::Quaternion test = -q;
  EXPECT_DOUBLE_EQ(test.w, -1);
  EXPECT_DOUBLE_EQ(test.x, -2);
  EXPECT_DOUBLE_EQ(test.y, -3);
  EXPECT_DOUBLE_EQ(test.z, -4);
}


// Addition Tests
TEST(QuaternionTests, AdditionTest1)
{
  math::Quaternion p(1, 2, 3, 4);
  math::Quaternion q(9, 8, 7, 6);
  math::Quaternion test = p + q;
  EXPECT_DOUBLE_EQ(test.w, 10);
  EXPECT_DOUBLE_EQ(test.x, 10);
  EXPECT_DOUBLE_EQ(test.y, 10);
  EXPECT_DOUBLE_EQ(test.z, 10);
}
TEST(QuaternionTests, AdditionTest2)
{
  math::Quaternion test(1, 2, 3, 4);
  math::Quaternion q(9, 8, 7, 6);
  test += q;
  EXPECT_DOUBLE_EQ(test.w, 10);
  EXPECT_DOUBLE_EQ(test.x, 10);
  EXPECT_DOUBLE_EQ(test.y, 10);
  EXPECT_DOUBLE_EQ(test.z, 10);
}


// Subtraction Tests
TEST(QuaternionTests, SubtractionTest1)
{
  math::Quaternion p(1, 2, 3, 4);
  math::Quaternion q(9, 8, 7, 6);
  math::Quaternion test = p - q;
  EXPECT_DOUBLE_EQ(test.w, -8);
  EXPECT_DOUBLE_EQ(test.x, -6);
  EXPECT_DOUBLE_EQ(test.y, -4);
  EXPECT_DOUBLE_EQ(test.z, -2);
}
TEST(QuaternionTests, SubtractionTest2)
{
  math::Quaternion test(1, 2, 3, 4);
  math::Quaternion q(9, 8, 7, 6);
  test -= q;
  EXPECT_DOUBLE_EQ(test.w, -8);
  EXPECT_DOUBLE_EQ(test.x, -6);
  EXPECT_DOUBLE_EQ(test.y, -4);
  EXPECT_DOUBLE_EQ(test.z, -2);
}


// Scalar Multiplication Tests
TEST(QuaternionTests, MultiplicationScalarTest1)
{
  math::Quaternion q(1, 2, 3, 4);
  math::Quaternion test = q * 2;
  EXPECT_DOUBLE_EQ(test.w, 2);
  EXPECT_DOUBLE_EQ(test.x, 4);
  EXPECT_DOUBLE_EQ(test.y, 6);
  EXPECT_DOUBLE_EQ(test.z, 8);
}
TEST(QuaternionTests, MultiplicationScalarTest2)
{
  math::Quaternion q(1, 2, 3, 4);
  math::Quaternion test = 2 * q;
  EXPECT_DOUBLE_EQ(test.w, 2);
  EXPECT_DOUBLE_EQ(test.x, 4);
  EXPECT_DOUBLE_EQ(test.y, 6);
  EXPECT_DOUBLE_EQ(test.z, 8);
}
TEST(QuaternionTests, MultiplicationScalarTest3)
{
  math::Quaternion test(1, 2, 3, 4);
  test *= 2;
  EXPECT_DOUBLE_EQ(test.w, 2);
  EXPECT_DOUBLE_EQ(test.x, 4);
  EXPECT_DOUBLE_EQ(test.y, 6);
  EXPECT_DOUBLE_EQ(test.z, 8);
}


// Scalar Division Tests
TEST(QuaternionTests, DivisionScalarTest2)
{
  math::Quaternion q(1, 2, 3, 4);
  math::Quaternion test = q / 2;
  EXPECT_DOUBLE_EQ(test.w, 0.5);
  EXPECT_DOUBLE_EQ(test.x, 1);
  EXPECT_DOUBLE_EQ(test.y, 1.5);
  EXPECT_DOUBLE_EQ(test.z, 2);
}
TEST(QuaternionTests, DivisionScalarTest3)
{
  math::Quaternion test(1, 2, 3, 4);
  test /= 2;
  EXPECT_DOUBLE_EQ(test.w, 0.5);
  EXPECT_DOUBLE_EQ(test.x, 1);
  EXPECT_DOUBLE_EQ(test.y, 1.5);
  EXPECT_DOUBLE_EQ(test.z, 2);
}


// Quaternion Pre-Product Tests
TEST(QuaternionTests, MultiplicationQuatTest1)
{
  // TODO: Find a suitable example to trust and make this test
}
TEST(QuaternionTests, MultiplicationQuatTest2)
{
  // TODO: Find a suitable example to trust and make this test
}


// Quaternion Post-Division Tests
TEST(QuaternionTests, DivisionQuatTest1)
{
  // TODO: Find a suitable example to trust and make this test
}
TEST(QuaternionTests, DivisionQuatTest2)
{
  // TODO: Find a suitable example to trust and make this test
}


// Vector Quotient Tests

TEST(QuaternionTests, DivisionVectorTest)
{
  // TODO: Find a suitable example to trust and make this test
}


// Magnitude Tests
TEST(QuaternionTests, MagnitudeTest)
{
  math::Quaternion test;
  EXPECT_DOUBLE_EQ(test.magnitude(), 0);

  test.set(1, 1, 1, 1);
  EXPECT_DOUBLE_EQ(test.magnitude(), 2);
}
TEST(QuaternionTests, TensorTest)
{
  math::Quaternion test;
  EXPECT_DOUBLE_EQ(test.tensor(), 0);

  test.set(1, 1, 1, 1);
  EXPECT_DOUBLE_EQ(test.tensor(), 2);
}


// Quaternion Norm Tests
TEST(QuaternionTests, QuatNormTest)
{
  math::Quaternion test;
  EXPECT_DOUBLE_EQ(test.norm(), 0);

  test.set(1, 1, 1, 1);
  EXPECT_DOUBLE_EQ(test.norm(), 4);
}


// Unitize Tests
TEST(QuaternionTests, UnitQuaternionTest)
{
  math::Quaternion A(5, 5, 5, 5);
  math::Quaternion test = A.unit();
  EXPECT_DOUBLE_EQ(test.w, 0.5);
  EXPECT_DOUBLE_EQ(test.x, 0.5);
  EXPECT_DOUBLE_EQ(test.y, 0.5);
  EXPECT_DOUBLE_EQ(test.z, 0.5);
}
TEST(QuaternionTests, VersorTest)
{
  math::Quaternion A(5, 5, 5, 5);
  math::Quaternion test = A.versor();
  EXPECT_DOUBLE_EQ(test.w, 0.5);
  EXPECT_DOUBLE_EQ(test.x, 0.5);
  EXPECT_DOUBLE_EQ(test.y, 0.5);
  EXPECT_DOUBLE_EQ(test.z, 0.5);
}
TEST(QuaternionTests, UnitizeTest)
{
  math::Quaternion test(5, 5, 5, 5);
  test.unitize();
  EXPECT_DOUBLE_EQ(test.w, 0.5);
  EXPECT_DOUBLE_EQ(test.x, 0.5);
  EXPECT_DOUBLE_EQ(test.y, 0.5);
  EXPECT_DOUBLE_EQ(test.z, 0.5);
}


// Conjugate Tests
TEST(QuaternionTests, ConjugateTest)
{
  math::Quaternion q(1, 2, 3, 4);
  math::Quaternion test = q.conjugate();
  EXPECT_DOUBLE_EQ(test.s,  1);
  EXPECT_DOUBLE_EQ(test.x, -2);
  EXPECT_DOUBLE_EQ(test.y, -3);
  EXPECT_DOUBLE_EQ(test.z, -4);
  EXPECT_TRUE(q == test.conjugate());
}


// Inverse Tests
TEST(QuaternionTests, InverseTest1)
{
  // TODO: Find a suitable example to trust and make this test
}
TEST(QuaternionTests, InverseTest2)
{
  // TODO: Find a suitable example to trust and make this test
}
TEST(QuaternionTests, InvertTest1)
{
  // TODO: Find a suitable example to trust and make this test
}
TEST(QuaternionTests, InvertTest2)
{
  // TODO: Find a suitable example to trust and make this test
}


// Zeroize Tests
TEST(QuaternionTests, ZeroizeTest)
{
  math::Quaternion test(1, 2, 3, 4);
  test.zeroize();
  EXPECT_DOUBLE_EQ(test.w, 0);
  EXPECT_DOUBLE_EQ(test.x, 0);
  EXPECT_DOUBLE_EQ(test.y, 0);
  EXPECT_DOUBLE_EQ(test.z, 0);
}


// Rotation Tests
TEST(QuaternionTests, RotateByTest1)
{
  // TODO: This will need a reliable example to test against.
}
TEST(QuaternionTests, RotateByTest2)
{
  // TODO: This will need a reliable example to test against.
}