#include "TextComponent.h"
#include "TextureManager.h"
using namespace Engine;
using namespace Graphics;

TextComponent::TextComponent(float x, float y, const char * text, const char * fontType ,Color c) :RectComponent(c)
{
	this->x = x;
	this->y = y;
	this->text = text;
	this->font = TextureManager::Inst()->LoadFont(fontType);
}
void TextComponent::Update()
{
	size_t i;
	float r = color.r, g = color.g, b = color.b, a = color.a;
	int originx = x;
	int originy = y;
	
	outRect = new Rect[str_length];
	Mat4f pre = Mat4f::translation(-width * 0.5f, - height * 0.5f, 0);
	Mat4f post = Mat4f::translation(width * 0.5f, height * 0.5f, 0);
	//outRect->bl.vertex = Owner->WorldTransform * rect.bl.vertex;
	//outRect->tl.vertex = Owner->WorldTransform * rect.tl.vertex;
	//outRect->tr.vertex = Owner->WorldTransform * rect.tr.vertex;
	//outRect->br.vertex = Owner->WorldTransform * rect.br.vertex;

	for (i = 0; i < str_length; ++i)
	{
		texture_glyph_t *glyph = texture_font_get_glyph(font, text + i);
		if (glyph != NULL)
		{
			float kerning = 0.0f;
			if (i > 0)
			{
				kerning = texture_glyph_get_kerning(glyph, text + i - 1);
			}
			originx += kerning;

			float x0 = (originx + glyph->offset_x);
			float y0 = (originy + glyph->offset_y);
			float x1 = (x0 + glyph->width);
			float y1 = (y0 - glyph->height);

			float s0 = glyph->s0;
			float t0 = glyph->t0;
			float s1 = glyph->s1;
			float t1 = glyph->t1;

			originx += glyph->advance_x;

		
			outRect[i].bl.vertex = Vec3f(x0, y0, 0);
			outRect[i].bl.color = Color(r, g, b, a);
			outRect[i].bl.tex = Vec3f(s0, t0, 1);

			
			outRect[i].tl.vertex = Vec3f(x0, y1, 0);
			outRect[i].tl.color = Color(r, g, b, a);
			outRect[i].tl.tex = Vec3f(s0, t1, 1);

		
			outRect[i].tr.vertex = Vec3f(x1, y1, 0);
			outRect[i].tr.color = Color(r, g, b, a);
			outRect[i].tr.tex = Vec3f(s1, t1, 1);

		
			outRect[i].br.vertex = Vec3f(x1, y0, 0);
			outRect[i].br.color = Color(r, g, b, a);
			outRect[i].br.tex = Vec3f(s1, t0, 1);
		

			outRect[i].bl.vertex =  Owner->WorldTransform * outRect[i].bl.vertex;
			outRect[i].tl.vertex = Owner->WorldTransform * outRect[i].tl.vertex;
			outRect[i].tr.vertex = Owner->WorldTransform * outRect[i].tr.vertex;
			outRect[i].br.vertex = Owner->WorldTransform * outRect[i].br.vertex;
		}


	}

	

}

void TextComponent::Init()
{
	str_length = strlen(text);
	for (int i = 0; i < str_length; ++i)
	{
		texture_glyph_t *glyph = texture_font_get_glyph(font, text + i);
		if (glyph != NULL)
		{
			float kerning = 0.0f;
			if (i > 0)
			{
				kerning = texture_glyph_get_kerning(glyph, text + i - 1);
			}
			width += glyph->advance_x + kerning;
			height = max(height, glyph->height);
		}
	}
}