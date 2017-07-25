#pragma once
#include "GraphicsComponent.h"
#include "SpriteRenderer.h"
#include "Texture.h"
namespace Engine {
	namespace Graphics {

		struct Rect
		{
			VertexData bl;
			VertexData tl;
			VertexData tr;
			VertexData br;
		};

		class SpriteComponent : public GraphicsComponent
		{
			int x;
			int y;
			int width = 0;
			int height = 0;
			const char * imageName;
			Rect rect;
			Rect outRect;
			
		public:
		
			SpriteComponent(float x, float y, float width, float height, Color c);
			SpriteComponent(Texture* texture );
			SpriteComponent(const char * imageName);	
			~SpriteComponent();
			
			inline const Rect& GetRect() const { return outRect; }
			void Update() override;
			void  Draw(Renderer * renderer) override;
			void  Init() override;

		};
	}
}