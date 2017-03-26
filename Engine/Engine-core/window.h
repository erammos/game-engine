#pragma once
#include <glew.h>
#include <glfw3.h>
#define MAX_KEYS 256
#define MAX_BUTTONS 32
namespace Engine {
	namespace Graphics
	{

		//TODO change input handling to seperate class, use observer patterns
		class Window
		{
		 private:
			const char* name;
			int width, height;
			GLFWwindow *gl_window;
			
			void init();
		protected: 
			void getGLWindow();
		public:
			Window(const char* name, int width, int height);
			~Window();
			bool m_Keys[MAX_KEYS];
			bool m_MouseButtons[MAX_BUTTONS];
			int mouse_x;
			int mouse_y;
			void update();
			int closed();
			void clear();
			inline int getWidth()
			{
				return width;
			}
			inline int getHeight()
			{
				return height;
			}

			 bool isKeyPressed(int keycode);

			 bool isMouseButtonPressed(int button);

			bool OnMouseMovement(int & x, int & y);
		
		};
		void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods);
	}

}