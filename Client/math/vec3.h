#ifndef _CF_MATH_VEC3_H_
#define _CF_MATH_VEC3_H_

namespace CFMath
{
	template<typename  T>
	class Vec3
	{
	public:
		Vec3(){}
		Vec3(T x, T y ,T z) :m_x(x), m_y(y),m_z(z){}
		Vec3(const Vec3& other) :m_x(other.X()), m_y(other.Y()) , m_z(other.Z()){}
		void Set(T x, T y , T z)
		{
			m_x = x;
			m_y = y;
			m_z = z;
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

		const Vec3& operator=(const Vec3& other)
		{
			this->m_x = other.X();
			this->m_y = other.Y();
			this->m_z = other.Z();
			return *this;
		}

		Vec3 operator +(const Vec3& other)
		{
			return Vec3(this->m_x + other.X(),
				this->m_y + other.Y()
				this->m_z + other.Z() );
		}

		const Vec3& operator +=(const Vec3& other)
		{
			this->m_x += other.X();
			this->m_y += other.Y();
			this->m_z += other.Z();
			return *this;
		}


		Vec3 operator -(const Vec3& other)
		{
			return Vec3(this->m_x - other.X(),
				this->m_y - other.Y()
				this->m_z - other.Z() );
		}

		const Vec3& operator -=(const Vec3& other)
		{
			this->m_x -= other.X();
			this->m_y -= other.Y();
			this->m_z -= other.Z();
			return *this;
		}

		T Dot(const Vec3& o)	const
		{
			return x * o.X() + y * o.Y() + z * o.Z();
		}

		Vec3 Cross(const Vec3& o)	const
		{
			return Vec3(y * o.X() - z * o.Y(),
				-x * o.Z() + z * o.X(),
				y * o.Z() - z * o.Y());
		}

		T operator[](int ind)
		{
			if (ind == 0)
				return x;
			if (ind == 1)
				return y;
			if (ind == 2)
				return z;
			return 0xffffffff;
		}

		Vec3 operator*(T prm)
		{
			return Vec3(this->m_x * prm,
				this->m_y * prm,
				this->m_z * prm );
		}

		const Vec3& operator*=(T prm)
		{
			this->m_x *= prm;
			this->m_y *= prm;
			this->m_z *= prm;
			return *this;
		}

		Vec3 operator/(T prm)
		{
			return Vec3(this->m_x / prm,
				this->m_y / prm, 
				this->m_z / prm );
		}

		const Vec3& operator/=(T prm)
		{
			this->m_x /= prm;
			this->m_y /= prm;
			this->m_z /= prm;
			return *this;
		}
	protected:
		T m_x, m_y , m_z ;
	};

	typedef Vec3<float>		Vec3f;
	typedef Vec3<double>	Vec3d;
	typedef Vec3<int>		Vec3i;
}

#endif