#ifndef _CF_MAT_4X4_H_
#define _CF_MAT_4X4_H_

#include "mathTools.h"
#include "vec3.h"

namespace CFMath
{
	template<typename T >
	class Mat4x4
	{
	public:
		Mat4x4();

		Mat4x4(const Mat4x4& o)
		{
			for (int i = 0; i < 16; i++)
				m_ele[i] = o.m_ele[i];
		}

		Mat4x4(T* ptr)
		{
			for (int i = 0; i < 16; i++)
				m_ele[i] = ptr[i];
		}

		virtual ~Mat4x4();

		const Mat4x4& operator=(const Mat4x4& o)
		{
			for (int i = 0; i < 16; i++)
				m_ele[i] = o.m_ele[i];

			return *this;
		}

		Mat4x4 operator *(const Mat4x4& o)	const
		{
			Mat4x4 v;

			for (y = 0; y < 4; y++)
			{
				for (x = 0; x < 4; x++)
				{
					v[y * 4 + x] = m_ele[y * 4] * o.m_ele[x]
						+ m_ele[y * 4 + 1] * o.m_ele[4 + x]
						+ m_ele[y * 4 + 2] * o.m_ele[8 + x]
						+ m_ele[y * 4 + 3] * o.m_ele[12 + x];
				}
			}

			return v;
		}

		Vec3<T> operator * (const Vec3<T>& o)	const
		{
			Vec3<T> v;
			v.Set(m_ele[0] * o.X() + m_ele[1] * o.Y() + m_ele[2] * o.Z() + m_ele[3] * 1,
				m_ele[4] * o.X() + m_ele[5] * o.Y() + m_ele[6] * o.Z() + m_ele[7] * 1,
				m_ele[8] * o.X() + m_ele[9] * o.Y() + m_ele[10] * o.Z() + m_ele[11] * 1);

			T w = m_ele[12] * o.X() + m_ele[13] * o.Y() + m_ele[14] * o.Z() + m_ele[15] * 1;
			v /= w;
			return v;
		}

		void TranslateVec3( Vec3<T>& inOut )	const
		{
			Vec3<T> v = (*this) * inOut;
			inOut = v;
		}

		void LoadIdentity()
		{
			for (int i = 0; i < 16; i++)
				m_ele[i] = 0;

			m_ele[0] = m_ele[5] = m_ele[10] = m_ele[15] = 1 ;
		}

		Mat4x4 GetTransvers()	const
		{
			Mat4x4 v;
			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					v.m_ele[y * 4 + x] = m_ele[x * 4 + y];
				}
			}

			return v;
		}

		void MakeTransvers()
		{
			Swap_r<T>(m_ele[1], m_ele[4]);
			Swap_r<T>(m_ele[2], m_ele[8]);
			Swap_r<T>(m_ele[3], m_ele[12]);
			
			Swap_r<T>(m_ele[6], m_ele[9]);
			Swap_r<T>(m_ele[7], m_ele[13]);
			Swap_r<T>(m_ele[11], m_ele[14]);
		}

		void MakeTranslation(T x, T y, T z)
		{
			LoadIdentity();
			m_ele[3] = x;
			m_ele[7] = y;
			m_ele[11] = z;
		}

		void MakeRotationX(T angle)
		{
			LoadIdentity();

			m_ele[5] = cosf(angle);
			m_ele[6] = sinf(angle);
			m_ele[9] = -sinf(angle);
			m_ele[10] = cosf(angle);
		}

		void MakeRotationY(T angle)
		{
			LoadIdentity();

			m_ele[0] = cosf(angle);
			m_ele[2] = -sinf(angle);
			m_ele[8] = sinf(angle);
			m_ele[10] = cosf(angle);
		}

		void MakeRotationZ(T angle)
		{
			LoadIdentity();

			m_ele[0] = cosf(angle);
			m_ele[1] = sinf(angle);
			m_ele[4] = -sinf(angle);
			m_ele[5] = cosf(angle);
		}

		void FromAngleAxis( T angle , const Vec3<T>& u )
		{
			LoadIdentity();

			m_ele[0] = cosf(angle) + u.x * u.x * (1 - cosf(angle));
			m_ele[1] = u.x * u.y * (1 - cosf(angle) - u.z * sinf(angle));
			m_ele[2] = u.y * sinf(angle) + u.x * u.z * (1 - cosf(angle));

			m_ele[4] = u.z * sinf(angle) + u.x * u.y * (1 - cosf(angle));
			m_ele[5] = cosf(angle) + u.y * u.y * (1 - cosf(angle));
			m_ele[6] = -u.x * sinf(angle) + u.y * u.z * (1 - cosf(angle));

			m_ele[8] = -u.y * sinf(angle) + u.x * u.z * (1 - cosf(angle));
			m_ele[9] = u.x * sinf(angle) + u.y * u.z * (1 - cosf(angle));
			m_ele[10] = cosf(angle) + u.z * u.z * (1 - cosf(angle));
		}
	protected:
		T	m_ele[16];
	};
}

#endif