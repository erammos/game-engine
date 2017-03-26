#pragma once
namespace Engine {
	namespace Math{
	template<typename T>
	class Vec2
	{
	
	   public:
		    T x, y;

			Vec2(T xx, T yy) : x(xx), y(yy){}
			Vec2() : x(0), y(0) {}
			Vec2<T> operator + (const Vec2<T> &v) 
			{
				return Vec2<T>(x+v.x,y+v.y);
			}
			Vec2<T> operator - (const Vec2<T> &v) 
			{			
				return Vec2<T>(x - v.x, y - v.y);
			}
			Vec2<T> operator * (const Vec2<T> &r)
			{
				return Vec2<T>(x * v.x, y * v.y);
			}
			bool operator == (const Vec2<T>&r)
			{
				return x = r.x && y == r.y;
			}
		/*	friend std::ostream& operator << (std::ostream& stream, const Vec2<T>& vector)
			{
				stream << "vec2:" << vector.x << "," << vector.y;
				return stream;
			}*/
	};

#define Vec2f Vec2<float>
#define Vec2d Vec2<double>
}
}
