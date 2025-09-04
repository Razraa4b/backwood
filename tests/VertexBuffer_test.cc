#include <gtest/gtest.h>
#include "OpenGLTestEnvironment.hpp"
#include <graphics/VertexBuffer.hpp>

using namespace bw;
using namespace bw::low_level;

TEST_F(OpenGLTestEnvironment, VertexBuffer_DefaultConstructor)
{
    VertexBuffer buffer(BufferUsage::Static);
    
    EXPECT_NE(buffer.getNativeHandle(), VertexBuffer::NullVertexBuffer);
    EXPECT_EQ(buffer.size(), 0u);
    EXPECT_EQ(buffer.capacity(), 0u);
    EXPECT_EQ(buffer.getUsage(), BufferUsage::Static);
}

////////////////////////////////////////////////////////////

TEST_F(OpenGLTestEnvironment, VertexBuffer_ConstructorWithInitialData)
{
    std::vector<Vertex> vertices = {
        Vertex(Vec3f(0.0f, 0.0f, 0.0f), Vec4f(1.0f, 0.0f, 0.0f, 1.0f)),
        Vertex(Vec3f(1.0f, 0.0f, 0.0f), Vec4f(0.0f, 1.0f, 0.0f, 1.0f)),
        Vertex(Vec3f(0.0f, 1.0f, 0.0f), Vec4f(0.0f, 0.0f, 1.0f, 1.0f))
    };
    
    VertexBuffer buffer(BufferUsage::Static, vertices);
    
    EXPECT_EQ(buffer.size(), 3u);
    EXPECT_GE(buffer.capacity(), 3 * sizeof(Vertex));
    EXPECT_EQ(buffer.getUsage(), BufferUsage::Static);
    
    auto retrievedData = buffer.data();
    EXPECT_EQ(retrievedData.size(), 3u);
}

////////////////////////////////////////////////////////////

TEST_F(OpenGLTestEnvironment, VertexBuffer_ConstructorWithReserve)
{
    const size_t reserveSize = 100;
    VertexBuffer buffer(BufferUsage::Dynamic, reserveSize);
    
    EXPECT_EQ(buffer.size(), 100u);
    EXPECT_GE(buffer.capacity(), reserveSize * sizeof(Vertex));
    EXPECT_EQ(buffer.getUsage(), BufferUsage::Dynamic);
}

////////////////////////////////////////////////////////////

TEST_F(OpenGLTestEnvironment, VertexBuffer_CopyConstructor)
{
    std::vector<Vertex> vertices = {
        Vertex(Vec3f(0.0f, 0.0f, 0.0f), Vec4f(1.0f, 0.0f, 0.0f, 1.0f)),
        Vertex(Vec3f(1.0f, 0.0f, 0.0f), Vec4f(0.0f, 1.0f, 0.0f, 1.0f))
    };
    
    VertexBuffer original(BufferUsage::Static, vertices);
    VertexBuffer copy(original);
    
    EXPECT_NE(original.getNativeHandle(), copy.getNativeHandle());
    EXPECT_EQ(original.size(), copy.size());
    EXPECT_EQ(original.capacity(), copy.capacity());
    
    auto originalData = original.data();
    auto copyData = copy.data();
    EXPECT_EQ(originalData.size(), copyData.size());
}

////////////////////////////////////////////////////////////

TEST_F(OpenGLTestEnvironment, VertexBuffer_MoveConstructor)
{
    std::vector<Vertex> vertices = {
        Vertex(Vec3f(0.0f, 0.0f, 0.0f), Vec4f(1.0f, 0.0f, 0.0f, 1.0f))
    };
    
    VertexBuffer original(BufferUsage::Static, vertices);
    unsigned int originalHandle = original.getNativeHandle();
    
    VertexBuffer moved(std::move(original));
    
    EXPECT_EQ(moved.getNativeHandle(), originalHandle);
    EXPECT_EQ(original.getNativeHandle(), VertexBuffer::NullVertexBuffer);
    EXPECT_EQ(moved.size(), 1u);
}

////////////////////////////////////////////////////////////

TEST_F(OpenGLTestEnvironment, VertexBuffer_UpdateData)
{
    VertexBuffer buffer(BufferUsage::Dynamic, 3);
    
    std::vector<Vertex> vertices = {
        Vertex(Vec3f(0.0f, 0.0f, 0.0f), Vec4f(1.0f, 0.0f, 0.0f, 1.0f)),
        Vertex(Vec3f(1.0f, 0.0f, 0.0f), Vec4f(0.0f, 1.0f, 0.0f, 1.0f)),
        Vertex(Vec3f(0.0f, 1.0f, 0.0f), Vec4f(0.0f, 0.0f, 1.0f, 1.0f))
    };
    
    buffer.update(vertices);
    
    auto retrievedData = buffer.data();
    EXPECT_EQ(retrievedData.size(), 3u);
}

////////////////////////////////////////////////////////////

