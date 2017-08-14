#pragma once
#include "RectComponent.h"
#include "freetype-gl.h" 
namespace Engine {
	namespace Graphics {

		

		class TextComponent : public RectComponent
		{
		
			const char *  text;
			texture_font_t * font;
			int str_length;
		public:

			TextComponent(float x, float y, const char * text, const char * fontType ,Color c);
		
			void Update() override;
		
			void  Init() override;
			Rect* GetRects(int& size) const {
				size = str_length;
				return outRect;
			} 

		};
	}
}