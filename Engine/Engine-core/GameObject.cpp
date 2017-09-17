#include "GameObject.h"
#include "GraphicComponent.h"
#include <iostream>
Engine::Graphics::GameObject::GameObject()
{
	parent = NULL;
}

Engine::Graphics::GameObject::~GameObject()
{
	
	for (int i = 0; i < childs.size(); i++)
	{
		delete childs[i];
	}
}
void Engine::Graphics::GameObject::Init()
{
	
	for (auto g : graphics) g->Init();
	for (int i = 0; i < childs.size(); i++)
	{
		childs[i]->Init();
	}

	
}

void Engine::Graphics::GameObject::Update()
{
	
	for (auto b : behaviours) b->Update();

	for (int i = 0; i < childs.size(); i++)
	{
		childs[i]->Update();
	}

}

void Engine::Graphics::GameObject::Draw(Renderer * renderer)
{
	m_dirty = m_dirty |= ((parent) ? parent->isDirty() : false);

	if (m_dirty)
	{
		//std::cout << "Rendering" << std::endl;
		WorldTransform = (parent) ? parent->WorldTransform * LocalTransform : LocalTransform;
			
			for (auto  g : graphics) g->Update();
			
				
			
	}

	for (auto  g : graphics) g->Draw(renderer);

	for (int i = 0; i < childs.size(); i++)
	{
		childs[i]->Draw(renderer);
	}

	if (m_dirty) m_dirty = false;
}

void Engine::Graphics::GameObject::Invalidate()
{
	m_dirty = true;
}

std::vector<Engine::Graphics::GameObject*> Engine::Graphics::GameObject::getChilds()
{
	return childs;
}

void Engine::Graphics::GameObject::Add(GameObject * gameobject)
{

	gameobject->parent = this;
	childs.push_back(gameobject);
}

void Engine::Graphics::GameObject::AddGraphicComponent(GraphicComponent * component)
{
	{
		component->SetOwner(this);
		graphics.push_back(component);
		
	}
}

void Engine::Graphics::GameObject::SetTransform(Engine::Graphics::Mat4f transform)
{
	LocalTransform = transform;
	m_dirty = true;
}
