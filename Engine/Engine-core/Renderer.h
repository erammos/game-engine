#pragma once
#include <deque>
#include "Math.h"
#include "freetype-gl.h"

namespace Engine {
	namespace Graphics
	{
		class GraphicComponent;
		using namespace Math;
		struct VertexData
		{
			Vec4f vertex;
			Color color;
			Vec4f tex;
			VertexData() {};
			
		};
		

		class Renderer
        {
		
		public:
			virtual void Begin() = 0;
			virtual void Draw(GraphicComponent* renderable) = 0;
			virtual void End() = 0;
			virtual void SetModelViewMatrix(Mat4f& matrix) = 0;
			virtual void SetProjectionMatrix(Mat4f& matrix) = 0;
			virtual void  DrawText(texture_font_t * font,
				const char * text, Color color, int x, int y) = 0;
		};
	}
}
