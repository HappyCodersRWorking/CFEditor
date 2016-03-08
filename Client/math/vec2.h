#ifndef _CF_VEC2_H_
#define _CF_VEC2_H_

namespace CFMath
{
	template<typename  T>
	class Vec2
	{
	public:
		Vec2(){}
		Vec2(T x, T y):m_x(x),m_y(y){}
		Vec2(const Vec2& other):m_x(other.X()),m_y(other.Y()){}
		void Set(T x, T y)
		{
			m_x = x;
			m_y = y;
		}

		T X() const
		{
			return m_x;
		}

		T Y() const
		{
			return m_y;
		}

		const Vec2& operator=(const Vec2& other)
		{
			this->m_x = other.X();
			this->m_y = other.Y();
			return *this;
		}

		Vec2 operator +( const Vec2& other )
		{
			return Vec2(this->m_x + other.X() ,
				this->m_y + other.Y() );
		}

		const Vec2& operator +=(const Vec2& other)
		{
			this->m_x += other.X();
			this->m_y += other.Y();
			return *this;
		}


		Vec2 operator -(const Vec2& other)
		{
			return Vec2(this->m_x - other.X(),
				this->m_y - other.Y() );
		}

		const Vec2& operator -=(const Vec2& other)
		{
			this->m_x -= other.X();
			this->m_y -= other.Y();
			return *this;
		}

		Vec2 operator*( T prm )
		{
			return Vec2( this->m_x * prm ,
				this->m_y * prm ) ;
		}

		const Vec2& operator*=(T prm)
		{
			this->m_x *= prm;
			this->m_y *= prm;
			return *this;
		}

		Vec2 operator/(T prm)
		{
			return Vec2(this->m_x / prm,
				this->m_y / prm ) ;
		}

		const Vec2& operator/=(T prm)
		{
			this->m_x /= prm;
			this->m_y /= prm;
			return *this;
		}
	protected:
		T m_x, m_y;
	};

	typedef Vec2<float>		Vec2f;
	typedef Vec2<double>	Vec2d;
	typedef Vec2<int>		Vec2i;
}

#endif