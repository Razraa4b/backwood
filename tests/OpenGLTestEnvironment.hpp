#pragma once

#include <gtest/gtest.h>

class OpenGLTestEnvironment : public testing::Test
{
protected:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};
