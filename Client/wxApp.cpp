#include "wxApp.h"
#include "wnd/wxMainFrm.h"
//#include "wnd/glfwProxy.h"
#include "luaProxy/luaProxy.h"

wxIMPLEMENT_APP(CFEditorApp);
double g_dSysTime= 0.0 ;

bool CFEditorApp::OnInit()
{
	//
	if (!wxApp::OnInit())
		return false;

	m_pMainFrm = new CFGui::CWxMainFrm(_T("Title"), 50, 50, 450, 300);
	m_pMainFrm->Show(TRUE);
	SetTopWindow(m_pMainFrm);

	CFLua::CLuaProxy::Ins().Init();
	//CFGui::CGlfwProxy::Ins().Init();

	return true;
}

bool CFEditorApp::ProcessIdle()
{
	static int flg = 0;
	flg++;
	if (flg > 50)
	{
		flg = 0;
		((CFGui::CWxMainFrm*)m_pMainFrm)->DisplayLog( _T("App::Idle...") );
	}
	return wxApp::ProcessIdle();
}
