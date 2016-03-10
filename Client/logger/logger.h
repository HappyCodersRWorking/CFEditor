#ifndef _CF_LOGGER_H_
#define _CF_LOGGER_H_

typedef void(*LogFunc_0)( int msgType, const char* s );
typedef void(*LogFunc_1)(int msgType, const char* s, const char* s1);
typedef void(*LogFunc_2)(int msgType, const char* s, const char* s1, const char* s2);

namespace CF
{
	class CLogger
	{
	public:
		static CLogger& Ins()
		{
			static CLogger s_ins;
			return s_ins;
		}

		void LogMsg(const char*);
		void LogMsg(const char*, const char*);
		void LogMsg(const char*, const char*, const char*);

		void LogWrn(const char*);
		void LogWrn(const char*, const char*);
		void LogWrn(const char*, const char*, const char*);

		void LogErr(const char*);
		void LogErr(const char*, const char*);
		void LogErr(const char*, const char*, const char*);

		void RegisterFunc(LogFunc_0 fc0, LogFunc_1 fc1, LogFunc_2 fc2)
		{
			m_func0 = fc0;
			m_func1 = fc1;
			m_func2 = fc2;
		}
	protected:

		LogFunc_0		m_func0;
		LogFunc_1		m_func1;
		LogFunc_2		m_func2;
	};
}

#endif