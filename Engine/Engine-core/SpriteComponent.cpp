
#include "SpriteComponent.h"
#include "TextureManager.h"

using namespace Engine;
using namespace Graphics;


void Engine::Graphics::SpriteComponent::Init()
{

	double offset_x = TextureManager::Inst()->textures[imageName];
	double perc_height = height / (double)TextureManager::Inst()->atlas_height;

	double perc_width = width / (double) TextureManager::Inst()->atlas_width;

    rect.bl.tex = Vec3f(offset_x, 0, 0);
	rect.tl.tex = Vec3f(offset_x, 0 + perc_height, 0);
	rect.tr.tex = Vec3f(offset_x + perc_width, 0 + perc_height, 0);
	rect.br.tex = Vec3f(offset_x + perc_width, 0, 0);
	

	rect.bl.vertex = Vec3f(x, y, 1);
	rect.tl.vertex = Vec3f(x, y + height, 1);
	rect.tr.vertex = Vec3f(x + width, y + height, 1);
	rect.br.vertex = Vec3f(x + width, y, 1);



	memcpy(&outRect.bl, &rect.bl, sizeof(VertexData));
	memcpy(&outRect.tl, &rect.tl, sizeof(VertexData));
	memcpy(&outRect.tr, &rect.tr, sizeof(VertexData));
	memcpy(&outRect.br, &rect.br, sizeof(VertexData));
}
SpriteComponent::SpriteComponent(float x ,float y, float width, float height, Color c) : GraphicsComponent(c)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height - height;
	
}

SpriteComponent::SpriteComponent(const char * imageName) : GraphicsComponent(Color(0,0,0,1))
{
	this->x = 0;
	this->y = 0;
	this->imageName = imageName;
	TextureManager::Inst()->AddTexture(imageName, width, height);

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


