#pragma once
#include <vector>
#include <GL/glew.h>
#include <string>
#include "math.h"


namespace Engine {
	namespace Graphics
	{
		
		class Shader
		{		
		public:
			GLuint program_id;
			const char* vertPath, *fragPath;
			Shader(const char* , const char*);
			~Shader();
			GLuint load();
			void enable();
			void disable();
			void setUniformMat4(const char * name, Math::Mat4f& matrix);
	
		};

		
	}
}