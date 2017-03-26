#pragma once
#pragma once
#pragma once
#include <glew.h>
#include <vector>
#include "VertexBuffer.h"

namespace Engine {
	namespace Graphics {

		class VertexArray
		{
		private:
			GLuint array_id;
			GLuint count;
			std::vector <Buffer*> buffers;
		public:
			VertexArray()
			{
				glGenVertexArrays(1, &array_id);

			}
			~VertexArray()
			{				
				for (int i = 0; i < buffers.size(); i++) delete buffers[i];
			}
			void addBuffer(Buffer* buffer, GLuint index)
			{
				bind();
				buffer->bind();
				glEnableVertexAttribArray(index);
				glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);
				buffer->unbind();
				unbind();

			}

			void bind()
			{
				glBindVertexArray(array_id);
			}
			void unbind()
			{
			   glBindVertexArray(0);
			}
		};
	}
}

