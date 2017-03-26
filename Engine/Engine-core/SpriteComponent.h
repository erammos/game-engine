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
			int texture_id;
		};

		class SpriteComponent : public GraphicsComponent
		{
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

		};
	}
}