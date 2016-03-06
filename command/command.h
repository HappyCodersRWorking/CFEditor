#ifndef _CF_COMMAND_H_
#define _CF_COMMAND_H_

#include <string>

namespace CFCommand
{
	class Command
	{
	public:
		Command(){}
		Command(double tm) :m_dGenTime(tm){}
		virtual  ~Command(){}
		virtual void DoIt() {}
		virtual void UndoIt() {}

		void SetGenTime(double t){ m_dGenTime = t; }
		double GetGenTime()	{ return m_dGenTime; }
		void SetDelayTime(double t) { m_dDelayTime = t; }
		double GetDelayTime()	{ return m_dDelayTime; }
		void SetContentStr(const std::string& s) { m_strContent = s; }
		const std::string& GetContentStr()		{ return m_strContent; }
	protected:
		double		m_dGenTime;
		double		m_dDelayTime;
		std::string	m_strContent;
	};
}

#endif