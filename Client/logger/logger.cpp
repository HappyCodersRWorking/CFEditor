#include "logger.h"
#include "stdio.h"

#define IFNULLRETURN(x) if(!x)return ;
#define IFNULLRETURN_2(x,y) if(!(x) || !(y))return ;
#define IFNULLRETURN_3(x,y,z) if(!(x) || !(y) ||!(z))return ;

namespace CF
{
	void CLogger::LogMsg(const char* s)
	{
		IFNULLRETURN(s);

		printf("MSG: %s\n", s);
		if (m_func0)	m_func0(0, s);
	}

	void CLogger::LogMsg(const char* s0 , const char* s1 )
	{
		IFNULLRETURN_2(s0,s1);

		printf("MSG: %s%s\n", s0 , s1 );
		if (m_func1)	m_func1(0, s0,s1);
	}

	void CLogger::LogMsg(const char* s0, const char* s1, const char* s2)
	{
		IFNULLRETURN_3(s0, s1, s2);

		printf("MSG: %s%s%s\n", s0, s1,s2);
		if (m_func2)	m_func2(0, s0, s1 , s2);
	}

	void CLogger::LogWrn(const char* s)
	{
		IFNULLRETURN(s);

		printf("WRN: %s\n", s);
		if (m_func0)	m_func0(1, s);
	}

	void CLogger::LogWrn(const char* s0, const char* s1)
	{
		IFNULLRETURN_2(s0, s1);

		printf("WRN: %s%s\n", s0, s1);
		if (m_func1)	m_func1(1, s0, s1);
	}

	void CLogger::LogWrn(const char* s0, const char* s1, const char* s2)
	{
		IFNULLRETURN_3(s0, s1, s2);

		printf("WRN: %s%s%s\n", s0, s1, s2);
		if (m_func2)	m_func2(1, s0, s1, s2);
	}

	void CLogger::LogErr(const char* s)
	{
		IFNULLRETURN(s);

		printf("ERR: %s\n", s);
		if (m_func0)	m_func0(2, s);
	}

	void CLogger::LogErr(const char* s0, const char* s1)
	{
		IFNULLRETURN_2(s0, s1);

		printf("ERR: %s%s\n", s0, s1);
		if (m_func1)	m_func1(2, s0, s1);
	}

	void CLogger::LogErr(const char* s0, const char* s1, const char* s2)
	{
		IFNULLRETURN_3(s0, s1, s2);

		printf("ERR: %s%s%s\n", s0, s1, s2);
		if (m_func2)	m_func2(2, s0, s1, s2);
	}
}
