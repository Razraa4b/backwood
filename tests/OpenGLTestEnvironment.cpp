#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "OpenGLTestEnvironment.hpp"

void OpenGLTestEnvironment::SetUpTestSuite()
{
	if (!glfwInit())
	{
		FAIL() << "Failed to initialize GLFW";
	}

	// OpenGL version 4.6
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

	// Create GLFW window
	auto window = glfwCreateWindow(1, 1, "Testing Window", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		FAIL() << "Failed to create GLFW window";
	}
	glfwMakeContextCurrent(window);

	// Load OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		glfwTerminate();
		FAIL() << "Failed to load OpenGL functions";
		return;
	}
    
    glfwHideWindow(window);
}

void OpenGLTestEnvironment::TearDownTestSuite()
{
    if(auto* context = glfwGetCurrentContext())
    {
        glfwDestroyWindow(context);
    }
    glfwTerminate();
}
