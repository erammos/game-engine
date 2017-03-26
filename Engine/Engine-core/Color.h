#pragma once


namespace Engine {
	namespace Math {
	
		class Color
		{

		public:
			float r, g, b, a;

			
			Color(float xx, float yy, float zz) : r(xx), g(yy), b(zz), a(1) {}
			Color(float xx, float yy, float zz , float ww) : r(xx), g(yy), b(zz), a(ww) {}
			Color() : r(0), g(0), b(0), a(1) {}
			Color operator + (const Color &v) const
			{
				return Color(r + v.r, g + v.g, b + v.b);
			}
			Color operator - (const Color &v) const
			{
				return Color(r - v.r, g - v.g, b - v.b);
			}
			Color operator * (Color &v) const
			{
				return Color(r * v.r, g * v.g, b* v.b);
			}
			
		
			/*friend std::ostream& operator << (std::ostream& stream, const Color& color)
			{
				stream << "color:" << color.r << "," << color.g << "," << color.b;
				return stream;
			}*/
		};


	}
}

