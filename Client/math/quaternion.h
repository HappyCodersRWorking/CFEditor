#ifndef _CF_MATH_QUATERNION_H_
#define _CF_MATH_QUATERNION_H_

#include "vec3.h"

namespace CFMath
{
	template<typename T>
	class CQuaternion
	{
	public:
		CQuaternion(){}
		CQuaternion(T xx , T yy , T zz , T ww)
		:x(xx),y(yy),z(zz),w(ww){}

		CQuaternion(const CQuaternion& o)
		{
			x = o.x;
			y = o.y;
			z = o.z;
			w = o.w;
		}

		void FromAngleAxis( const Vec3<T>& axis , T angle )
		{
			Vec3<T> tmp(axis);
			tmp.Normalize();

			T sinV = sinf(angle / 2);

			x = tmp.X() * sinV;
			y = tmp.Y() * sinV;
			z = tmp.Z() * sinV;
			w = cosf(angle / 2);
		}

		CQuaternion operator*(const CQuaternion& o)	const
		{
			/*
			return CQuaternion(
				x * o.x + y * o.w + z * o.z - w * o.y,
				x * o.y - y * o.z + z * o.w + w * o.x,
				x * o.z + w * o.w - z * o.x + y * o.y,
				x * o.w - y * o.x - z * o.y - w * o.z);
				*/

			/*return CQuaternion(
				w * o.x + x * o.w + z * o.y - y * o.z,
				w * o.y + y * o.w + x * o.z - z * o.x,
				w * o.z + z * o.w + y * o.x - x * o.y,
				w * o.w - x * o.x - y * o.y - z * o.z);*/

			return CQuaternion(
				w * o.x + x * o.w - z * o.y + y * o.z,
				w * o.y + y * o.w - x * o.z + z * o.x,
				w * o.z + z * o.w - y * o.x + x * o.y,
				w * o.w - x * o.x - y * o.y - z * o.z); 
		}

		Vec3<T> operator*(const Vec3<T>& v)	const
		{
			Vec3<T> uv , uuv ;
			Vec3<T> qvec(x, y, z);
			uv = qvec.Cross(v);
			uuv = qvec.Cross(uv);
			uv *= (2.0f * w);
			uuv *= 2.0f;
			return v + uv + uuv;
		}

	protected:
		T x, y, z, w;
	};

	typedef CQuaternion<float>		CQuatf;
	typedef CQuaternion<double>		CQuatd;
}

#endif