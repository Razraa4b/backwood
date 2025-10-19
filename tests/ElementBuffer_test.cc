#include <gtest/gtest.h>
#include "OpenGLTestEnvironment.hpp"
#include <graphics/ElementBuffer.hpp>

using namespace bw;
using namespace bw::low_level;

TEST_F(OpenGLTestEnvironment, ElementBuffer_DefaultConstructor)
{
    ElementBuffer buffer(BufferUsage::Static);
    
    EXPECT_NE(buffer.getNativeHandle(), ElementBuffer::NullElementBuffer);
    EXPECT_EQ(buffer.size(), 0u);
    EXPECT_EQ(buffer.capacity(), 0u);
    EXPECT_EQ(buffer.getUsage(), BufferUsage::Static);
}

////////////////////////////////////////////////////////////

TEST_F(OpenGLTestEnvironment, ElementBuffer_ConstructorWithInitialData)
{
    std::vector<size_t> indices = {0, 1, 2, 0, 2, 3};
    
    ElementBuffer buffer(BufferUsage::Static, indices);
    
    EXPECT_EQ(buffer.size(), 6u);
    EXPECT_GE(buffer.capacity(), 6 * sizeof(size_t));
    EXPECT_EQ(buffer.getUsage(), BufferUsage::Static);
    
    auto retrievedData = buffer.data();
    EXPECT_EQ(retrievedData.size(), 6u);
    EXPECT_EQ(retrievedData, indices);
}

////////////////////////////////////////////////////////////

TEST_F(OpenGLTestEnvironment, ElementBuffer_ConstructorWithReserve)
{
    const size_t reserveSize = 100;
    ElementBuffer buffer(BufferUsage::Dynamic, reserveSize);
    
    EXPECT_EQ(buffer.size(), 100u);
    EXPECT_GE(buffer.capacity(), reserveSize * sizeof(size_t));
    EXPECT_EQ(buffer.getUsage(), BufferUsage::Dynamic);
}

////////////////////////////////////////////////////////////

TEST_F(OpenGLTestEnvironment, ElementBuffer_CopyConstructor)
{
    std::vector<size_t> indices = {0, 1, 2, 0, 2, 3};
    
    ElementBuffer original(BufferUsage::Static, indices);
    ElementBuffer copy(original);
    
    EXPECT_NE(original.getNativeHandle(), copy.getNativeHandle());
    EXPECT_EQ(original.size(), copy.size());
    EXPECT_EQ(original.capacity(), copy.capacity());
    
    auto originalData = original.data();
    auto copyData = copy.data();
    EXPECT_EQ(originalData.size(), copyData.size());
    EXPECT_EQ(originalData, copyData);
}

////////////////////////////////////////////////////////////

TEST_F(OpenGLTestEnvironment, ElementBuffer_MoveConstructor)
{
    std::vector<size_t> indices = {0, 1, 2};
    
    ElementBuffer original(BufferUsage::Static, indices);
    unsigned int originalHandle = original.getNativeHandle();
    
    ElementBuffer moved(std::move(original));
    
    EXPECT_EQ(moved.getNativeHandle(), originalHandle);
    EXPECT_EQ(original.getNativeHandle(), ElementBuffer::NullElementBuffer);
    EXPECT_EQ(moved.size(), 3u);
}

////////////////////////////////////////////////////////////

TEST_F(OpenGLTestEnvironment, ElementBuffer_UpdateData)
{
    ElementBuffer buffer(BufferUsage::Dynamic, 3);
    
    std::vector<size_t> indices = {0, 1, 2};
    
    buffer.update(indices);
    
    auto retrievedData = buffer.data();
    EXPECT_EQ(retrievedData.size(), 3u);
    EXPECT_EQ(retrievedData, indices);
}

////////////////////////////////////////////////////////////

TEST_F(OpenGLTestEnvironment, ElementBuffer_UpdateDataWithOffset)
{
    ElementBuffer buffer(BufferUsage::Dynamic, 5);
    
    std::vector<size_t> initialIndices = {0, 1, 2};
    
    buffer.update(initialIndices);
    
    std::vector<size_t> updateIndices = {42};
    
    buffer.update(1, updateIndices);
    
    auto retrievedData = buffer.data();
    EXPECT_EQ(retrievedData.size(), 5u);
    // Проверяем, что данные обновились корректно
    EXPECT_EQ(retrievedData[0], 0u);
    EXPECT_EQ(retrievedData[1], 42u);
    EXPECT_EQ(retrievedData[2], 2u);
}

////////////////////////////////////////////////////////////

TEST_F(OpenGLTestEnvironment, ElementBuffer_ReserveMemory)
{
    ElementBuffer buffer(BufferUsage::Dynamic);
    const size_t newCapacity = 200;
    
    buffer.reserve(newCapacity);
    
    EXPECT_GE(buffer.capacity(), newCapacity * sizeof(size_t));
    EXPECT_EQ(buffer.size(), newCapacity);
}

////////////////////////////////////////////////////////////

