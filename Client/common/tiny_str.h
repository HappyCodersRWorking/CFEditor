#ifndef _CF_TINY_STR_H_
#define _CF_TINY_STR_H_

#include "assert.h"

namespace CF
{
	template<typename T>
	class CTiStr
	{
	public:
		enum SIZE_TYPE
		{
			SZ_MIN=-1,
			SZ_32,
			SZ_64,
			SZ_128,
			SZ_256,
			SZ_512,
			SZ_MAX
		};

		CTiStr(SIZE_TYPE szTp = SZ_128)
		{
			m_eSzTp = szTp;
			int cnt = GetEleCntByType(m_eSzTp);
			m_pData = new T[cnt];
		}

		CTiStr(T* dt, SIZE_TYPE szTp = SZ_128)
		{
			m_eSzTp = szTp;
			int cnt = GetEleCntByType(m_eSzTp);
			m_pData = new T[cnt];

			SetData(dt);
		}

		virtual ~CTiStr()
		{
			if (m_pData)
				delete[] m_pData;
		}

		SIZE_TYPE GetSzType()	{ return m_eSzTp ; }

		static int GetEleCntByType(SIZE_TYPE tp)
		{
			if (tp <= SZ_MIN || tp >= SZ_MAX)
			{
				assert(0 && "CTinyStr::GetEleCntByType() , unknown type .");
				return 0;
			}

			switch (tp)
			{
			case SZ_32:
				return 32 ;
			case SZ_64:
				return 64 ;
			case SZ_128:
				return 128 ;
			case SZ_256:
				return 256 ;
			case SZ_512:
				return 512 ;
			default:
				break;
			}

			assert(0 && "CTinyStr::GetEleCntByType() , unknown type .");
			return 0;
		}

		static int GetTypeSz(SIZE_TYPE tp)
		{
			if (tp <= SZ_MIN || tp >= SZ_MAX)
			{
				assert(0 && "CTinyStr::GetTypeSz() , unknown type .");
				return 0;
			}

			switch (tp)
			{
			case SZ_32:
				return 32 * sizeof(T);
			case SZ_64:
				return 64 * sizeof(T);
			case SZ_128:
				return 128 * sizeof(T);
			case SZ_256:
				return 256 * sizeof(T);
			case SZ_512:
				return 512 * sizeof(T);
			default:
				break;
			}

			assert(0 && "CTinyStr::GetTypeSz() , unknown type .");
			return 0;
		}

		const T* GetPtr()const{ return m_pData; }

		int SetData(const T* dt)
		{
			int eleCnt = GetEleCntByType(m_eSzTp);
			int i = 0;
			for ( ; i < eleCnt; i++)
			{
				if (dt[i] == 0 || i == eleCnt - 1 )
				{
					m_pData[i] = 0;
					break;
				}
				else
				{
					m_pData[i] = dt[i];
				}
			}

			return i + 1;
		}

		T operator[](int ind)	const
		{
			return m_pData[ind];
		}

		const CTiStr& operator= (const T* ptr)
		{
			SetData(ptr);
			return *this;
		}

		const CTiStr& operator= (const CTiStr& o)
		{
			SetData(o.GetPtr());
			return *this;
		}

		bool operator==(const T* ptr)
		{
			int eleCnt = GetEleCntByType(m_eSzTp);
			for (int i = 0; i < eleCnt; i++)
			{
				if (m_pData[i] == 0)
				{
					if (ptr[i] == 0)
						return true;
					else
						return false;
				}
				else
				{
					if (m_pData[i] != ptr[i])
						return false;
				}
			}

			return true;
		}

		bool operator==(const CTiStr& o)
		{
			int eleCnt0 = GetEleCntByType(m_eSzTp);
			int eleCnt1 = GetEleCntByType(o.GetSzType());

			for (int i = 0; i < eleCnt0 && i < eleCnt1 ; i++)
			{
				if (m_pData[i] == 0)
				{
					if (o[i] == 0)
						return true;
					else
						return false;
				}
				else
				{
					if (m_pData[i] != o[i])
						return false;
				}
			}
			return true;
		}

	protected:
		SIZE_TYPE		m_eSzTp;
		int				m_nDataLen;
		T				*m_pData;
	};

	typedef CTiStr<char>		CTiStrA;
	typedef CTiStr<wchar_t>		CTiStrW;
}

#endif