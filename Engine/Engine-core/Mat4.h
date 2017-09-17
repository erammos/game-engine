#pragma once
#include "Vec4.h"

namespace Engine {
	namespace Math {
		template<typename T>
		class Mat4
		{

		public: 
			
			union
			{
				T values[16];
				Vec4<T> columns[4];
			};
		
			

				Mat4()
				{
					memset(values, 0, sizeof(values));
				}


				Mat4 operator * (const Mat4& rhs) const
				{
					Mat4 m;
					for (int i = 0; i < 4; ++i) {
						for (int j = 0; j < 4; ++j) {
							m.values[i + j * 4] = rhs.values[j * 4] * values[i] +
								+rhs.values[1 + j * 4] * values[i + 4]
								+ rhs.values[2 + j * 4] * values[i + 8]
								+ rhs.values[3 + j * 4] * values[i + 12];
						}

						
					}

					return m;
				}
				Vec4<T> operator *(const Vec4<T> &src) const
				{
					Vec4<T> dst;
					dst.x = src.x * values[0] + src.y * values[4] + src.z *  values[8] + values[12];
					dst.y = src.x * values[1] + src.y * values[5] + src.z * values[9] + values[13];
					dst.z = src.x * values[2] + src.y * values[6] + src.z *  values[10] + values[14];
					dst.w = src.x * values[3] + src.y * values[7] + src.z *  values[11] + values[15];
					return dst;
				}


				static Mat4 identity()
				{
					Mat4 m;

					m.values[0] = 1;
					m.values[5] = 1;
					m.values[10] = 1;
					m.values[15] = 1;

					return m;
				}
				static Mat4 ortho(T r_min, T r_max, T u_min, T u_max, T d_min, T d_max)
				{
					Mat4 m = identity();

					m.values[0] = 2.0f / (r_max - r_min);
					m.values[1] = 0.0f;
					m.values[2] = 0.0f;
					m.values[3] = 0.0f;

					m.values[4] = 0.0f;
					m.values[5] = 2.0f / (u_max - u_min);
					m.values[6] = 0.0f;
					m.values[7] = 0.0f;

					m.values[8] = 0;
					m.values[9] = 0;
					m.values[10] = 1/ (d_max - d_min);
					m.values[11] = 0;

					m.values[12] = -(r_max + r_min) / (r_max - r_min);
					m.values[13] = -(u_max + u_min) / (u_max - u_min);
					m.values[14] = -(d_min) / (d_max - d_min);
					m.values[15] = 1.0f;
					return m;
				}
				/**
				const float cotangent = 1 / tanf(3.14159f / 6.0f);

				return Matrix4(cotangent / aspectRatio, 0.0f, 0.0f, 0.0f,
					0.0f, cotangent, 0.0f, 0.0f,
					0.0f, 0.0f, -50.0f / (50.0f - 1.0f), (-50.0f * 1.0f) / (50.0f - 1.0f),
					0.0f, 0.0f, -1.0f, 0.0f);
				*/
				/*Matrix44<double> perspTransform(double fov, double aspect, double d_min, double d_max)
				{
					double u_max = d_min*tan(fov);
					double r_max = aspect*u_max;
					double u_min = -u_max;
					double r_min = -r_max;

					double InvRdiff = 1.0 / (r_max - r_min);
					double InvUdiff = 1.0 / (u_max - u_min);
					double InvDiff = 1.0 / (d_max - d_min);

					double m[4][4]{
						{ 2.*d_min*InvRdiff,0,0,0 },
						{ 0,2.*d_min*InvUdiff,0,0 },
						{ -(r_max + r_min)*InvRdiff,-(u_max + u_min)*InvUdiff,d_max*InvDiff,1 },
						{ 0,0,-d_max*d_min*InvDiff,0 } };

					Matrix44 <double> vt(m);
					return vt;

				}*/
				static Mat4 persp(double fov, double aspect, double d_min, double d_max)
				{

					Mat4 m = identity();

					double u_max = d_min*tan(fov * 0.5f);
					double r_max = aspect*u_max;
					double u_min = -u_max;
					double r_min = -r_max;

					double InvRdiff = 1.0 / (r_max - r_min);
					double InvUdiff = 1.0 / (u_max - u_min);
					double InvDiff = 1.0 / (d_max - d_min);


					m.values[0] = 2.*d_min*InvRdiff;
					m.values[1] = 0.0f;
					m.values[2] = 0.0f;
					m.values[3] = 0.0f;

					m.values[4] = 0.0f;
					m.values[5] = 2.*d_min*InvUdiff;
					m.values[6] = 0.0f;
					m.values[7] = 0.0f;

					m.values[8] = (r_max + r_min)*InvRdiff;
					m.values[9] = (u_max + u_min)*InvUdiff;
					m.values[10] = -d_max*InvDiff;
					m.values[11] = -1;

					m.values[12] = 0.0f;
					m.values[13] = 0.0f;
					m.values[14] = -d_max*d_min*InvDiff;
					m.values[15] = 0.0f;

					return m;

				}
				

				static Mat4 translation(const Vec4<T>& t)
				{
					return translation(t.x, t.y, t.z);
				}
				static Mat4 translation(T tx, T ty, T tz)
				{
					Mat4 m = identity();
					m.values[12] = tx;
					m.values[13] = ty;
					m.values[14] = tz;

					return m;
				}
				/*static Mat4 rotation(T angle, const Vec3<T>& axis)
				{
					Mat4 m = identity();

					float r = TO_RADIANS(angle);
					float c = cos(r);
					float s = sin(r);
					float t = 1.0f - c;

					float x = axis.x;
					float y = axis.y;
					float z = axis.z;

					m.values[0] = t * x * x  + c;
					m.values[1] = t * x * y + s * z;
					m.values[2] = t * x * z - s * y;

					m.values[3] = t * x * y - s * z;
					m.values[4] = t * y * y  + c;
					m.values[5] = t * y * z + s * x;

					m.values[6] = t * x * z - s * y;
					m.values[7] = t * y * z - s * x;
					m.values[8] = t * z * z  + c;

					return m;

				}
				*/
				static Mat4 rotateZ(T angle)
				{
					
					Mat4 m = identity();
					m.values[0] = cos(angle);
					m.values[1] = -sin(angle);
					m.values[2] = 0.0f;
					m.values[3] = 0.0f;

					m.values[4] = sin(angle);
					m.values[5] = cos(angle);
					m.values[6] = 0.0f;
					m.values[7] = 0.0f;

					

					return m;
				}

				static Mat4 rotateY(T angle)
				{
					

					Mat4 m = identity();
					m.values[0] = cos(angle);
					m.values[1] = 0.0;
					m.values[2] = sin(angle);
					m.values[3] = 0.0f;

					m.values[8] = -sin(angle);
					m.values[9] = 0.0;
					m.values[10] = cos(angle);
					m.values[11] = 0.0f;

					return m;
				}

				static Mat4 scale(T sx, T sy, T sz)
				{
					Mat4 m = identity();

					m.values[0] = sx;
					m.values[5] = sy;
					m.values[10] = sz;

					return m;
				}
		};


#define Mat4f Mat4<float>
#define Mat4d Mat4<double>
}
}