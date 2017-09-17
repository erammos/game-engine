#pragma once
#include "GraphicComponent.h"
#include "Renderer.h"
#include <vector>
namespace Engine {
	namespace Graphics {

		struct Rect
		{
			VertexData bl;
			VertexData tl;
			VertexData tr;
			VertexData br;
		};

		class RectComponent : public GraphicComponent
		{
		protected:
			int x;
			int y;
			int width = 0;
			int height = 0;
			const char * imageName;
			Rect rect;
			std::vector<Rect> outRect;

		public:

			RectComponent(float x, float y, float width, float height, Color c);
			RectComponent(Color c);
			virtual ~RectComponent();

		      virtual std::vector<Rect> GetRects() const {
				 return outRect; }
			virtual void Update() override;
			virtual void  Init() override;
			inline int  GetWidth() const {
				return width;
			}
			inline int GetHeight() const {
				return height;
			}

		};
	}
}