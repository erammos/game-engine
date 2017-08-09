#include "GraphicComponent.h"
#include "Renderer.h"
void Engine::Graphics::GraphicComponent::Draw(Renderer * renderer)
{
	renderer->Draw(this);
}
