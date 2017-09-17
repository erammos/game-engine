#pragma once
#include "GameObject.h"
#include "Renderer.h"
#include "Shader.h"
#include "GraphicComponent.h"

namespace Engine {
	namespace Graphics
	{
		class Layer
		{
		protected:
			Renderer * renderer;
			Shader *   layerShader;
			std::vector<GameObject *> objects;
			Mat4f projectionTransform;
		public:
			Layer( Shader * shader, Renderer * renderer): layerShader(shader), renderer(renderer)
			{

				layerShader = shader;
				this->renderer = renderer;
			}
			virtual ~Layer()
			{
				delete renderer;
				delete layerShader;
				for (int i = 0; i < objects.size(); i++) delete objects[i];
			}
			virtual void add(GameObject *gameObject)
			{
				objects.push_back(gameObject);
			}

			void render()
			{
				//layerShader->enable();
				renderer->Begin();
				for (int i = 0; i < objects.size(); i++)
				{
					objects[i]->Draw(renderer);
				}
				renderer->End();
			}

		};
	}
}