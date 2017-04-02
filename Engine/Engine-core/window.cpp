#include "window.h"
#include <iostream>

namespace Engine {
	namespace Graphics
	{

		
		void windowResizeCB(GLFWwindow * window, int width, int height)
		{

			glViewport(0, 0, width, height);

		}
		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			Window* wnd= (Window *)glfwGetWindowUserPointer(window);
			
			wnd->m_Keys[key]= action != GLFW_RELEASE;
		}
		void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
		{
			Window* wnd = (Window *)glfwGetWindowUserPointer(window);

			wnd->m_MouseButtons[button] = action != GLFW_RELEASE;
		}
		void mouse_movement(GLFWwindow* window, double x, double y)
		{
			Window* wnd = (Window *)glfwGetWindowUserPointer(window);

			wnd->mouse_x = x;
			wnd->mouse_y = y;
		}
		void Window::init()
		{
			if (!glfwInit())
			{
				std::cout << "Failed to init window";
				glfwTerminate();
				return;
			}

			
			gl_window = glfwCreateWindow(width, height, name, NULL, NULL);
			
			if (!gl_window)
			{
				glfwTerminate();
				std::cout << "Failed to create window";
				return;
			}
			glfwMakeContextCurrent(gl_window);
		
			
			
			glfwSetFramebufferSizeCallback(gl_window, windowResizeCB);
			glfwSetWindowUserPointer(gl_window, this);
			glfwSetKeyCallback(gl_window, key_callback);
			glfwSetMouseButtonCallback(gl_window, mouse_button_callback);
			glfwSetCursorPosCallback(gl_window, mouse_movement);
			if (glewInit() != GLEW_OK)
			{
				std::cout << "Failed to init GLEW";
			}
		}
		void Window::getGLWindow()
		{
		}
		Window::Window(const char * name, int width, int height)
		{
			this->name = name;
			this->width = width;
			this->height = height;
			init();
			for (int i = 0; i < MAX_KEYS; i++)
			{
				m_Keys[i] = false;
			}
			for (int i = 0; i < MAX_BUTTONS; i++)
			{
				m_MouseButtons[i] = false;
			}

		}
		Window::~Window()
		{
			glfwTerminate();
		}
		void Window::update() 
		{
			GLenum error = glGetError();
			if (error != GL_NO_ERROR)
			{
				std::cout << "OpenGL Error:" << error << std::endl;
			}

			glfwPollEvents();
			glfwSwapBuffers(gl_window);

		}
		int Window::closed()
		{
			
			return glfwWindowShouldClose(gl_window);
		}
		void Window::clear()
		{
			glClear(GL_COLOR_BUFFER_BIT);
			
			//glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glClearColor(0.1f, 0.0f, 0.0f, 0.0f);
			
			
		}

		bool Window::isKeyPressed(int keycode)
		{
			if (keycode >= MAX_KEYS)
				return false;

			return m_Keys[keycode];
		}

		bool Window::isMouseButtonPressed(int button)
		{
			if (button >= MAX_BUTTONS)
				return false;

			return m_MouseButtons[button];
		}
		bool Window::OnMouseMovement(int &x, int &y)
		{
			
			x = mouse_x;
			y = mouse_y;
			return true;
		}

	
		
	}
}