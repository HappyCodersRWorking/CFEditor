#include "cFunction.h"
#include "../Editor/EditorContext.h"
#include "../wnd/glfwProxy.h"

extern "C" int EnterEditMode(lua_State* L)
{
	int prm = luaL_checkinteger(L, 1);
	int ret = CFEditor::CEditorContext::Ins().EnterEditMode(prm);
	//int ret = _EnterEditMode(g_pEditorContext, prm);
	lua_pushinteger(L, ret);
	return 1;
}

extern "C" int QuitEditMode(lua_State* L)
{
	int ret = CFEditor::CEditorContext::Ins().QuitEditMode() ;
	//int ret = _QuitEditMode(g_pEditorContext);
	lua_pushinteger(L, ret);
	return 1;
}

extern "C" int ChangeViewMode(lua_State* L)
{
	size_t sz = 0;
	const char* md = luaL_checklstring(L, 1, &sz);
	int ret = CFEditor::CEditorContext::Ins().ChangeViewMode(md);
	//int ret = _ChangeViewMode(g_pEditorContext, md);
	lua_pushinteger(L, ret);
	return 1;
}

extern "C" int ChangeSelectMode(lua_State* L)
{
	size_t sz = 0;
	const char* md = luaL_checklstring(L, 1, &sz);
	int ret = CFEditor::CEditorContext::Ins().ChangeSelMode(md);
	//int ret = _ChangeSelMode(g_pEditorContext, md);
	lua_pushinteger(L, ret);
	return 1;
}

extern "C" int AddMenuItem(lua_State* L)
{
	size_t sz0 = 0;
	size_t sz1 = 0;
	const char* s0 = luaL_checkstring(L, 1, &sz);
	const char* s1 = luaL_checkstring(L, 2, &sz);

	int ret = CFGui::CGlfwProxy::Ins().AddMenu(s0, s1);
	lua_pushinteger(L, ret);
	return 1;
}

extern "C" int LogMsg(lua_State* L)
{
	size_t sz = 0;
	const char* s = luaL_checkstring(L, 1, &sz);
	CFGui::CGlfwProxy::Ins().DisplayLog(s, 0);
	return 0;
}

extern "C" int LogWrn(lua_State* L)
{
	size_t sz = 0;
	const char* s = luaL_checkstring(L, 1, &sz);
	CFGui::CGlfwProxy::Ins().DisplayLog(s, 1);
	return 0;
}

extern "C" int LogErr(lua_State* L)
{
	size_t sz = 0;
	const char* s = luaL_checkstring(L, 1, &sz);
	CFGui::CGlfwProxy::Ins().DisplayLog(s, 2);

	return 0;
}