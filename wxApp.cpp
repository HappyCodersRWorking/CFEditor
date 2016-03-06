#include "wxApp.h"
#include "wnd/wxMainFrm.h"
#include "wnd/glfwProxy.h"
#include "luaProxy/luaProxy.h"

wxIMPLEMENT_APP(CFEditorApp);

bool CFEditorApp::OnInit()
{
	//
	if (!wxApp::OnInit())
		return false;

	CFGui::CWxMainFrm * frm = new CFGui::CWxMainFrm(_T("Title"), 50, 50, 450, 300);
	frm->Show(TRUE);
	SetTopWindow(frm);

	CFLua::CLuaProxy::Ins().Init();
	CFGui::CGlfwProxy::Ins().Init();

	return true;
}
