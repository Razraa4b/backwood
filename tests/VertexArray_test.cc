#include <gtest/gtest.h>
#include "OpenGLTestEnvironment.hpp"
#include <graphics/VertexArray.hpp>
#include <graphics/VertexBuffer.hpp>
#include <graphics/ElementBuffer.hpp>

using namespace bw;
using namespace bw::low_level;

TEST_F(OpenGLTestEnvironment, VertexArray_DefaultConstructor)
{
    VertexArray vao;
    
    EXPECT_NE(vao.getNativeHandle(), VertexArray::NullVertexArray);
    EXPECT_EQ(vao.getCurrentVertexBuffer(), nullptr);
    EXPECT_EQ(vao.getRange().start, 0u);
    EXPECT_EQ(vao.getRange().count, 0u);
}

////////////////////////////////////////////////////////////

TEST_F(OpenGLTestEnvironment, VertexArray_ConstructorWithVertexBuffer)
{
    std::vector<Vertex> vertices = {
        Vertex(Vec3f(0.0f, 0.0f, 0.0f), Vec4f(1.0f, 0.0f, 0.0f, 1.0f)),
        Vertex(Vec3f(1.0f, 0.0f, 0.0f), Vec4f(0.0f, 1.0f, 0.0f, 1.0f)),
        Vertex(Vec3f(0.0f, 1.0f, 0.0f), Vec4f(0.0f, 0.0f, 1.0f, 1.0f))
    };
    
    VertexBuffer vbo(BufferUsage::Static, vertices);
    VertexArray vao(vbo);
    
    EXPECT_NE(vao.getNativeHandle(), VertexArray::NullVertexArray);
    EXPECT_NE(vao.getCurrentVertexBuffer(), nullptr);
    EXPECT_EQ(vao.getRange().start, 0u);
    EXPECT_EQ(vao.getRange().count, 3u);
}

////////////////////////////////////////////////////////////

TEST_F(OpenGLTestEnvironment, VertexArray_ConstructorWithVertexBufferAndRange)
{
    std::vector<Vertex> vertices = {
        Vertex(Vec3f(0.0f, 0.0f, 0.0f), Vec4f(1.0f, 0.0f, 0.0f, 1.0f)),
        Vertex(Vec3f(1.0f, 0.0f, 0.0f), Vec4f(0.0f, 1.0f, 0.0f, 1.0f)),
        Vertex(Vec3f(0.0f, 1.0f, 0.0f), Vec4f(0.0f, 0.0f, 1.0f, 1.0f)),
        Vertex(Vec3f(1.0f, 1.0f, 0.0f), Vec4f(1.0f, 1.0f, 1.0f, 1.0f))
    };
    
    VertexBuffer vbo(BufferUsage::Static, vertices);
    VertexArray::Range range(1, 2);
    VertexArray vao(vbo, range);
    
    EXPECT_NE(vao.getNativeHandle(), VertexArray::NullVertexArray);
    EXPECT_NE(vao.getCurrentVertexBuffer(), nullptr);
    EXPECT_EQ(vao.getRange().start, 1u);
    EXPECT_EQ(vao.getRange().count, 2u);
}

////////////////////////////////////////////////////////////

TEST_F(OpenGLTestEnvironment, VertexArray_CopyConstructor)
{
    std::vector<Vertex> vertices = {
        Vertex(Vec3f(0.0f, 0.0f, 0.0f), Vec4f(1.0f, 0.0f, 0.0f, 1.0f)),
        Vertex(Vec3f(1.0f, 0.0f, 0.0f), Vec4f(0.0f, 1.0f, 0.0f, 1.0f))
    };
    
    VertexBuffer vbo(BufferUsage::Static, vertices);
    VertexArray original(vbo);
    
    VertexArray copy(original);
    
    EXPECT_NE(original.getNativeHandle(), copy.getNativeHandle());
    EXPECT_NE(copy.getCurrentVertexBuffer(), nullptr);
    EXPECT_EQ(copy.getRange().start, 0u);
    EXPECT_EQ(copy.getRange().count, 2u);
}

////////////////////////////////////////////////////////////

