#pragma once
#include "Component.h"
namespace Engine {
	namespace Graphics {
		using namespace Math;
		 class GraphicsComponent: public Component
		{
		protected:	
			Color color;
		
		    GraphicsComponent(Color c) : color(c) { }
		
			virtual ~GraphicsComponent()
			{
				
			}
		public:	
			
			virtual void Draw(Renderer * renderer) =0;
			inline const Color& GetColor() const { return color; }
			
		};
	}

}