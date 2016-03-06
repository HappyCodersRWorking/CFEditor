#include "logger.h"

#define IFNULLRETURN(x) if(!x)return ;

namespace CF
{
	void CLogger::LogMsg(const char* s)
	{
		IFNULLRETURN(s);


	}

	void CLogger::LogWrn(const char* s)
	{
		IFNULLRETURN(s);
	}

	void CLogger::LogErr(const char* s)
	{
		IFNULLRETURN(s);
	}
}
