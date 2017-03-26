#pragma once
#include <glew.h>
namespace Engine {
	namespace Graphics{

	class Buffer
	{
	private:
		GLuint buffer_id;
		GLuint componentCount;
	public:
		Buffer(GLfloat *data, GLsizei count, GLuint componentCount)
		{
			this->componentCount = componentCount;
			glGenBuffers(1, &buffer_id);
			glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
			glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

		}
		void bind()
		{
			glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
		}
		void unbind()
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		inline GLuint getComponentCount()
		{
			return componentCount;
		}

	};

}

}
