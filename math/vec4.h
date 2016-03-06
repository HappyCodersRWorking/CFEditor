#ifndef _CF_MATH_VEC4_H_
#define _CF_MATH_VEC4_H_

namespace CFMath
{
	template<typename  T>
	class Vec4
	{
	public:
		Vec4(){}
		Vec4(T x, T y, T z , T w) :m_x(x), m_y(y), m_z(z) , m_w(w){}
		Vec4(const Vec4& other) 
			:m_x(other.X()), 
			m_y(other.Y()), 
			m_z(other.Z()),
			m_w(other.W()){}

		void Set(T x, T y, T z, T w)
		{
			m_x = x;
			m_y = y;
			m_z = z;
			m_w = w;
		}

		T X() const
		{
			return m_x;
		}

		T Y() const
		{
			return m_y;
		}

		T Z() const
		{
			return m_z;
		}

		T W() const
		{
			return m_w;
		}

		const Vec4& operator=(const Vec4& other)
		{
			this->m_x = other.X();
			this->m_y = other.Y();
			this->m_z = other.Z();
			this->m_w = other.W();
			return *this;
		}

		Vec4 operator +(const Vec4& other)
		{
			return Vec4(this->m_x + other.X(),
				this->m_y + other.Y(),
				this->m_z + other.Z(),
				this->m_w + other.W());
		}

		const Vec4& operator +=(const Vec4& other)
		{
			this->m_x += other.X();
			this->m_y += other.Y();
			this->m_z += other.Z();
			this->m_w += other.W();
			return *this;
		}


		Vec4 operator -(const Vec4& other)
		{
			return Vec4(this->m_x - other.X(),
				this->m_y - other.Y(),
				this->m_z - other.Z(),
				this->m_w - other.W());
		}

		const Vec4& operator -=(const Vec4& other)
		{
			this->m_x -= other.X();
			this->m_y -= other.Y();
			this->m_z -= other.Z();
			this->m_w -= other.W();
			return *this;
		}

		Vec4 operator*(T prm)
		{
			return Vec4(this->m_x * prm,
				this->m_y * prm,
				this->m_z * prm,
				this->m_w * prm);
		}

		const Vec4& operator*=(T prm)
		{
			this->m_x *= prm;
			this->m_y *= prm;
			this->m_z *= prm;
			this->m_w *= prm;
			return *this;
		}

		Vec4 operator/(T prm)
		{
			return Vec4(this->m_x / prm,
				this->m_y / prm,
				this->m_z / prm,
				this->m_w / prm);
		}

		const Vec4& operator/=(T prm)
		{
			this->m_x /= prm;
			this->m_y /= prm;
			this->m_z /= prm;
			this->m_w /= prm;
			return *this;
		}
	protected:
		T m_x, m_y, m_z, m_w;
	};

	typedef Vec4<float>		Vec4f;
	typedef Vec4<double>	Vec4d;
	typedef Vec4<int>		Vec4i;
}

#endif