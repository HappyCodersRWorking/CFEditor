#include "luaProxy.h"

#include "cFunction.h"

namespace CFLua
{

	CLuaProxy::CLuaProxy()
	{
		m_pLua = luaL_newstate();
		luaL_openlibs(m_pLua);
		luaopen_table(m_pLua);
	}

	CLuaProxy::~CLuaProxy()
	{
		lua_close(m_pLua);
	}

	bool CLuaProxy::Init()
	{
		RegisterFuns();
		return true;
	}

	bool CLuaProxy::RegisterFuns()
	{
		int cnt = GET_ARRAY_LEN(s_luaFuncInfo);
		for ( int i = 0; i < cnt; i++ )
		{
			lua_register( m_pLua , s_luaFuncInfo[i].funcName, s_luaFuncInfo[i].func) ;
		}

		return true;
	}

	bool CLuaProxy::DoString(const char* str)
	{
		if (!str)
			return false;

		luaL_dostring(m_pLua, str);

		return true;
	}

	bool CLuaProxy::DoFile(const char* pth)
	{
		if (!pth)
			return false;

		luaL_dofile(m_pLua, pth);

		return true;
	}
}