#ifndef _CF_OBJECT_H_
#define _CF_OBJECT_H_

#include <string>

/*
	CF::Object	作为所有场景物件的基类，管理最基本的属性
*/

namespace CF
{
	class Object
	{
	public:
		Object(){}
		Object(const std::string& nm):m_strName(nm){}
		void SetName(const std::string& nm){ m_strName = nm; }
		const std::string& GetName()	{ return m_strName; }
	protected:
		std::string		m_strName;
	};
}

#endif