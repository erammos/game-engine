#pragma once
#include <deque>
#include "Math.h"

namespace Engine {
	namespace Graphics
	{
		class GraphicsComponent;
		using namespace Math;
		struct VertexData
		{
			Vec3f vertex;
			Color color;
			Vec3f tex;
			VertexData() {};
			
		};
		

		class Renderer
        {
		
		public:
			virtual void Begin() = 0;
			virtual void Draw(GraphicsComponent* renderable) = 0;
			virtual void End() = 0;
			virtual void SetModelViewMatrix(Mat4f& matrix) = 0;
			virtual void SetProjectionMatrix(Mat4f& matrix) = 0;

		};
	}
}
