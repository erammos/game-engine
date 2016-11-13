#pragma once
#include "Vec3.h"
template<typename T>
class Matrix44
{
public:
	Matrix44(T t[4][4]) {
	
		for (uint8_t i = 0; i < 4; ++i) {
			for (uint8_t j = 0; j < 4; ++j) {
				m[i][j] = t[i][j];
			}
		}
	}

	std::string toString()
	{
		string s = "";
		
		for (uint8_t i = 0; i < 4; ++i) {
			for (uint8_t j = 0; j < 4; ++j) {
				s = s + to_string(m[i][j]) + " ";
			}
			s = s + "\n";
		}
		return s;
	}
	Matrix44() {}
	const T* operator [] (int i) const { return m[i]; }
	T* operator [] (int i) { return m[i]; }
	 T m[4][4] = { { 1,0,0,0 },{ 0,1,0,0 },{ 0,0,1,0 },{ 0,0,0,1 } };
	Matrix44 operator * (const Matrix44& rhs) const
	{
		Matrix44 mult;
		for (uint8_t i = 0; i < 4; ++i) {
			for (uint8_t j = 0; j < 4; ++j) {
				mult[i][j] = m[i][0] * rhs[0][j] +
					m[i][1] * rhs[1][j] +
					m[i][2] * rhs[2][j] +
					m[i][3] * rhs[3][j];
			}
		}

		return mult;
	}

	Matrix44 rotateX(T angle)
	{
		T temp[4][4] = {
		 { 1,0,0,0 }
		,{ 0,cos(angle),-sin(angle),0 }
		,{ 0,sin(angle),cos(angle),0 },
		{ 0, 0, 0,1 } };

		return Matrix44(temp);
	}
	Matrix44 rotateY(T angle)
	{
		T temp[4][4] = {
			{ cos(angle),0,sin(angle),0 }
			,{ 0,1,0,0 }
			,{ -sin(angle),0,cos(angle),0 },
			{ 0, 0, 0,1 } };

		return Matrix44(temp);
	}
	Matrix44 rotateZ(T angle)
	{
		T temp[4][4] = {
			{ cos(angle),-sin(angle),0,0 }
			,{ sin(angle),cos(angle),0,0 }
			,{ 0,0,1,0 },
			{ 0, 0, 0,1 } };

		return Matrix44(temp).transpose();
	}

	Matrix44 translation(T tx,T ty, T tz)
	{
		T temp[4][4] = {
			{ 1,0,0,0 }
			,{ 0,1,0,0 }
			,{ 0,0,1,0 },
			{ tx, ty, tz,1 } };

		return Matrix44(temp);
	}
	Vec3<T> transformPoint(const Vec3<T> &src) const
	{
		Vec3<T> dst;
		dst.x = src.x * m[0][0] + src.y * m[1][0] + src.z * m[2][0] + m[3][0];
		dst.y = src.x * m[0][1] + src.y * m[1][1] + src.z * m[2][1] + m[3][1];
		dst.z = src.x * m[0][2] + src.y * m[1][2] + src.z * m[2][2] + m[3][2];
		T w = src.x * m[0][3] + src.y * m[1][3] + src.z * m[2][3] + m[3][3];
		if (w != 1 && w != 0) {
			dst.x = dst.x / w;
			dst.y = dst.y / w;
			dst.z = dst.z / w;
		}
		return dst;
	}
	Vec3<T> transformVector(const Vec3<T> &src) const
	{
		Vec3 dst;
		dst.x = src.x * m[0][0] + src.y * m[1][0] + src.z * m[2][0];
		dst.y = src.x * m[0][1] + src.y * m[1][1] + src.z * m[2][1];
		dst.z = src.x * m[0][2] + src.y * m[1][2] + src.z * m[2][2];
		return dst;
	}
	Matrix44 transpose() const
	{
		Matrix44 transpMat;
		for (uint8_t i = 0; i < 4; ++i) {
			for (uint8_t j = 0; j < 4; ++j) {
				transpMat[i][j] = m[j][i];
			}
		}

		return transpMat;
	}

	Matrix44 inverse()
	{
		int i, j, k;
		Matrix44 s;
		Matrix44 t(*this);

		// Forward elimination
		for (i = 0; i < 3; i++) {
			int pivot = i;

			T pivotsize = t[i][i];

			if (pivotsize < 0)
				pivotsize = -pivotsize;

			for (j = i + 1; j < 4; j++) {
				T tmp = t[j][i];

				if (tmp < 0)
					tmp = -tmp;

				if (tmp > pivotsize) {
					pivot = j;
					pivotsize = tmp;
				}
			}

			if (pivotsize == 0) {
				// Cannot invert singular matrix
				return Matrix44();
			}

			if (pivot != i) {
				for (j = 0; j < 4; j++) {
					T tmp;

					tmp = t[i][j];
					t[i][j] = t[pivot][j];
					t[pivot][j] = tmp;

					tmp = s[i][j];
					s[i][j] = s[pivot][j];
					s[pivot][j] = tmp;
				}
			}

			for (j = i + 1; j < 4; j++) {
				T f = t[j][i] / t[i][i];

				for (k = 0; k < 4; k++) {
					t[j][k] -= f * t[i][k];
					s[j][k] -= f * s[i][k];
				}
			}
		}

		// Backward substitution
		for (i = 3; i >= 0; --i) {
			T f;

			if ((f = t[i][i]) == 0) {
				// Cannot invert singular matrix
				return Matrix44();
			}

			for (j = 0; j < 4; j++) {
				t[i][j] /= f;
				s[i][j] /= f;
			}

			for (j = 0; j < i; j++) {
				f = t[j][i];

				for (k = 0; k < 4; k++) {
					t[j][k] -= f * t[i][k];
					s[j][k] -= f * s[i][k];
				}
			}
		}

		return s;
	}



};
