#include <gtest/gtest.h>
#include <math/Vec4.hpp>

using namespace bw;
using namespace testing;

// Common test fixture for all Vector tests
template <typename T>
class VectorTest : public Test {
protected:
    void SetUp() override {}
};

// Test types to use
using VectorTypes = Types<int, float, double>;
TYPED_TEST_SUITE(VectorTest, VectorTypes);


TEST(Vec4Construction, DefaultConstructor) {
    Vec4f v;
    EXPECT_EQ(v.x, 0.0f);
    EXPECT_EQ(v.y, 0.0f);
    EXPECT_EQ(v.z, 0.0f);
    EXPECT_EQ(v.w, 0.0f);
}

////////////////////////////////////////////////////////////

TEST(Vec4Construction, ComponentConstructor) {
    Vec4i v(1, 2, 3, 4);
    EXPECT_EQ(v.x, 1);
    EXPECT_EQ(v.y, 2);
    EXPECT_EQ(v.z, 3);
    EXPECT_EQ(v.w, 4);
}

////////////////////////////////////////////////////////////

TEST(Vec4Construction, CopyConstructor) {
    Vec4d original(1.5, 2.5, 3.5, 4.5);
    Vec4d copy(original);
    EXPECT_DOUBLE_EQ(copy.x, 1.5);
    EXPECT_DOUBLE_EQ(copy.y, 2.5);
    EXPECT_DOUBLE_EQ(copy.z, 3.5);
    EXPECT_DOUBLE_EQ(copy.w, 4.5);
}

////////////////////////////////////////////////////////////

TEST(Vec4Construction, MoveConstructor) {
    Vec4i original(3, 4, 5, 6);
    Vec4i moved(std::move(original));
    EXPECT_EQ(moved.x, 3);
    EXPECT_EQ(moved.y, 4);
    EXPECT_EQ(moved.z, 5);
    EXPECT_EQ(moved.w, 6);
}

////////////////////////////////////////////////////////////

TEST(Vec4Operators, AssignmentOperator) {
    Vec4f v1(1.1f, 2.2f, 3.3f, 4.4f);
    Vec4f v2;
    v2 = v1;
    EXPECT_FLOAT_EQ(v2.x, 1.1f);
    EXPECT_FLOAT_EQ(v2.y, 2.2f);
    EXPECT_FLOAT_EQ(v2.z, 3.3f);
    EXPECT_FLOAT_EQ(v2.w, 4.4f);
}

////////////////////////////////////////////////////////////

TEST(Vec4Operators, MoveAssignmentOperator) {
    Vec4i v1(5, 6, 7, 8);
    Vec4i v2;
    v2 = std::move(v1);
    EXPECT_EQ(v2.x, 5);
    EXPECT_EQ(v2.y, 6);
    EXPECT_EQ(v2.z, 7);
    EXPECT_EQ(v2.w, 8);
}

////////////////////////////////////////////////////////////

TEST(Vec4Operators, EqualityOperator) {
    Vec4i v1(1, 2, 3, 4);
    Vec4i v2(1, 2, 3, 4);
    Vec4i v3(3, 4, 5, 6);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 == v3);
}

////////////////////////////////////////////////////////////

TEST(Vec4Methods, ZeroStaticMethod) {
    Vec4i v = Vec4i::zero();
    EXPECT_EQ(v.x, 0);
    EXPECT_EQ(v.y, 0);
    EXPECT_EQ(v.z, 0);
    EXPECT_EQ(v.w, 0);
}

////////////////////////////////////////////////////////////

TEST(Vec4Methods, OneStaticMethod) {
    Vec4f v = Vec4f::one();
    EXPECT_FLOAT_EQ(v.x, 1.0f);
    EXPECT_FLOAT_EQ(v.y, 1.0f);
    EXPECT_FLOAT_EQ(v.z, 1.0f);
    EXPECT_FLOAT_EQ(v.w, 1.0f);
}

////////////////////////////////////////////////////////////

TEST(Vec4Methods, LengthMethod) {
    Vec4f v(2.0f, 3.0f, 6.0f, 12.0f);
    float expected_length = std::sqrt(2.0f*2.0f + 3.0f*3.0f + 6.0f*6.0f + 12.0f*12.0f);
    EXPECT_FLOAT_EQ(v.length(), expected_length);
}

////////////////////////////////////////////////////////////

TEST(Vec4Methods, NormalizedMethod) {
    Vec4f v(2.0f, 3.0f, 6.0f, 12.0f);
    float len = v.length();
    Vec4f norm = v.normalized();
    
    EXPECT_FLOAT_EQ(norm.length(), 1.0f);
    
    float tolerance = 1e-6f;
    EXPECT_NEAR(norm.x, 2.0f/len, tolerance);
    EXPECT_NEAR(norm.y, 3.0f/len, tolerance);
    EXPECT_NEAR(norm.z, 6.0f/len, tolerance);
    EXPECT_NEAR(norm.w, 12.0f/len, tolerance);
}
