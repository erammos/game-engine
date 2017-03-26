#pragma once

namespace Engine {
	namespace Math {
		template<typename T>
		class Vec3
		{

		public:
			T x , y , z , w;
	
			Vec3() : x(T(0)), y(T(0)), z(T(0)), w(T(1))  {} 
			Vec3(T xx, T yy, T zz) : x(xx), y(yy), z(zz), w(1) {}

			Vec3<T> operator + (const Vec3<T> &v) const
			{
				return Vec3<T>(x + v.x, y + v.y, z + v.z);
			}
			Vec3<T> operator - (const Vec3<T> &v) const
			{
				return Vec3<T>(x - v.x, y - v.y, z - v.z);
			}
			Vec3<T> operator * (const T &r) const
			{
				return Vec3<T>(x * r, y * r, z * r);
			}
			Vec3<T>& normalize()
			{
				T len = length();
				if (len > 0) {
					T invLen = 1 / len;
					x *= invLen, y *= invLen, z *= invLen;
				}

				return *this;
			}
			T dot(const Vec3<T> &v) const
			{
				return x * v.x + y * v.y + z * v.z;
			}
			Vec3<T> cross(const Vec3<T> &v) const
			{
				return Vec3<T>(
					y * v.z - z * v.y,
					z * v.x - x * v.z,
					x * v.y - y * v.x);
			}
/*			friend std::ostream& operator << (std::ostream& stream, const Vec3<T>& vector)
			{
				stream << "vec3:" << vector.x << "," << vector.y << "," << vector.z;
				return stream;
			}*/
		};

#define Vec3f Vec3<float>
#define Vec3d Vec3<double>
	}
}
