#ifndef _C_FUNCTIONS_H_
#define _C_FUNCTIONS_H_

#include "../lua/lua.hpp"

#define GET_ARRAY_LEN(arry) (sizeof(arry) / sizeof(arry[0]))

extern "C" int EnterEditMode(lua_State*);
extern "C" int QuitEditMode(lua_State*);
extern "C" int ChangeViewMode(lua_State*);
extern "C" int ChangeSelectMode(lua_State*);

extern "C" int AddMenuItem(lua_State*);
extern "C" int LogMsg(lua_State*);
extern "C" int LogWrn(lua_State*);
extern "C" int LogErr(lua_State*);

//
typedef int(*luaFormatFunc)(lua_State*);

struct FuncInfo
{
	const char*		funcName;
	luaFormatFunc	func;
};

static FuncInfo s_luaFuncInfo[] =
{
	{ "EnterEditMode", EnterEditMode },
	{ "QuitEditMode" , QuitEditMode },
	{ "ChangeViewMode", ChangeViewMode },
	{ "ChangeSelectMode", ChangeSelectMode },
	{ "AddMenuItem", AddMenuItem },
	{ "LogMsg", LogMsg },
	{ "LogWrn", LogWrn },
	{ "LogErr", LogErr },
};

#endif