TEST_F(OpenGLTestEnvironment, VertexBuffer_UpdateDataWithOffset)
{
    VertexBuffer buffer(BufferUsage::Dynamic, 5);
    
    std::vector<Vertex> initialVertices = {
        Vertex(Vec3f(0.0f, 0.0f, 0.0f), Vec4f(1.0f, 0.0f, 0.0f, 1.0f)),
        Vertex(Vec3f(1.0f, 0.0f, 0.0f), Vec4f(0.0f, 1.0f, 0.0f, 1.0f)),
        Vertex(Vec3f(0.0f, 1.0f, 0.0f), Vec4f(0.0f, 0.0f, 1.0f, 1.0f))
    };
    
    buffer.update(initialVertices);
    
    std::vector<Vertex> updateVertices = {
        Vertex(Vec3f(2.0f, 2.0f, 2.0f), Vec4f(1.0f, 1.0f, 1.0f, 1.0f))
    };
    
    buffer.update(1, updateVertices);
    
    auto retrievedData = buffer.data();
    EXPECT_EQ(retrievedData.size(), 5u);
}

////////////////////////////////////////////////////////////

TEST_F(OpenGLTestEnvironment, VertexBuffer_ReserveMemory)
{
    VertexBuffer buffer(BufferUsage::Dynamic);
    const size_t newCapacity = 200 * sizeof(Vertex);
    
    buffer.reserve(200);
    
    EXPECT_GE(buffer.capacity(), newCapacity);
    EXPECT_EQ(buffer.size(), 200u);
}

////////////////////////////////////////////////////////////

TEST_F(OpenGLTestEnvironment, VertexBuffer_CopyTo)
{
    std::vector<Vertex> vertices = {
        Vertex(Vec3f(0.0f, 0.0f, 0.0f), Vec4f(1.0f, 0.0f, 0.0f, 1.0f)),
        Vertex(Vec3f(1.0f, 0.0f, 0.0f), Vec4f(0.0f, 1.0f, 0.0f, 1.0f))
    };
    
    VertexBuffer source(BufferUsage::Static, vertices);
    VertexBuffer destination(BufferUsage::Static);
    
    source.copyTo(destination);
    
    EXPECT_EQ(source.size(), destination.size());
    
    auto sourceData = source.data();
    auto destinationData = destination.data();
    EXPECT_EQ(sourceData.size(), destinationData.size());
}

////////////////////////////////////////////////////////////

TEST_F(OpenGLTestEnvironment, VertexBuffer_DataRange)
{
    std::vector<Vertex> vertices = {
        Vertex(Vec3f(0.0f, 0.0f, 0.0f), Vec4f(1.0f, 0.0f, 0.0f, 1.0f)),
        Vertex(Vec3f(1.0f, 0.0f, 0.0f), Vec4f(0.0f, 1.0f, 0.0f, 1.0f)),
        Vertex(Vec3f(2.0f, 0.0f, 0.0f), Vec4f(0.0f, 0.0f, 1.0f, 1.0f))
    };
    
    VertexBuffer buffer(BufferUsage::Static, vertices);
    
    auto rangeData = buffer.data(1, 2);
    EXPECT_EQ(rangeData.size(), 2u);
}

////////////////////////////////////////////////////////////

TEST_F(OpenGLTestEnvironment, VertexBuffer_EqualityOperators)
{
    VertexBuffer buffer1(BufferUsage::Static);
    VertexBuffer buffer2(BufferUsage::Static);
    
    EXPECT_TRUE(buffer1 != buffer2);
    EXPECT_FALSE(buffer1 == buffer2);
    
    VertexBuffer buffer3 = buffer1;
    EXPECT_TRUE(buffer1 != buffer3);
    EXPECT_FALSE(buffer1 == buffer3);
}

////////////////////////////////////////////////////////////

TEST_F(OpenGLTestEnvironment, VertexBuffer_MoveAssignment)
{
    std::vector<Vertex> vertices = {
        Vertex(Vec3f(0.0f, 0.0f, 0.0f), Vec4f(1.0f, 0.0f, 0.0f, 1.0f))
    };
    
    VertexBuffer original(BufferUsage::Static, vertices);
    unsigned int originalHandle = original.getNativeHandle();
    
    VertexBuffer moved(BufferUsage::Dynamic);
    moved = std::move(original);
    
    EXPECT_EQ(moved.getNativeHandle(), originalHandle);
    EXPECT_EQ(original.getNativeHandle(), VertexBuffer::NullVertexBuffer);
}

////////////////////////////////////////////////////////////

TEST_F(OpenGLTestEnvironment, VertexBuffer_CopyAssignment)
{
    std::vector<Vertex> vertices = {
        Vertex(Vec3f(0.0f, 0.0f, 0.0f), Vec4f(1.0f, 0.0f, 0.0f, 1.0f)),
        Vertex(Vec3f(1.0f, 0.0f, 0.0f), Vec4f(0.0f, 1.0f, 0.0f, 1.0f))
    };
    
    VertexBuffer original(BufferUsage::Static, vertices);
    VertexBuffer copy(BufferUsage::Dynamic);
    
    copy = original;
    
    EXPECT_NE(original.getNativeHandle(), copy.getNativeHandle());
    EXPECT_EQ(original.size(), copy.size());
}

////////////////////////////////////////////////////////////

TEST_F(OpenGLTestEnvironment, VertexBuffer_Release)
{
    VertexBuffer buffer(BufferUsage::Static);
    unsigned int handle = buffer.getNativeHandle();
    
    EXPECT_NE(handle, VertexBuffer::NullVertexBuffer);
    
    buffer.release();
    
    EXPECT_EQ(buffer.getNativeHandle(), VertexBuffer::NullVertexBuffer);
}
