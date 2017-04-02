
#include "SpriteComponent.h"
#include "TextureManager.h"

using namespace Engine;
using namespace Graphics;

void Engine::Graphics::SpriteComponent::init(float x, float y, float width, float height)
{
	rect.bl.vertex = Vec3f(x, y, 1);
	rect.tl.vertex = Vec3f(x, y + width, 1);
	rect.tr.vertex = Vec3f(x + width, y + height, 1);
	rect.br.vertex = Vec3f(x + width, y, 1);

	rect.bl.uv = Vec2f(0, 0);
	rect.tl.uv = Vec2f(0, 1);
	rect.tr.uv = Vec2f(1, 1);
	rect.br.uv = Vec2f(1, 0);

	memcpy(&outRect.bl, &rect.bl, sizeof(VertexData));
	memcpy(&outRect.tl, &rect.tl, sizeof(VertexData));
	memcpy(&outRect.tr, &rect.tr, sizeof(VertexData));
	memcpy(&outRect.br, &rect.br, sizeof(VertexData));
}

SpriteComponent::SpriteComponent(float x ,float y, float width, float height, Color c) : GraphicsComponent(c)
{
	
	init(x, y, width, height);
}

SpriteComponent::SpriteComponent(const char * imageName) : GraphicsComponent(Color(0,0,0,1))
{
	int width(0);
	int height(0);
	int id=TextureManager::Inst()->LoadTexture(imageName, width, height);

	rect.bl.tid = id;
	rect.tl.tid = id;
	rect.tr.tid = id;
	rect.br.tid = id;

	init(0, 0, width, height);


}

SpriteComponent::~SpriteComponent()
{
	TextureManager::Inst()->UnloadTexture(rect.bl.tid);
}
void SpriteComponent::Update()
{
		


		outRect.bl.vertex = Owner->WorldTransform * rect.bl.vertex;
		outRect.tl.vertex = Owner->WorldTransform * rect.tl.vertex;
		outRect.tr.vertex = Owner->WorldTransform * rect.tr.vertex;
		outRect.br.vertex = Owner->WorldTransform * rect.br.vertex;

}
void SpriteComponent::Draw(Renderer * renderer)
{
	SpriteRenderer * spriteRenderer = (SpriteRenderer *)renderer;
	spriteRenderer->Draw(this);
}


