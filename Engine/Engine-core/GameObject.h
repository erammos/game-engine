#pragma once
#include <vector>
#include "Math.h"


namespace Engine {
	namespace Graphics
	{
		class Renderer;
		class GraphicsComponent;
		using namespace Math;

		class GameObject
		{
		protected:
		   GameObject * parent;
		   std::vector<GameObject *> childs;
		   GraphicsComponent * graphics = NULL;
		   bool m_dirty = true;

	    public:
		   Mat4f WorldTransform = Mat4f::identity();
		   Mat4f LocalTransform = Mat4f::identity();
		public:
			GameObject();
			~GameObject();
			void Draw(Renderer * renderer);
			void Init();
			void Add(GameObject * gameobject);
			void AddGraphicComponent(GraphicsComponent * component);
			void SetTransform(Mat4f transform);
			inline const bool isDirty() const { return m_dirty; }
		};



	}
}