TEST_F(OpenGLTestEnvironment, VertexArray_MoveConstructor)
{
    std::vector<Vertex> vertices = {
        Vertex(Vec3f(0.0f, 0.0f, 0.0f), Vec4f(1.0f, 0.0f, 0.0f, 1.0f))
    };
    
    VertexBuffer vbo(BufferUsage::Static, vertices);
    VertexArray original(vbo);
    unsigned int originalHandle = original.getNativeHandle();
    
    VertexArray moved(std::move(original));
    
    EXPECT_EQ(moved.getNativeHandle(), originalHandle);
    EXPECT_EQ(original.getNativeHandle(), VertexArray::NullVertexArray);
    EXPECT_NE(moved.getCurrentVertexBuffer(), nullptr);
    EXPECT_EQ(moved.getRange().count, 1u);
}

////////////////////////////////////////////////////////////

TEST_F(OpenGLTestEnvironment, VertexArray_BindToVertexBuffer)
{
    std::vector<Vertex> vertices = {
        Vertex(Vec3f(0.0f, 0.0f, 0.0f), Vec4f(1.0f, 0.0f, 0.0f, 1.0f)),
        Vertex(Vec3f(1.0f, 0.0f, 0.0f), Vec4f(0.0f, 1.0f, 0.0f, 1.0f))
    };
    
    VertexBuffer vbo(BufferUsage::Static, vertices);
    VertexArray vao;
    
    vao.bindTo(vbo);
    
    EXPECT_NE(vao.getCurrentVertexBuffer(), nullptr);
    EXPECT_EQ(vao.getRange().start, 0u);
    EXPECT_EQ(vao.getRange().count, 2u);
}

////////////////////////////////////////////////////////////

TEST_F(OpenGLTestEnvironment, VertexArray_BindToVertexBufferWithRange)
{
    std::vector<Vertex> vertices = {
        Vertex(Vec3f(0.0f, 0.0f, 0.0f), Vec4f(1.0f, 0.0f, 0.0f, 1.0f)),
        Vertex(Vec3f(1.0f, 0.0f, 0.0f), Vec4f(0.0f, 1.0f, 0.0f, 1.0f)),
        Vertex(Vec3f(2.0f, 0.0f, 0.0f), Vec4f(0.0f, 0.0f, 1.0f, 1.0f))
    };
    
    VertexBuffer vbo(BufferUsage::Static, vertices);
    VertexArray vao;
    VertexArray::Range range(1, 1);
    
    vao.bindTo(vbo, range);
    
    EXPECT_NE(vao.getCurrentVertexBuffer(), nullptr);
    EXPECT_EQ(vao.getRange().start, 1u);
    EXPECT_EQ(vao.getRange().count, 1u);
}

////////////////////////////////////////////////////////////

TEST_F(OpenGLTestEnvironment, VertexArray_BindToBothBuffers)
{
    std::vector<Vertex> vertices = {
        Vertex(Vec3f(0.0f, 0.0f, 0.0f), Vec4f(1.0f, 0.0f, 0.0f, 1.0f)),
        Vertex(Vec3f(1.0f, 0.0f, 0.0f), Vec4f(0.0f, 1.0f, 0.0f, 1.0f)),
        Vertex(Vec3f(0.0f, 1.0f, 0.0f), Vec4f(0.0f, 0.0f, 1.0f, 1.0f))
    };
    
    std::vector<size_t> indices = {0, 1, 2};
    
    VertexBuffer vbo(BufferUsage::Static, vertices);
    ElementBuffer ebo(BufferUsage::Static, indices);
    VertexArray vao;
    
    vao.bindTo(vbo);
    
    EXPECT_NE(vao.getCurrentVertexBuffer(), nullptr);
    EXPECT_EQ(vao.getRange().count, 3u);
}

////////////////////////////////////////////////////////////

TEST_F(OpenGLTestEnvironment, VertexArray_EqualityOperators)
{
    VertexArray vao1;
    VertexArray vao2;
    
    EXPECT_TRUE(vao1 != vao2);
    EXPECT_FALSE(vao1 == vao2);
    
    VertexArray vao3 = vao1;
    EXPECT_TRUE(vao1 != vao3);
    EXPECT_FALSE(vao1 == vao3);
}

////////////////////////////////////////////////////////////

