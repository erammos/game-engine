#pragma once
#include <GL/glew.h>
#include <string>
#include "FreeImage.h"
namespace Engine {
	namespace Graphics
	{
		class Texture
		{
		private:
			std :: string m_Path;
		    GLuint m_TID;
			unsigned int width, height;
		public:
			Texture(const char* path);
			~Texture();
			void bind() const;
			void unbind() const;

			inline const unsigned int getWidth() const { return width; }
            inline const unsigned int getHeight() const { return height; }
		private:
			BYTE* load(const char* filename);
			
		};

	}
}