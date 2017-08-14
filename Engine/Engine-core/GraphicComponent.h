#pragma once
#include "Component.h"
namespace Engine {
	namespace Graphics {
		using namespace Math;

		enum GraphicComponentType { };
		 class GraphicComponent: public Component
		{
		protected:	
			Color color;
		
		    GraphicComponent(Color c) : color(c) { }
		
		
		public:	
			
			virtual void Draw(Renderer * renderer);
			virtual void Init() = 0;
			inline const Color& GetColor() const { return color; }
			virtual ~GraphicComponent()
			{

			}
		};
	}

}