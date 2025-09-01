#include <format>
#include "utils/Logger.hpp"
#include "ext/GLLogging.hpp"
#include "SimpleWindow.hpp"

#if defined(_WIN32)
#define GLFW_EXPOSE_NATIVE_WIN32
#include <windows.h>

#elif defined(__linux__)
#define GLFW_EXPOSE_NATIVE_X11
#define GLFW_EXPOSE_NATIVE_GLX
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#elif defined(__APPLE__)
#include <AppKit/AppKit.h>
#endif

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

namespace bw
{
	struct WindowImpl
	{
		GLFWwindow* glfwWindow;
	};

	////////////////////////////////////////////////////////////

	void _framebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	////////////////////////////////////////////////////////////

	SimpleWindow::SimpleWindow(std::string title, Recti rect) : _impl(std::make_unique<WindowImpl>()), _logger(Logger::getInstance())
	{
		if (!glfwInit())
		{
			_logger.fatal("Failed to initialize GLFW");
			return;
		}

		// OpenGL version 4.6
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

		// Create GLFW window
		_impl->glfwWindow = glfwCreateWindow(rect.size.x, rect.size.y, title.c_str(), nullptr, nullptr);
		if (!_impl->glfwWindow)
		{
			glfwTerminate();
			_logger.fatal("Failed to create GLFW window");
			return;
		}
		glfwMakeContextCurrent(_impl->glfwWindow);
		_logger.info("Successfully created GLFW window");

		// Load OpenGL
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			glfwTerminate();
			_logger.fatal("Failed to create GLFW window");
			return;
		}
		_logger.info("Successfully initialized glad and loaded OpenGL");

		// Move window to specified position
		move(rect.position);

		glfwSetFramebufferSizeCallback(_impl->glfwWindow, _framebufferSizeCallback);
	}

	////////////////////////////////////////////////////////////

	SimpleWindow::SimpleWindow(std::string title, Vec2i size) : SimpleWindow(title, Recti { { 0, 0 }, size }) { }

	////////////////////////////////////////////////////////////

	SimpleWindow::SimpleWindow() : SimpleWindow("The simplest window", { 700, 450 }) { }

	////////////////////////////////////////////////////////////

	SimpleWindow::~SimpleWindow()
	{
		auto title = getTitle();
		glfwDestroyWindow(_impl->glfwWindow);
        glfwTerminate();
		_logger.info(std::format("SimpleWindow with the title \"{}\" destroyed", title));
        _logger.info("GLFW context terminated");
	}

	////////////////////////////////////////////////////////////

	void SimpleWindow::resize(Vec2i size) const
	{
		glfwSetWindowSize(_impl->glfwWindow, size.x, size.y);
	}
	
	////////////////////////////////////////////////////////////
	
	void SimpleWindow::move(Vec2i position) const 
	{
		glfwSetWindowPos(_impl->glfwWindow, position.x, position.y);
	}

	////////////////////////////////////////////////////////////

	void SimpleWindow::show() const
	{
		glfwShowWindow(_impl->glfwWindow);
	}

	////////////////////////////////////////////////////////////

	void SimpleWindow::hide() const 
	{
		glfwHideWindow(_impl->glfwWindow);
	}

	////////////////////////////////////////////////////////////

	void SimpleWindow::clear(Vec4i color)
	{
		glClearColor(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	////////////////////////////////////////////////////////////

	void SimpleWindow::update()
	{
		glfwSwapBuffers(_impl->glfwWindow);
		glfwPollEvents();

        int error = glGetError();
        if(error != GL_NO_ERROR)
        {
            GL_ERROR(std::format("An error occurred under the code {}", error));
        }
    }

	////////////////////////////////////////////////////////////

	bool SimpleWindow::isVisible() const 
	{
		return glfwGetWindowAttrib(_impl->glfwWindow, GLFW_VISIBLE) == GLFW_TRUE;
	}

	////////////////////////////////////////////////////////////

	bool SimpleWindow::isOpen() const
	{
		return !glfwWindowShouldClose(_impl->glfwWindow);
	}

	////////////////////////////////////////////////////////////

	void SimpleWindow::close() const
	{
		if (_impl->glfwWindow)
		{
			glfwSetWindowShouldClose(_impl->glfwWindow, true);
			_logger.info(std::format("Window with the title \"{}\" closed", getTitle()));
		}
	}

	////////////////////////////////////////////////////////////

	Vec2i SimpleWindow::getPosition() const
	{
		Vec2i position;
		glfwGetWindowPos(_impl->glfwWindow, &position.x, &position.y);
		return position;
	}

	////////////////////////////////////////////////////////////

	Vec2i SimpleWindow::getSize() const
	{
		Vec2i size;
		glfwGetWindowSize(_impl->glfwWindow, &size.x, &size.y);
		return size;
	}

	////////////////////////////////////////////////////////////

	std::string SimpleWindow::getTitle() const
	{
		return glfwGetWindowTitle(_impl->glfwWindow);
	}

	////////////////////////////////////////////////////////////

	void* SimpleWindow::getNativeHandle()
	{
#if defined(_WIN32)
		return glfwGetWin32Window(_impl->glfwWindow);
#elif defined(__linux__)
		return (void*)glfwGetX11Window(_impl->glfwWindow);
#elif defined(__APPLE__)
		return glfwGetCocoaWindow(_impl->glfwWindow);
#endif
	}

	////////////////////////////////////////////////////////////

	void* SimpleWindow::getGraphicsContext()
	{
		return _impl->glfwWindow;
	}
}
