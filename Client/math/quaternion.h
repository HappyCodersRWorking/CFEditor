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
		CQuaternion(const CQuaternion& o)
		{
			x = o.x;
			y = o.y;
			z = o.z;
			w = o.w;
		}

		void FromAngleAxis( const Vec3<T>& axis , T angle )
		{
		}
	protected:
		T x, y, z, w;
	};
}

#endif