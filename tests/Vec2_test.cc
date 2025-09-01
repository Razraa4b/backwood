#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <math/Vec2.hpp>

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


TEST(Vec2Construction, DefaultConstructor) {
    Vec2f v;
    EXPECT_EQ(v.x, 0.0f);
    EXPECT_EQ(v.y, 0.0f);
}

TEST(Vec2Construction, ComponentConstructor) {
    Vec2i v(1, 2);
    EXPECT_EQ(v.x, 1);
    EXPECT_EQ(v.y, 2);
}

TEST(Vec2Construction, CopyConstructor) {
    Vec2d original(1.5, 2.5);
    Vec2d copy(original);
    EXPECT_DOUBLE_EQ(copy.x, 1.5);
    EXPECT_DOUBLE_EQ(copy.y, 2.5);
}

TEST(Vec2Construction, MoveConstructor) {
    Vec2i original(3, 4);
    Vec2i moved(std::move(original));
    EXPECT_EQ(moved.x, 3);
    EXPECT_EQ(moved.y, 4);
}

TEST(Vec2Operators, AssignmentOperator) {
    Vec2f v1(1.1f, 2.2f);
    Vec2f v2;
    v2 = v1;
    EXPECT_FLOAT_EQ(v2.x, 1.1f);
    EXPECT_FLOAT_EQ(v2.y, 2.2f);
}

TEST(Vec2Operators, MoveAssignmentOperator) {
    Vec2i v1(5, 6);
    Vec2i v2;
    v2 = std::move(v1);
    EXPECT_EQ(v2.x, 5);
    EXPECT_EQ(v2.y, 6);
}

TEST(Vec2Operators, EqualityOperator) {
    Vec2i v1(1, 2);
    Vec2i v2(1, 2);
    Vec2i v3(3, 4);
    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 == v3);
}

TEST(Vec2Methods, ZeroStaticMethod) {
    Vec2i v = Vec2i::zero();
    EXPECT_EQ(v.x, 0);
    EXPECT_EQ(v.y, 0);
}

TEST(Vec2Methods, OneStaticMethod) {
    Vec2f v = Vec2f::one();
    EXPECT_FLOAT_EQ(v.x, 1.0f);
    EXPECT_FLOAT_EQ(v.y, 1.0f);
}

TEST(Vec2Methods, LengthMethod) {
    Vec2f v(3.0f, 4.0f);
    EXPECT_FLOAT_EQ(v.length(), 5.0f);
}

TEST(Vec2Methods, NormalizedMethod) {
    Vec2f v(3.0f, 4.0f);
    Vec2f norm = v.normalized();
    EXPECT_FLOAT_EQ(norm.length(), 1.0f);
    EXPECT_FLOAT_EQ(norm.x, 0.6f);
    EXPECT_FLOAT_EQ(norm.y, 0.8f);
}

TEST(Vec2Components, ComponentAliases) {
    Vec2f v(1.0f, 2.0f);
    EXPECT_FLOAT_EQ(v.r, 1.0f);
    EXPECT_FLOAT_EQ(v.g, 2.0f);
    EXPECT_FLOAT_EQ(v.s, 1.0f);
    EXPECT_FLOAT_EQ(v.t, 2.0f);
}

