#pragma once
#include "GraphicComponent.h"
#include "Renderer.h"
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
			Rect* outRect;

		public:

			RectComponent(float x, float y, float width, float height, Color c);
			RectComponent(Color c);
			~RectComponent();

		      virtual Rect* GetRects(int& size) const { 
				       size = 1;
				 return outRect; }
			virtual void Update() override;
			virtual void  Init() override;

		};
	}
}