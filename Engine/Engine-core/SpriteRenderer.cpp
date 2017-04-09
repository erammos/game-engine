#include "SpriteRenderer.h"
#include "SpriteComponent.h"
#include "TextureManager.h"

void Engine::Graphics::SpriteRenderer::init()
{
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ibo);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER,m_vbo );
	glBufferData(GL_ARRAY_BUFFER, TOTAL_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(SHADER_VERTEX_ATTRIB);
	glEnableVertexAttribArray(SHADER_COLOR_ATTRIB);
	glEnableVertexAttribArray(SHADER_UV_ATTRIB);
	glEnableVertexAttribArray(SHADER_TEXTURE_ID_ATTRIB);

	glVertexAttribPointer(SHADER_VERTEX_ATTRIB, 4, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const GLvoid *)0);
	glVertexAttribPointer(SHADER_COLOR_ATTRIB, 4, GL_FLOAT, GL_FALSE, VERTEX_SIZE,(const GLvoid *)(offsetof(VertexData,VertexData::color)));
	glVertexAttribPointer(SHADER_UV_ATTRIB, 2, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const GLvoid *)(offsetof(VertexData, VertexData::uv)));
	glVertexAttribPointer(SHADER_TEXTURE_ID_ATTRIB, 1, GL_INT, GL_FALSE, VERTEX_SIZE, (const GLvoid *)(offsetof(VertexData, VertexData::tid)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLushort indices[TOTAL_INDICES_SIZE];
	int offset = 0;
	for (int i = 0; i < TOTAL_INDICES_SIZE; i += 6)
	{
		indices[i + 0] = offset + 0;
		indices[i + 1] = offset + 1;
		indices[i + 2] = offset + 2;

		indices[i + 3] = offset + 2;
		indices[i + 4] = offset + 3;
		indices[i + 5] = offset + 0;

		offset += 4;
	}
	
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, TOTAL_INDICES_SIZE * sizeof(GLushort), indices, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
	
	//glActiveTexture(GL_TEXTURE1);
	/*for (int i = 0; i < 2; i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		TextureManager::Inst()->BindTexture(i);

		//(glBindTExture(GL_TEXTURE_2D, TextureManager::Inst);
	}*/

}

Engine::Graphics::SpriteRenderer::SpriteRenderer()
{
	init();
}

Engine::Graphics::SpriteRenderer::~SpriteRenderer()
{
	
	glDeleteBuffers(1, &m_ibo);
	glDeleteBuffers(1, &m_vbo);
}




void Engine::Graphics::SpriteRenderer::Begin()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	m_buffer = (VertexData *)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
}

void Engine::Graphics::SpriteRenderer::Draw(GraphicsComponent* renderable)
{
	SpriteComponent * sprite = (SpriteComponent *)renderable;

	Color color = sprite->GetColor();
	Rect rect = sprite->GetRect();
	

	VertexData * p = &rect.bl;
	for (int i = 0; i < 4; i++)
	{
 		m_buffer->vertex = p->vertex;
		m_buffer->color = color;
		m_buffer->uv = p->uv;
		m_buffer->tid = p->tid;
		p++;
		m_buffer++;

	}
	m_indexCount += 6;
}
void Engine::Graphics::SpriteRenderer::End()
{
	
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_SHORT, NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	m_indexCount = 0;
}

void Engine::Graphics::SpriteRenderer::SetShaderId(GLuint shader_id)
{
	this->shader_id = shader_id;
	
}

void Engine::Graphics::SpriteRenderer::SetModelViewMatrix(Engine::Math::Mat4f& matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(shader_id, "model_matrix"), 1, GL_FALSE, matrix.values);

}

void Engine::Graphics::SpriteRenderer::SetProjectionMatrix(Engine::Math::Mat4f& matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(shader_id, "proj_matrix"), 1, GL_FALSE, matrix.values);

}

	

