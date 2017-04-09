
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



	memcpy(&outRect.bl, &rect.bl, sizeof(VertexData));
	memcpy(&outRect.tl, &rect.tl, sizeof(VertexData));
	memcpy(&outRect.tr, &rect.tr, sizeof(VertexData));
	memcpy(&outRect.br, &rect.br, sizeof(VertexData));
}

SpriteComponent::SpriteComponent(float x ,float y, float width, float height, Color c) : GraphicsComponent(c)
{
	
	init(x, y, width, height);
}

SpriteComponent::SpriteComponent(const char * imageName) : GraphicsComponent(Color(0,0,0,0))
{
	int width(0);
	int height(0);
	int id=TextureManager::Inst()->LoadTexture(imageName, width, height);

	rect.bl.tex = Vec3f(0, 0, id);
	rect.tl.tex = Vec3f(0, 1, id);
	rect.tr.tex = Vec3f(1, 1, id);
	rect.br.tex = Vec3f(1, 0, id);


	init(0, 0, width, height);


}

SpriteComponent::~SpriteComponent()
{
	TextureManager::Inst()->UnloadTexture(rect.br.tex.z);
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


