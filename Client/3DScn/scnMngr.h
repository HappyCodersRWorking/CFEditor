#ifndef _CF_SCN_MNGR_H_
#define _CF_SCN_MNGR_H_

#include <string>
#include <map>

namespace CFScn
{
	class CScnMngr
	{
	public:
		CScnMngr();
		virtual ~CScnMngr();
		virtual bool Init();

		void SetName(const std::string& nm)	{ m_strName = nm; }
		const std::string& GetName()		{ return m_strName; }
	protected:
		std::string		m_strName;
	};
}

#endif