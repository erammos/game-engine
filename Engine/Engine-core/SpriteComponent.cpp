
#include "SpriteComponent.h"
#include "TextureManager.h"

using namespace Engine;
using namespace Graphics;


void Engine::Graphics::SpriteComponent::Init()
{

	Vec4f percetages = TextureManager::Inst()->textures[imageName];


	double Ax = (percetages.x ) / (double)TextureManager::Inst()->atlas_width;
	double Ay = (percetages.y ) / (double)TextureManager::Inst()->atlas_height;

	double Bx = (percetages.x + width) / (double)TextureManager::Inst()->atlas_width;
	double By = (percetages.y + height) / (double)TextureManager::Inst()->atlas_height;


    rect.bl.tex = Vec4f(Ax, Ay, 0);
    rect.tl.tex = Vec4f(Ax, By, 0);
	rect.tr.tex = Vec4f(Bx, By, 0);
	rect.br.tex = Vec4f(Bx, Ay, 0);
	
	RectComponent::Init();
}


SpriteComponent::SpriteComponent(const char * imageName) : RectComponent(Color(0,0,0,1))
{
	this->x = 0;
	this->y = 0;
	this->imageName = imageName;
	TextureManager::Inst()->AddTexture(imageName);
	width = TextureManager::Inst()->textures[imageName].z;
	height = TextureManager::Inst()->textures[imageName].w;

}

SpriteComponent::~SpriteComponent()
{
	TextureManager::Inst()->UnloadTexture(rect.br.tex.z);
}
void SpriteComponent::Update()
{
		
	RectComponent::Update();

}


