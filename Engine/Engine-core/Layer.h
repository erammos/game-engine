#pragma once
#include "GameObject.h"
#include "Renderer.h"
#include "Shader.h"
#include "GraphicsComponent.h"

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
				shader->enable();
				glUniformMatrix4fv(glGetUniformLocation(shader->program_id, "proj_matrix"), 1, GL_FALSE, Mat4f::ortho(0.0, 80.0f, 0.0f, 60.0f, 1.0f, -1.0f).values);
				shader->disable();
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
				layerShader->enable();
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