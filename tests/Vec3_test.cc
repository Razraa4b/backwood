#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <math/Vec3.hpp>

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


TEST(Vec3Construction, DefaultConstructor) {
    Vec3f v;
    EXPECT_EQ(v.x, 0.0f);
    EXPECT_EQ(v.y, 0.0f);
    EXPECT_EQ(v.z, 0.0f);
}

TEST(Vec3Construction, ComponentConstructor) {
    Vec3i v(1, 2, 3);
    EXPECT_EQ(v.x, 1);
    EXPECT_EQ(v.y, 2);
    EXPECT_EQ(v.z, 3);
}

TEST(Vec3Construction, CopyConstructor) {
    Vec3d original(1.5, 2.5, 3.5);
    Vec3d copy(original);
    EXPECT_DOUBLE_EQ(copy.x, 1.5);
    EXPECT_DOUBLE_EQ(copy.y, 2.5);
    EXPECT_DOUBLE_EQ(copy.z, 3.5);
}

TEST(Vec3Construction, MoveConstructor) {
    Vec3i original(3, 4, 5);
    Vec3i moved(std::move(original));
    EXPECT_EQ(moved.x, 3);
    EXPECT_EQ(moved.y, 4);
    EXPECT_EQ(moved.z, 5);
}

TEST(Vec3Operators, AssignmentOperator) {
    Vec3f v1(1.1f, 2.2f, 3.3f);
    Vec3f v2;
    v2 = v1;
    EXPECT_FLOAT_EQ(v2.x, 1.1f);
    EXPECT_FLOAT_EQ(v2.y, 2.2f);
    EXPECT_FLOAT_EQ(v2.z, 3.3f);
}

TEST(Vec3Operators, MoveAssignmentOperator) {
    Vec3i v1(5, 6, 7);
    Vec3i v2;
    v2 = std::move(v1);
    EXPECT_EQ(v2.x, 5);
    EXPECT_EQ(v2.y, 6);
    EXPECT_EQ(v2.z, 7);
}

TEST(Vec3Operators, EqualityOperator) {
    Vec3i v1(1, 2, 3);
    Vec3i v2(1, 2, 3);
    Vec3i v3(3, 4, 5);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 == v3);
}

TEST(Vec3Methods, ZeroStaticMethod) {
    Vec3i v = Vec3i::zero();
    EXPECT_EQ(v.x, 0);
    EXPECT_EQ(v.y, 0);
    EXPECT_EQ(v.z, 0);
}

TEST(Vec3Methods, OneStaticMethod) {
    Vec3f v = Vec3f::one();
    EXPECT_FLOAT_EQ(v.x, 1.0f);
    EXPECT_FLOAT_EQ(v.y, 1.0f);
    EXPECT_FLOAT_EQ(v.z, 1.0f);
}

TEST(Vec3Methods, LengthMethod) {
    Vec3f v(2.0f, 3.0f, 6.0f);
    EXPECT_FLOAT_EQ(v.length(), 7.0f);
}

TEST(Vec3Methods, NormalizedMethod) {
    Vec3f v(2.0f, 3.0f, 6.0f);
    Vec3f norm = v.normalized();
    EXPECT_FLOAT_EQ(norm.length(), 1.0f);
    EXPECT_FLOAT_EQ(norm.x, 2.0f/7.0f);
    EXPECT_FLOAT_EQ(norm.y, 3.0f/7.0f);
    EXPECT_FLOAT_EQ(norm.z, 6.0f/7.0f);
}

TEST(Vec3Components, ComponentAliases) {
    Vec3f v(1.0f, 2.0f, 3.0f);
    EXPECT_FLOAT_EQ(v.r, 1.0f);
    EXPECT_FLOAT_EQ(v.g, 2.0f);
    EXPECT_FLOAT_EQ(v.b, 3.0f);
    EXPECT_FLOAT_EQ(v.s, 1.0f);
    EXPECT_FLOAT_EQ(v.t, 2.0f);
    EXPECT_FLOAT_EQ(v.p, 3.0f);
}
