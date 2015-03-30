#ifndef VEC_3
#define VEC_3
//#define _USE_MATH_DEFINES

#include <iostream>
#include <math.h>
//#include <cmath>
#include <assert.h>

namespace DXEngine
{
	template <class T>
	class Vec3
	{
	public:

		T x;
		T y;
		T z;

		Vec3(): x(0), y(0), z(0) {}
		Vec3(T px, T py, T pz): x(px), y(py), z(pz) {}


		Vec3& operator+=(const Vec3& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			return *this;
		}

		//Vec3& operator+=(T f) const
		//{
		//	x += f;
		//	y += f;
		//	z += f;
		//	return *this;
		//}

		Vec3 operator+(const Vec3& rhs) const
		{
			Vec3 result = *this;
			result += rhs;
			return result;
		}

		//Vec3& operator+(T f) const
		//{
		//	Vec3 result = *this;
		//	result += f;
		//	return result;
		//}


		Vec3& operator-=(const Vec3& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			return *this;
		}

		Vec3 operator-(const Vec3& rhs) const
		{
			Vec3 result = *this;
			result -= rhs;
			return result;
		}

		Vec3 operator-() const
		{
			Vec3 result(-x, -y, -z);
			return result;
		}

		Vec3& operator*=(T f)
		{
			x *= f;
			y *= f;
			z *= f;
			return *this;
		}

		Vec3 operator*(T f) const
		{
			return Vec3(x * f, y * f, z * f);
			//Vec3 result = *this;
			//result *= f;
			//return result;
		}

		Vec3& operator/=(T t) const
		{
			x /= t;
			y /= t;
			z /= t;
			return *this;
		}

		Vec3 operator/ (T f) const
		{
			return Vec3(x/f,y/f,z/f);
		}

		float Length() const
		{
			return sqrt(SqrLength());
		}

		float SqrLength() const
		{
			return x * x + y * y + z * z;
		}

		void Normalize()
		{
			T oneOverLen = 1.0f / Length();
			*this *= oneOverLen;
			assert(SqrLength() > 0.99f && SqrLength() < 1.01f);
		}

		//float DotProduct(const Vec3& v) const
		//{
		//	return x * v.x + y * v.y + z * v.z;
		//}

		Vec3 CrossProduct(const Vec3 &v)
		{
			return Vec3(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
		}

		float DotProduct(const Vec3 &v)
		{
			return x*v.x + y*v.y + z*v.z;
		}
	};

	inline
		float RadToDeg (float Angle) 
	{
		static float ratio = 180.0f / 3.141592653589793238f;
		//static float ratio = 180.0f / static_cast<float>(M_PI);
		return Angle * ratio;
	}

	inline 
		float DegToRad (float Angle)
	{
		float ratio = (Angle / 180.0f) * 3.141592653589793238f;
		return ratio;// * 3.141592653589793238f;
	}

	template <class T>
	T DotProduct(const Vec3<T>& u, const Vec3<T>& v)
	{
		return u.x * v.x + u.y * v.y + u.z * v.z;
	}

	template <class T>
	Vec3<T> CrossProduct(const Vec3<T>& u, const Vec3<T>& v)
	{
		return Vec3<T>(u.y * v.z - u.z * v.y,
			u.z * v.x - u.x * v. z,
			u.x * v.y - u.y * v.x);
	}

	typedef Vec3<int> Vec3i;
	typedef Vec3<float> Vec3f;
	typedef Vec3<double> Vec3d;
}

#endif