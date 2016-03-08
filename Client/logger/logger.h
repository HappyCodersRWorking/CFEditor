#ifndef _CF_LOGGER_H_
#define _CF_LOGGER_H_

namespace CF
{
	class CLogger
	{
	public:
		void LogMsg(const char*);
		void LogWrn(const char*);
		void LogErr(const char*);
	protected:
	};
}

#endif