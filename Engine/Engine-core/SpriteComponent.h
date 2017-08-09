#pragma once
#include "RectComponent.h"

namespace Engine {
	namespace Graphics {

	
		class SpriteComponent : public RectComponent
		{		
			const char * imageName;
			
		public:
		
			SpriteComponent(const char * imageName);	
			~SpriteComponent();
			
			void Update() override;
			void  Init() override;

		};
	}
}