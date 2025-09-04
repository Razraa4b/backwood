#include <gtest/gtest.h>
#include <math/Matrix.hpp>

using namespace bw;

TEST(TranslateFunction, IdentityTranslation)
{
    Matrix4x4<float> actual;

    for (int i = 0; i < 4; ++i)
        actual[i][i] = 1.0f;

    // Translate by zero Vector
    auto copy = actual;
    actual.translate({ 0.0f, 0.0f, 0.0f });

    // Should be equal to actual matrix
    EXPECT_TRUE(copy == actual);
}

////////////////////////////////////////////////////////////

TEST(TranslateFunction, SimpleTranslation)
{
    Matrix4x4<float> actual;

    for (int i = 0; i < 4; ++i)
        actual[i][i] = 1.0f;

    Vec3f pos = { 3.5f, -2.0f, 1.0f };
    actual.translate(pos);

    // Manually build expected matrix
    Matrix4x4<float> expected;
    expected.fill(0.0f);
    for (int i = 0; i < 4; ++i)
        expected[i][i] = 1.0f;

    expected[0][3] = pos.x;
    expected[1][3] = pos.y;
    expected[2][3] = pos.z;

    EXPECT_TRUE(actual == expected);
}

////////////////////////////////////////////////////////////

TEST(TranslateFunction, TranslateNonIdentityMatrix)
{
    Matrix4x4<float> actual;
    // Example matrix (simple scale matrix)
    actual[0][0] = 2.0f;
    actual[1][1] = 3.0f;
    actual[2][2] = 4.0f;
    actual[3][3] = 1.0f;

    Vec3f pos = { 1.0f, 2.0f, 3.0f };
    auto copy = actual;
    copy.translate(pos);

    Matrix4x4<float> translation;

    for (int i = 0; i < 4; ++i)
        translation[i][i] = 1.0f;
    translation[0][3] = pos.x;
    translation[1][3] = pos.y;
    translation[2][3] = pos.z;

    Matrix4x4<float> expected = actual * translation;

    EXPECT_TRUE(copy == expected);
}
