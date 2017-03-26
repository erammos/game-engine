#pragma once

#include <deque>
#include <glew.h>

#include "Renderer.h"

namespace Engine {
	namespace Graphics
	{

#define MAX_SPRITES        10000
#define VERTEX_SIZE        sizeof(VertexData)
#define SPRITE_SIZE        VERTEX_SIZE * 4
#define TOTAL_BUFFER_SIZE  SPRITE_SIZE * MAX_SPRITES
#define TOTAL_INDICES_SIZE MAX_SPRITES * 6
#define SHADER_VERTEX_ATTRIB 0
#define SHADER_COLOR_ATTRIB 1
#define SHADER_UV_ATTRIB 2
#define	SHADER_TEXTURE_ID_ATTRIB 3

	
		class SpriteRenderer: public Renderer
		{
		private:

			GLuint m_vbo;
			GLuint m_vao;
			GLuint m_ibo;
			GLuint shader_id;
			VertexData* m_buffer;
			
			int m_indexCount = 0;
			void init();
		public:
			SpriteRenderer();
			 ~SpriteRenderer();
			 void Begin() override;
			 void Draw(GraphicsComponent* renderable) override;		
			 void End() override;
			 void SetShaderId(GLuint shader_id);
			 void SetModelViewMatrix(Mat4f& matrix) override;
			 void SetProjectionMatrix(Mat4f& matrix) override;




		};
	}
}
