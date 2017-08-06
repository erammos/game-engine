#pragma once
#include <GL/glew.h>
namespace Engine {
	namespace Graphics {

		class IndexBuffer
		{
		private:
			GLuint buffer_id;
			GLuint count;
		public:
			IndexBuffer(GLushort *data, GLsizei count)
			{
				this->count = count;
				glGenBuffers(1, &buffer_id);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), data, GL_STATIC_DRAW);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			}
			void bind()
			{
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id);
			}
			void unbind()
			{
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			}
			inline GLuint getCount()
			{
				return count;
			}

		};
	}
}
