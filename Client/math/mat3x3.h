#ifndef _CF_MAT_3X3_H_
#define _CF_MAT_3X3_H_

#include "mathTools.h"

namespace CFMath
{
	template<typename T >
	class Mat3x3
	{
	public:
		Mat3x3();
		
		Mat3x3(const Mat3x3& o)
		{
			for (int i = 0; i < 9; i++)
				m_ele[i] = o.m_ele[i];
		}
		
		Mat3x3(T* ptr)
		{
			for (int i = 0; i < 9; i++)
				m_ele[i] = ptr[i];
		}

		virtual ~Mat3x3();

		const Mat3x3& operator=(const Mat3x3& o)
		{
			for (int i = 0; i < 9; i++)
				m_ele[i] = o.m_ele[i];

			return *this;
		}

		Mat3x3 operator *(const Mat3x3& o)	const
		{
			Mat3x3 v;

			for (y = 0; y < 3; y++)
			{
				for (x = 0; x < 3; x++)
				{
					v[y * 3 + x] = m_ele[y * 3 ] * o.m_ele[ x ] 
						+ m_ele[ y * 3 + 1 ] * o.m_ele[ 3 + x ]
						+ m_ele[ y * 3 + 2 ] * o.m_ele[ 6 + x ];
				}
			}
			return v;
		}

		void LoadIdentity()
		{
			for (int i = 0; i < 9; i++)
				m_ele[i] = 0;

			m_ele[0] = m_ele[4] = m_ele[8] = 1;
		}

		Mat3x3 GetTransvers()	const 
		{
			Mat3x3 v;
			for (int y = 0; y < 3; y++)
			{
				for (int x = 0; x < 3; x++)
				{
					v.m_ele[y*3+x] = m_ele[x*3+y];
				}
			}

			return v;
		}

		void MakeTransvers()
		{
			Swap_r<T>(m_ele[1], m_ele[3]);
			Swap_r<T>(m_ele[2], m_ele[6]);
			Swap_r<T>(m_ele[5], m_ele[7]);
		}

	protected:
		T	m_ele[9];
	};
}

#endif