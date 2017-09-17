#include "RectComponent.h"
using namespace Engine;
using namespace Graphics;

RectComponent::RectComponent(float x, float y, float width, float height, Color c):GraphicComponent(c)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;

	rect.bl.tex = Vec4f(-1, -1, -1);
	rect.tl.tex = Vec4f(-1, -1, -1);
	rect.tr.tex = Vec4f(-1, -1, -1);
	rect.br.tex = Vec4f(-1, -1, -1);

	rect.bl.color = color;
	rect.tl.color = color;
	rect.tr.color = color;
	rect.br.color = color;
}

RectComponent::RectComponent(Color c):GraphicComponent(c)
{



}

RectComponent::~RectComponent()
{
	outRect.clear();
}
void RectComponent::Init()
{
	rect.bl.vertex = Vec4f(x, y, 0);
	rect.tl.vertex = Vec4f(x, y + height, 0);
	rect.tr.vertex = Vec4f(x + width, y + height, 0);
	rect.br.vertex = Vec4f(x + width, y, 0);

	outRect.clear();
	outRect.push_back(rect);

	
	
}
void RectComponent::Update()
{
	
	outRect[0].bl.vertex = Owner->WorldTransform * rect.bl.vertex;
	outRect[0].tl.vertex = Owner->WorldTransform * rect.tl.vertex;
	outRect[0].tr.vertex = Owner->WorldTransform * rect.tr.vertex;
	outRect[0].br.vertex = Owner->WorldTransform * rect.br.vertex;

}
