#ifndef _CF_OBJECT_H_
#define _CF_OBJECT_H_

#include <string>

/*
	CF::Object	��Ϊ���г�������Ļ��࣬���������������
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