#include "RectComponent.h"
using namespace Engine;
using namespace Graphics;

RectComponent::RectComponent(float x, float y, float width, float height, Color c):GraphicComponent(c)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height - height;
}

RectComponent::RectComponent(Color c):GraphicComponent(c)
{
}

RectComponent::~RectComponent()
{
	delete outRect;
}
void RectComponent::Init()
{
	rect.bl.vertex = Vec3f(x, y, 1);
	rect.tl.vertex = Vec3f(x, y + height, 1);
	rect.tr.vertex = Vec3f(x + width, y + height, 1);
	rect.br.vertex = Vec3f(x + width, y, 1);

	outRect = new Rect();
	memcpy(&outRect->bl, &rect.bl, sizeof(VertexData));
	memcpy(&outRect->tl, &rect.tl, sizeof(VertexData));
	memcpy(&outRect->tr, &rect.tr, sizeof(VertexData));
	memcpy(&outRect->br, &rect.br, sizeof(VertexData));
	
}
void RectComponent::Update()
{

	outRect->bl.vertex = Owner->WorldTransform * rect.bl.vertex;
	outRect->tl.vertex = Owner->WorldTransform * rect.tl.vertex;
	outRect->tr.vertex = Owner->WorldTransform * rect.tr.vertex;
	outRect->br.vertex = Owner->WorldTransform * rect.br.vertex;

}
