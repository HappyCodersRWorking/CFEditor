#ifndef _CF_MATH_TOOLS_H_
#define _CF_MATH_TOOLS_H_

#include <math.h>

namespace CFMath
{
	template<typename T>
	void Swap_p(T* a, T* b)
	{
		T tmp = *a;
		*a = *b;
		*b = tmp;
	}

	template<typename T>
	void Swap_r(T& a, T&b)
	{
		T tmp = a;
		a = b;
		b = tmp;
	}
}

#endif