TEST_F(OpenGLTestEnvironment, VertexArray_MoveAssignment)
{
    std::vector<Vertex> vertices = {
        Vertex(Vec3f(0.0f, 0.0f, 0.0f), Vec4f(1.0f, 0.0f, 0.0f, 1.0f))
    };
    
    VertexBuffer vbo(BufferUsage::Static, vertices);
    VertexArray original(vbo);
    unsigned int originalHandle = original.getNativeHandle();
    
    VertexArray moved;
    moved = std::move(original);
    
    EXPECT_EQ(moved.getNativeHandle(), originalHandle);
    EXPECT_EQ(original.getNativeHandle(), VertexArray::NullVertexArray);
    EXPECT_NE(moved.getCurrentVertexBuffer(), nullptr);
}

////////////////////////////////////////////////////////////

TEST_F(OpenGLTestEnvironment, VertexArray_CopyAssignment)
{
    std::vector<Vertex> vertices = {
        Vertex(Vec3f(0.0f, 0.0f, 0.0f), Vec4f(1.0f, 0.0f, 0.0f, 1.0f)),
        Vertex(Vec3f(1.0f, 0.0f, 0.0f), Vec4f(0.0f, 1.0f, 0.0f, 1.0f))
    };
    
    VertexBuffer vbo(BufferUsage::Static, vertices);
    VertexArray original(vbo);
    
    VertexArray copy;
    copy = original;
    
    EXPECT_NE(original.getNativeHandle(), copy.getNativeHandle());
    EXPECT_NE(copy.getCurrentVertexBuffer(), nullptr);
    EXPECT_EQ(copy.getRange().count, 2u);
}

////////////////////////////////////////////////////////////

TEST_F(OpenGLTestEnvironment, VertexArray_Release)
{
    std::vector<Vertex> vertices = {
        Vertex(Vec3f(0.0f, 0.0f, 0.0f), Vec4f(1.0f, 0.0f, 0.0f, 1.0f))
    };
    
    VertexBuffer vbo(BufferUsage::Static, vertices);
    VertexArray vao(vbo);
    unsigned int handle = vao.getNativeHandle();
    
    EXPECT_NE(handle, VertexArray::NullVertexArray);
    EXPECT_NE(vao.getCurrentVertexBuffer(), nullptr);
    
    vao.release();
    
    EXPECT_EQ(vao.getNativeHandle(), VertexArray::NullVertexArray);
    EXPECT_EQ(vao.getCurrentVertexBuffer(), nullptr);
    EXPECT_EQ(vao.getRange().start, 0u);
    EXPECT_EQ(vao.getRange().count, 0u);
}

////////////////////////////////////////////////////////////

TEST_F(OpenGLTestEnvironment, VertexArray_GetRange)
{
    std::vector<Vertex> vertices = {
        Vertex(Vec3f(0.0f, 0.0f, 0.0f), Vec4f(1.0f, 0.0f, 0.0f, 1.0f)),
        Vertex(Vec3f(1.0f, 0.0f, 0.0f), Vec4f(0.0f, 1.0f, 0.0f, 1.0f)),
        Vertex(Vec3f(2.0f, 0.0f, 0.0f), Vec4f(0.0f, 0.0f, 1.0f, 1.0f))
    };
    
    VertexBuffer vbo(BufferUsage::Static, vertices);
    VertexArray::Range range(1, 2);
    VertexArray vao(vbo, range);
    
    auto retrievedRange = vao.getRange();
    EXPECT_EQ(retrievedRange.start, 1u);
    EXPECT_EQ(retrievedRange.count, 2u);
}

////////////////////////////////////////////////////////////

TEST_F(OpenGLTestEnvironment, VertexArray_GetCurrentBuffers)
{
    std::vector<Vertex> vertices = {
        Vertex(Vec3f(0.0f, 0.0f, 0.0f), Vec4f(1.0f, 0.0f, 0.0f, 1.0f))
    };
    
    std::vector<size_t> indices = {0};
    
    VertexBuffer vbo(BufferUsage::Static, vertices);
    ElementBuffer ebo(BufferUsage::Static, indices);
    VertexArray vao;
    
    vao.bindTo(vbo);
    
    EXPECT_EQ(vao.getCurrentVertexBuffer(), &vbo);
}