TEST_F(OpenGLTestEnvironment, ElementBuffer_CopyTo)
{
    std::vector<size_t> indices = {0, 1, 2, 3, 4};
    
    ElementBuffer source(BufferUsage::Static, indices);
    ElementBuffer destination(BufferUsage::Static);
    
    source.copyTo(destination);
    
    EXPECT_EQ(source.size(), destination.size());
    
    auto sourceData = source.data();
    auto destinationData = destination.data();
    EXPECT_EQ(sourceData.size(), destinationData.size());
    EXPECT_EQ(sourceData, destinationData);
}

////////////////////////////////////////////////////////////

TEST_F(OpenGLTestEnvironment, ElementBuffer_DataRange)
{
    std::vector<size_t> indices = {10, 20, 30, 40, 50};
    
    ElementBuffer buffer(BufferUsage::Static, indices);
    
    auto rangeData = buffer.data(1, 3);
    EXPECT_EQ(rangeData.size(), 3u);
    EXPECT_EQ(rangeData[0], 20u);
    EXPECT_EQ(rangeData[1], 30u);
    EXPECT_EQ(rangeData[2], 40u);
}

////////////////////////////////////////////////////////////

TEST_F(OpenGLTestEnvironment, ElementBuffer_EqualityOperators)
{
    ElementBuffer buffer1(BufferUsage::Static);
    ElementBuffer buffer2(BufferUsage::Static);
    
    EXPECT_TRUE(buffer1 != buffer2);
    EXPECT_FALSE(buffer1 == buffer2);
    
    ElementBuffer buffer3 = buffer1;
    EXPECT_TRUE(buffer1 != buffer3); // Разные handles
    EXPECT_FALSE(buffer1 == buffer3);
}

////////////////////////////////////////////////////////////

TEST_F(OpenGLTestEnvironment, ElementBuffer_MoveAssignment)
{
    std::vector<size_t> indices = {0, 1, 2};
    
    ElementBuffer original(BufferUsage::Static, indices);
    unsigned int originalHandle = original.getNativeHandle();
    
    ElementBuffer moved(BufferUsage::Dynamic);
    moved = std::move(original);
    
    EXPECT_EQ(moved.getNativeHandle(), originalHandle);
    EXPECT_EQ(original.getNativeHandle(), ElementBuffer::NullElementBuffer);
    EXPECT_EQ(moved.size(), 3u);
}

////////////////////////////////////////////////////////////

TEST_F(OpenGLTestEnvironment, ElementBuffer_CopyAssignment)
{
    std::vector<size_t> indices = {5, 10, 15, 20};
    
    ElementBuffer original(BufferUsage::Static, indices);
    ElementBuffer copy(BufferUsage::Dynamic);
    
    copy = original;
    
    EXPECT_NE(original.getNativeHandle(), copy.getNativeHandle());
    EXPECT_EQ(original.size(), copy.size());
    
    auto originalData = original.data();
    auto copyData = copy.data();
    EXPECT_EQ(originalData, copyData);
}

////////////////////////////////////////////////////////////

TEST_F(OpenGLTestEnvironment, ElementBuffer_Release)
{
    ElementBuffer buffer(BufferUsage::Static);
    unsigned int handle = buffer.getNativeHandle();
    
    EXPECT_NE(handle, ElementBuffer::NullElementBuffer);
    
    buffer.release();
    
    EXPECT_EQ(buffer.getNativeHandle(), ElementBuffer::NullElementBuffer);
}

////////////////////////////////////////////////////////////

TEST_F(OpenGLTestEnvironment, ElementBuffer_ReserveSmallerSize)
{
    ElementBuffer buffer(BufferUsage::Dynamic, 10);
    
    // Изначальный размер
    size_t initialSize = buffer.size();
    size_t initialCapacity = buffer.capacity();
    
    // Пытаемся зарезервировать меньше - не должно измениться
    buffer.reserve(5);
    
    EXPECT_EQ(buffer.size(), initialSize);
    EXPECT_EQ(buffer.capacity(), initialCapacity);
}

////////////////////////////////////////////////////////////

TEST_F(OpenGLTestEnvironment, ElementBuffer_EmptyData)
{
    ElementBuffer buffer(BufferUsage::Static);
    
    auto emptyData = buffer.data();
    EXPECT_TRUE(emptyData.empty());
    
    auto rangeData = buffer.data(0, 0);
    EXPECT_TRUE(rangeData.empty());
}

////////////////////////////////////////////////////////////

TEST_F(OpenGLTestEnvironment, ElementBuffer_UsageTypeConversion)
{
    ElementBuffer staticBuffer(BufferUsage::Static);
    EXPECT_EQ(staticBuffer.getUsage(), BufferUsage::Static);
    
    ElementBuffer dynamicBuffer(BufferUsage::Dynamic);
    EXPECT_EQ(dynamicBuffer.getUsage(), BufferUsage::Dynamic);
    
    ElementBuffer streamBuffer(BufferUsage::Stream);
    EXPECT_EQ(streamBuffer.getUsage(), BufferUsage::Stream);
}
