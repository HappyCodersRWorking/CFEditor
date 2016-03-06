#ifndef _CF_LUA_PROXY_H_
#define _CF_LUA_PROXY_H_

#include "../lua/lua.hpp"

namespace CFLua
{
	class CLuaProxy
	{
	public:
		static CLuaProxy& Ins()
		{
			static CLuaProxy s_ins;
			return s_ins;
		}

		bool Init();

		bool RegisterFuns();
		bool DoString(const char*);
		bool DoFile(const char* pth);
	protected:
		CLuaProxy();
		virtual ~CLuaProxy();

		lua_State		*m_pLua;
	};
}

#endif