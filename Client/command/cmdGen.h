#ifndef _CF_CMD_GEN_H_
#define _CF_CMD_GEN_H_

#include "command.h"
#include <string>
#include <list>

namespace CFCommand
{
	class CmdGen
	{
	public:
		CmdGen(){}
		virtual ~CmdGen(){}

	protected:
		std::list<Command>		m_lstCmd;
	};
}

#endif