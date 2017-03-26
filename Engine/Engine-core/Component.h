#pragma once
#include "GameObject.h"
namespace Engine {
	namespace Graphics {
		
		class Component
		{
		protected:	
			GameObject * Owner = NULL;
			Component(GameObject * owner):Owner(owner)  { }
			Component(){}
		public:
			virtual void Update() = 0;
			inline const GameObject * GetOwner() const { return Owner; }
			void SetOwner(GameObject * object)
			{
				Owner = object;
			}
			
	
		};
	}

}