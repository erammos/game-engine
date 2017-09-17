#pragma once
#include <vector>
#include "Math.h"


namespace Engine {
	namespace Graphics
	{
		class Renderer;
		class GraphicComponent;
		class Component;
		using namespace Math;

		class GameObject
		{
		protected:
		   GameObject * parent;
		   std::vector<GameObject *> childs;
		   std::vector<GraphicComponent *> graphics;
		   std::vector<Component *> behaviours;
		   bool m_dirty = true;

	    public:
		   Mat4f WorldTransform = Mat4f::identity();
		   Mat4f LocalTransform = Mat4f::identity();
		public:
			GameObject();
			~GameObject();
			void Draw(Renderer * renderer);
			void Invalidate();
			std::vector<GameObject *> getChilds();
			void Init();
			void Update();
			void Add(GameObject * gameobject);
			void AddGraphicComponent(GraphicComponent * component);
			void SetTransform(Mat4f transform);
			inline const bool isDirty() const { return m_dirty; }
		
		};



	}
}
