#include "GameObject.h"
#include "GraphicsComponent.h"
#include <iostream>
Engine::Graphics::GameObject::GameObject()
{
	parent = NULL;
}

Engine::Graphics::GameObject::~GameObject()
{
	delete graphics;
	for (int i = 0; i < childs.size(); i++)
	{
		delete childs[i];
	}
}
void Engine::Graphics::GameObject::Init()
{
	
	if (graphics)graphics->Init();
	for (int i = 0; i < childs.size(); i++)
	{
		childs[i]->Init();
	}

	
}

void Engine::Graphics::GameObject::Draw(Renderer * renderer)
{
	m_dirty = m_dirty |= ((parent) ? parent->isDirty() : false);

	if (m_dirty)
	{
		//std::cout << "Rendering" << std::endl;
		WorldTransform = (parent) ? parent->WorldTransform * LocalTransform : LocalTransform;
		if (graphics)graphics->Update();
	}

	if (graphics)graphics->Draw(renderer);

	for (int i = 0; i < childs.size(); i++)
	{
		childs[i]->Draw(renderer);
	}

	if (m_dirty) m_dirty = false;
}

void Engine::Graphics::GameObject::Add(GameObject * gameobject)
{

	gameobject->parent = this;
	childs.push_back(gameobject);
}

void Engine::Graphics::GameObject::AddGraphicComponent(GraphicsComponent * component)
{
	{
		component->SetOwner(this);
		graphics = component;
	}
}

void Engine::Graphics::GameObject::SetTransform(Engine::Graphics::Mat4f transform)
{
	LocalTransform = transform;
	m_dirty = true;
}
