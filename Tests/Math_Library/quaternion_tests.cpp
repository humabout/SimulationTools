// quaternion_tests.cpp


// Inclusions
#include "../pch.h"
#include "../../Source/Math/quaternion.h"
#include "../../Source/Math/quaternion.cpp"
#include "../../Source/Math/math_constants.h"


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
  math::Vector x(1, 0, 0);
  math::Quaternion qx(x, math::HALF_PI);
  EXPECT_DOUBLE_EQ(qx.w, sqrt(0.5));
  EXPECT_DOUBLE_EQ(qx.x, sqrt(0.5));
  EXPECT_DOUBLE_EQ(qx.y, 0);
  EXPECT_DOUBLE_EQ(qx.z, 0);

  math::Vector y(0, 1, 0);
  math::Quaternion qy(y, math::HALF_PI);
  EXPECT_DOUBLE_EQ(qy.w, sqrt(0.5));
  EXPECT_DOUBLE_EQ(qy.x, 0);
  EXPECT_DOUBLE_EQ(qy.y, sqrt(0.5));
  EXPECT_DOUBLE_EQ(qy.z, 0);

  math::Vector z(0, 0, 1);
  math::Quaternion qz(z, math::HALF_PI);
  EXPECT_DOUBLE_EQ(qz.w, sqrt(0.5));
  EXPECT_DOUBLE_EQ(qz.x, 0);
  EXPECT_DOUBLE_EQ(qz.y, 0);
  EXPECT_DOUBLE_EQ(qz.z, sqrt(0.5));
}
TEST(QuaternionTests, ConstructorDcmTest)
{
  math::Matrix dcm(  6.0/23,   2.0/115, 111.0/115,
                    22.0/23,   3.0/23,   -6.0/23,
                    -3.0/23, 114.0/115,   2.0/115 );
  math::Quaternion test(dcm);

  math::Quaternion truth(9, 8, 7, 6);
  truth.unitize();
  EXPECT_DOUBLE_EQ(test.w, truth.w);
  EXPECT_DOUBLE_EQ(test.x, truth.x);
  EXPECT_DOUBLE_EQ(test.y, truth.y);
  EXPECT_DOUBLE_EQ(test.z, truth.z);
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
TEST(QuaternionTests, OperatorConvertDcmToQuatTest)
{
  math::Matrix dcm(  6.0 / 23,   2.0 / 115, 111.0 / 115,
                    22.0 / 23,   3.0 / 23,   -6.0 / 23,
                    -3.0 / 23, 114.0 / 115,   2.0 / 115);
  math::Quaternion test;
  test << dcm;

  math::Quaternion truth(9, 8, 7, 6);
  truth.unitize();
  EXPECT_DOUBLE_EQ(test.w, truth.w);
  EXPECT_DOUBLE_EQ(test.x, truth.x);
  EXPECT_DOUBLE_EQ(test.y, truth.y);
  EXPECT_DOUBLE_EQ(test.z, truth.z);
}
TEST(QuaternionTests, OperatorConvertQuatToDcmTest1)
{
  math::Matrix truth( 6.0 / 23,   2.0 / 115, 111.0 / 115,
                     22.0 / 23,   3.0 / 23,   -6.0 / 23,
                     -3.0 / 23, 114.0 / 115,   2.0 / 115);
  math::Quaternion q(9, 8, 7, 6);
  math::Matrix test = q.getDCM();

  EXPECT_NEAR(test.e11, truth.e11, 1e-15);
  EXPECT_NEAR(test.e12, truth.e12, 1e-15);
  EXPECT_NEAR(test.e13, truth.e13, 1e-15);
  EXPECT_NEAR(test.e21, truth.e21, 1e-15);
  EXPECT_NEAR(test.e22, truth.e22, 1e-15);
  EXPECT_NEAR(test.e23, truth.e23, 1e-15);
  EXPECT_NEAR(test.e31, truth.e31, 1e-15);
  EXPECT_NEAR(test.e32, truth.e32, 1e-15);
  EXPECT_NEAR(test.e33, truth.e33, 1e-15);
}
TEST(QuaternionTests, OperatorConvertQuatToDcmTest2)
{
  math::Matrix truth( 6.0 / 23,   2.0 / 115, 111.0 / 115,
                     22.0 / 23,   3.0 / 23,   -6.0 / 23,
                     -3.0 / 23, 114.0 / 115,   2.0 / 115);
  math::Quaternion q(9, 8, 7, 6);
  math::Matrix test;
  test << q;

  EXPECT_NEAR(test.e11, truth.e11, 1e-15);
  EXPECT_NEAR(test.e12, truth.e12, 1e-15);
  EXPECT_NEAR(test.e13, truth.e13, 1e-15);
  EXPECT_NEAR(test.e21, truth.e21, 1e-15);
  EXPECT_NEAR(test.e22, truth.e22, 1e-15);
  EXPECT_NEAR(test.e23, truth.e23, 1e-15);
  EXPECT_NEAR(test.e31, truth.e31, 1e-15);
  EXPECT_NEAR(test.e32, truth.e32, 1e-15);
  EXPECT_NEAR(test.e33, truth.e33, 1e-15);
}


// Setter Tests
TEST(QuaternionTests, SetterElementwiseTest)
{
  math::Quaternion test;
  test.set(1, 2, 3, 4);
  EXPECT_DOUBLE_EQ(test.w, 1);
  EXPECT_DOUBLE_EQ(test.x, 2);
  EXPECT_DOUBLE_EQ(test.y, 3);
  EXPECT_DOUBLE_EQ(test.z, 4);
}
TEST(QuaternionTests, SetterscalarvectorTest)
{
  math::Quaternion test;
  test.set(1, math::Vector(2, 3, 4));
  EXPECT_DOUBLE_EQ(test.w, 1);
  EXPECT_DOUBLE_EQ(test.x, 2);
  EXPECT_DOUBLE_EQ(test.y, 3);
  EXPECT_DOUBLE_EQ(test.z, 4);
}
TEST(QuaternionTests, SetterVectorTest)
{
  math::Quaternion test(9,9,9,9);
  test.set(math::Vector(1, 2, 3));
  EXPECT_DOUBLE_EQ(test.w, 0);
  EXPECT_DOUBLE_EQ(test.x, 1);
  EXPECT_DOUBLE_EQ(test.y, 2);
  EXPECT_DOUBLE_EQ(test.z, 3);
}
TEST(QuaternionTests, SetterEulerAxesTest)
{
  math::Vector x(1, 0, 0);
  math::Quaternion qx;
  qx.set(x, math::HALF_PI);
  EXPECT_DOUBLE_EQ(qx.w, sqrt(0.5));
  EXPECT_DOUBLE_EQ(qx.x, sqrt(0.5));
  EXPECT_DOUBLE_EQ(qx.y, 0);
  EXPECT_DOUBLE_EQ(qx.z, 0);

  math::Vector y(0, 1, 0);
  math::Quaternion qy;
  qy.set(y, math::HALF_PI);
  EXPECT_DOUBLE_EQ(qy.w, sqrt(0.5));
  EXPECT_DOUBLE_EQ(qy.x, 0);
  EXPECT_DOUBLE_EQ(qy.y, sqrt(0.5));
  EXPECT_DOUBLE_EQ(qy.z, 0);

  math::Vector z(0, 0, 1);
  math::Quaternion qz;
  qz.set(z, math::HALF_PI);
  EXPECT_DOUBLE_EQ(qz.w, sqrt(0.5));
  EXPECT_DOUBLE_EQ(qz.x, 0);
  EXPECT_DOUBLE_EQ(qz.y, 0);
  EXPECT_DOUBLE_EQ(qz.z, sqrt(0.5));
}
TEST(QuaternionTests, SetterDcmTest)
{
  math::Matrix dcm( 6.0 / 23,   2.0 / 115, 111.0 / 115,
                   22.0 / 23,   3.0 / 23,   -6.0 / 23,
                   -3.0 / 23, 114.0 / 115,   2.0 / 115);
  math::Quaternion test;
  test.set(dcm);

  math::Quaternion truth(9, 8, 7, 6);
  truth.unitize();
  EXPECT_DOUBLE_EQ(test.w, truth.w);
  EXPECT_DOUBLE_EQ(test.x, truth.x);
  EXPECT_DOUBLE_EQ(test.y, truth.y);
  EXPECT_DOUBLE_EQ(test.z, truth.z);
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
  math::Quaternion p(1, 2, 3, 4);
  math::Quaternion q(9, 8, 7, 6);
  math::Quaternion test = p * q;
  EXPECT_TRUE(test == math::Quaternion(-52, 16, 54, 32));
}
TEST(QuaternionTests, MultiplicationQuatTest2)
{
  math::Quaternion test(1, 2, 3, 4);
  math::Quaternion q(9, 8, 7, 6);
  test *= q;
  EXPECT_TRUE(test == math::Quaternion(-52, 16, 54, 32));
}


// Quaternion Post-Division Tests
TEST(QuaternionTests, DivisionQuatTest1)
{
  math::Quaternion p(-52, 16, 54, 32);
  math::Quaternion q(9, 8, 7, 6);
  math::Quaternion test = p / q;
  EXPECT_DOUBLE_EQ(test.w, 1.0);
  EXPECT_DOUBLE_EQ(test.x, 2.0);
  EXPECT_DOUBLE_EQ(test.y, 3.0);
  EXPECT_DOUBLE_EQ(test.z, 4.0);
}
TEST(QuaternionTests, DivisionQuatTest2)
{
  math::Quaternion test(-52, 16, 54, 32);
  math::Quaternion q(9, 8, 7, 6);
  test /= q;
  EXPECT_DOUBLE_EQ(test.w, 1.0);
  EXPECT_DOUBLE_EQ(test.x, 2.0);
  EXPECT_DOUBLE_EQ(test.y, 3.0);
  EXPECT_DOUBLE_EQ(test.z, 4.0);
}


// Vector Quotient Tests
TEST(QuaternionTests, DivisionVectorTest)
{
  math::Quaternion p(0, 1, 2, 3);
  math::Quaternion q(0, 4, -6, 8);
  math::Quaternion truth = p / q;
  math::Vector u(1, 2, 3);
  math::Vector v(4, -6, 8);
  math::Quaternion test = u / v;
  EXPECT_DOUBLE_EQ(test.w, truth.w);
  EXPECT_DOUBLE_EQ(test.x, truth.x);
  EXPECT_DOUBLE_EQ(test.y, truth.y);
  EXPECT_DOUBLE_EQ(test.z, truth.z);
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
  EXPECT_DOUBLE_EQ(test.w,  1);
  EXPECT_DOUBLE_EQ(test.x, -2);
  EXPECT_DOUBLE_EQ(test.y, -3);
  EXPECT_DOUBLE_EQ(test.z, -4);
  EXPECT_TRUE(q == test.conjugate());
}


// Inverse Tests
TEST(QuaternionTests, InverseTest)
{
  math::Quaternion p(9, 8, 7, 6);  math::Quaternion test = p.conjugate() / p.norm();
  EXPECT_DOUBLE_EQ(test.w,  9.0 / 230);
  EXPECT_DOUBLE_EQ(test.x, -8.0 / 230);
  EXPECT_DOUBLE_EQ(test.y, -7.0 / 230);
  EXPECT_DOUBLE_EQ(test.z, -6.0 / 230);
  
  test = test.inverse();
  EXPECT_DOUBLE_EQ(test.w, 9.0);
  EXPECT_DOUBLE_EQ(test.x, 8.0);
  EXPECT_DOUBLE_EQ(test.y, 7.0);
  EXPECT_DOUBLE_EQ(test.z, 6.0);
}
TEST(QuaternionTests, InvertTest)
{
  math::Quaternion test(9, 8, 7, 6);
  test.invert();
  EXPECT_DOUBLE_EQ(test.w,  9.0 / 230);
  EXPECT_DOUBLE_EQ(test.x, -8.0 / 230);
  EXPECT_DOUBLE_EQ(test.y, -7.0 / 230);
  EXPECT_DOUBLE_EQ(test.z, -6.0 / 230);

  test.invert();
  EXPECT_DOUBLE_EQ(test.w, 9.0);
  EXPECT_DOUBLE_EQ(test.x, 8.0);
  EXPECT_DOUBLE_EQ(test.y, 7.0);
  EXPECT_DOUBLE_EQ(test.z, 6.0);
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
  math::Vector x(1, 0, 0);
  math::Quaternion R(x, math::HALF_PI);

  math::Quaternion p(0, 0, 1, 0);
  p = p.rotatedBy(R);
  EXPECT_DOUBLE_EQ(p.w, 0);
  EXPECT_DOUBLE_EQ(p.x, 0);
  EXPECT_DOUBLE_EQ(p.y, 0);
  EXPECT_DOUBLE_EQ(p.z, 1);
}
TEST(QuaternionTests, RotateByTest2)
{
  math::Vector x(1, 0, 0);
  math::Quaternion R(x, math::HALF_PI);

  math::Quaternion p(0, 0, 1, 0);
  p = p.rotatedBy(R);
  p = p.rotatedBy(R.inverse());

  EXPECT_DOUBLE_EQ(p.w, 0);
  EXPECT_DOUBLE_EQ(p.x, 0);
  EXPECT_DOUBLE_EQ(p.y, 1);
  EXPECT_DOUBLE_EQ(p.z, 0);
}


// Conversion Tests
TEST(QuaternionTests, ConversionQuatToDcmTest1)
{

}