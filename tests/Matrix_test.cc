#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <math/Matrix.hpp>

using namespace bw;
using namespace testing;

// Matrix construction tests
TEST(MatrixConstruction, DefaultConstructor)
{
    Matrix<2, 3, int> mat;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            EXPECT_EQ(mat[i][j], 0);
        }
    }
}

////////////////////////////////////////////////////////////

TEST(MatrixConstruction, InitializerConstructor)
{
    std::vector<std::vector<int>> data = {{1, 2}, {3, 4}};
    Matrix<2, 2, int> mat(data);
    
    EXPECT_EQ(mat[0][0], 1);
    EXPECT_EQ(mat[0][1], 2);
    EXPECT_EQ(mat[1][0], 3);
    EXPECT_EQ(mat[1][1], 4);
}

////////////////////////////////////////////////////////////

TEST(MatrixConstruction, CopyConstructor)
{
    Matrix<2, 2, int> original;
    original.fill(5);
    
    Matrix<2, 2, int> copy(original);
    
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            EXPECT_EQ(copy[i][j], 5);
        }
    }
}

////////////////////////////////////////////////////////////

TEST(MatrixConstruction, MoveConstructor)
{
    Matrix<2, 2, int> original;
    original.fill(7);
    
    Matrix<2, 2, int> moved(std::move(original));
    
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            EXPECT_EQ(moved[i][j], 7);
        }
    }
}

////////////////////////////////////////////////////////////

// Matrix functions tests
TEST(MatrixFunctions, FillAndConvert)
{
    Matrix<2, 2, float> mat;
    mat.fill(2.5f);
    
    auto arr = mat.toLinearArray();
    std::array<float, 4> expected = {2.5f, 2.5f, 2.5f, 2.5f};
    EXPECT_THAT(arr, ElementsAreArray(expected));
}

////////////////////////////////////////////////////////////

// Matrix operations tests
TEST(MatrixOperations, Addition)
{
    Matrix<2, 2, int> mat1;
    mat1.fill(1);
    Matrix<2, 2, int> mat2;
    mat2.fill(2);
    
    auto result = mat1 + mat2;
    
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            EXPECT_EQ(result[i][j], 3);
        }
    }
}

////////////////////////////////////////////////////////////

TEST(MatrixOperations, Subtraction)
{
    Matrix<2, 2, int> mat1;
    mat1.fill(5);
    Matrix<2, 2, int> mat2;
    mat2.fill(3);
    
    auto result = mat1 - mat2;
    
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            EXPECT_EQ(result[i][j], 2);
        }
    }
}

////////////////////////////////////////////////////////////

TEST(MatrixOperations, Multiplication)
{
    Matrix<2, 3, int> mat1;
    Matrix<3, 2, int> mat2;
    
    // fill testing matrices
    int val = 1;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            mat1[i][j] = val++;
        }
    }
    
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 2; ++j) {
            mat2[i][j] = 1;
        }
    }
    
    auto result = mat1 * mat2;
    
    EXPECT_EQ(result[0][0], 1+2+3);
    EXPECT_EQ(result[0][1], 1+2+3);
    EXPECT_EQ(result[1][0], 4+5+6);
    EXPECT_EQ(result[1][1], 4+5+6);
}

////////////////////////////////////////////////////////////

// Matrix edge cases tests
TEST(MatrixEdgeCases, EmptyMatrix)
{
    Matrix<0, 0, int> mat;
    auto arr = mat.toLinearArray();
    EXPECT_TRUE(arr.empty());
}

////////////////////////////////////////////////////////////

TEST(MatrixEdgeCases, LargeMatrix)
{
    Matrix<10000, 10000, double> mat;
    mat.fill(1.0);
    
    EXPECT_DOUBLE_EQ(mat[9999][9999], 1.0);
}

////////////////////////////////////////////////////////////

TEST(MatrixEdgeCases, SelfAssignment)
{
    Matrix<2, 2, int> mat;
    mat.fill(10);
    
    mat = mat;
    
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            EXPECT_EQ(mat[i][j], 10);
        }
    }
}
