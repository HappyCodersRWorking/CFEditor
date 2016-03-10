#ifndef _CF_OBJECT_H_
#define _CF_OBJECT_H_

#include "tiny_str.h"
/*
	CF::Object	作为所有场景物件的基类，管理最基本的属性
*/

namespace CF
{
	class Object
	{
	public:
		Object(){}
		Object(const CF::CTiStrW& nm) :m_strName(nm){}
		const CF::CTiStrW& GetName()	{ return m_strName; }
		void SetName(wchar_t* s)		{ m_strName = s; }
	protected:
		CF::CTiStrW				m_strName;
	};
}

#endif