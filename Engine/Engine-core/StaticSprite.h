#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "GraphicsComponent.h"
#include "Shader.h"
namespace Engine {
	namespace Graphics {
		using namespace Math;
	
		class StaticSprite: public GraphicsComponent
		{
		private:
			Shader* shader2D;
			VertexArray* vertexArray;
			IndexBuffer* indexBuffer;
		public:
			StaticSprite(Vec3f pos, Vec2f s, Color c,Shader* shader):GraphicsComponent(c)
			{
				shader2D = shader;

		
				vertexArray = new VertexArray();
				GLfloat vertices[] =
				{
					0, 0, 0,
					0, s.y, 0,
					s.x, s.y, 0,
					s.x, 0, 0
				};
				GLfloat colors[] =
				{
					color.r , color.g , color.b , color.a,
					color.r , color.g , color.b , color.a,
					color.r , color.g , color.b , color.a,
					color.r , color.g , color.b , color.a
				};
				GLushort indices[] =
				{
					0,1,2,2,3,0
				};
				vertexArray->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
				vertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 1);
				indexBuffer = new IndexBuffer(indices, 6);
			}
			virtual ~StaticSprite()
			{
				delete vertexArray;
				delete indexBuffer;
			}
			inline  VertexArray* getVertexArray() const { return vertexArray; }
			inline  IndexBuffer* getIndexBuffer() const { return indexBuffer; }
			inline  Shader * getShader() const { return shader2D; }
		};
	}

}
