#include "glfwProxy.h"
#include "assert.h"
#include <string>
#include <fstream>
#include <sstream>
#include <streambuf>
#include "../common/tools.h"
#include "../luaProxy/luaProxy.h"
#include "../input/InputEventLsnr_debug.h"
#include "../input/InputMngr.h"

#include "wxMainFrm.h"
#include <iostream>

void PrintInfo();

void MouseBtnFunc(GLFWwindow* wnd, int, int, int);
void MouseMoveFunc(GLFWwindow* wnd, double, double);
void MouseEnterFunc(GLFWwindow* wnd, int);
void MouseWheelFunc(GLFWwindow* wnd, double, double);
void KeyFunc(GLFWwindow* wnd, int, int, int, int);

namespace CFGui
{
	CGlfwProxy::CGlfwProxy() 
		:m_nNextMenuItemID(100)
		,m_pMainFrm(NULL)
		, m_glWnd(NULL)
	{
	}
	
	CGlfwProxy::~CGlfwProxy()
	{
	}
	
	bool CGlfwProxy::Init()
	{
		char pth[256];
		::GetCurrentDirectoryA( 250 , pth );

		std::ifstream strm("cfg/gui.lua", std::ios::in | std::ios::binary);
		DWORD err= GetLastError();
		IErrorInfo *ei;
		GetErrorInfo(err, &ei);

		std::stringstream buf;
		buf << strm.rdbuf();
		std::string contents(buf.str());

		CFLua::CLuaProxy::Ins().DoString(contents.c_str());
		return true;
	}

	bool CGlfwProxy::_createOpengl()
	{

		if (!glfwInit())
			return -1;

		m_glWnd = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
		if (!m_glWnd)
		{
			glfwTerminate();
			return -1;
		}

		glfwMakeContextCurrent(m_glWnd);

		PrintInfo();

		int w, h;
		glfwGetWindowSize(m_glWnd, &w, &h);

		int x, y;
		glfwGetWindowPos(m_glWnd, &x, &y);

		glfwSetWindowTitle(m_glWnd, "OK,this is a window.");

		HWND hdl = glfwGetWin32Window(m_glWnd);

		LONG style = ::GetWindowLong(hdl, GWL_STYLE);
		style &= (~WS_BORDER);
		style &= (~WS_CAPTION);
		style &= (~WS_DLGFRAME);
		style &= (~WS_SYSMENU);
		style &= (~WS_THICKFRAME);
		style &= (~WS_MINIMIZEBOX);
		style &= (~WS_MAXIMIZEBOX);
		::SetWindowLong(hdl, GWL_STYLE, style);

		glfwSetMouseButtonCallback(m_glWnd, MouseBtnFunc);
		glfwSetCursorPosCallback(m_glWnd, MouseMoveFunc);
		glfwSetScrollCallback(m_glWnd, MouseWheelFunc);
		glfwSetKeyCallback(m_glWnd, KeyFunc);

		//
		CFInput::InputEventLsnr_Debug lsnr;

		CFInput::CInputMngr::Ins().RegisterEventLsnr(CFInput::MouseDown, &lsnr);
		CFInput::CInputMngr::Ins().RegisterEventLsnr(CFInput::MouseUp, &lsnr);
		CFInput::CInputMngr::Ins().RegisterEventLsnr(CFInput::MouseMove, &lsnr);
		CFInput::CInputMngr::Ins().RegisterEventLsnr(CFInput::MouseWheel, &lsnr);
		CFInput::CInputMngr::Ins().RegisterEventLsnr(CFInput::KeyDown, &lsnr);
		CFInput::CInputMngr::Ins().RegisterEventLsnr(CFInput::KeyUp, &lsnr);
		//

		return true;
	}

	int CGlfwProxy::AddMenu(const char* menuText, const char* script)
	{
		if (!menuText || !script)
		{
			assert(0 && "CGlfwProxy::AddMenu(...) , input parameter is wrong .");
			return - 1;
		}

		if (!m_pMainFrm)
		{
			assert(0 && "CGlfwProxy::AddMenu(...) , m_pMainFrm is NULL .");
			return -2 ;
		}

		wxMenuBar* mb = m_pMainFrm->GetMenuBar();
		if (!mb)
		{
			assert(0 && "CGlfwProxy::AddMenu(...) ,wxMenuBar of m_pMainFrm is NULL .");
			return -3;
		}

		std::string  ts = menuText;
		std::vector<std::string> lst;
		if (CFTools::SplitString(ts, '/', lst) < 2)
			return -4;

		wxMenu* theOne = NULL;

		wxString txt0 = CFTools::StdStrToWxStr(lst[0]);
		wxString txt1 = CFTools::StdStrToWxStr(lst[1]);
		wxMenu*		menu0 = NULL;

		int p = mb->FindMenu(txt0);
		if (p < 0)
		{
			menu0 = new wxMenu();
			mb->Append(menu0, txt0);
		}
		else
		{
			menu0 = mb->GetMenu(p);
		}

		//
		std::vector<std::string>	vecS;

		std::vector<std::string>::iterator itr = lst.begin();
		advance(itr,1);
		for (; itr != lst.end(); itr++)
			vecS.push_back(*itr);

		wxMenuItem* mi = _addMenuItem(menu0, vecS);
		if (mi == NULL)
		{
			assert(0 && "_addMenuItem() failed ...");
		}

		MenuItem& theMi = m_mpMenuItems[mi->GetId()];
		theMi.m_text = menuText;
		theMi.m_strScript = script;

		return 0;
	}

	wxMenuItem* CGlfwProxy::_addMenuItem(wxMenu* prntMenu , std::vector<std::string>& txts)
	{
		if ( txts.size() == 0 )
		{
			return NULL ;
		}
		else if ( txts.size() == 1 )
		{
			wxString s = CFTools::StdStrToWxStr(txts[0]);
			int p = prntMenu->FindItem(s);
			int id = -1;
			if (p < 0)
			{
				id = _NextMenuItemID();
				prntMenu->Append(id, s, _T(""), false);
			}
			else
			{
				wxMenuItem* mi = prntMenu->FindItemByPosition(p);
				id = mi->GetId();
			}

			return prntMenu->FindItem(id);
		}
		else
		{
			wxString s = CFTools::StdStrToWxStr( txts[0] );
			txts.erase(txts.begin());
			wxMenuItem* newItem = NULL;
			//

			wxMenu *subMn = new wxMenu();
			prntMenu->AppendSubMenu(subMn , s );
			
			return _addMenuItem( subMn , txts );
		}

		return NULL;
	}

	void CGlfwProxy::OnMenuItemEvent(int id)
	{
		std::string fn;
		std::map< int, MenuItem >::iterator itr = m_mpMenuItems.find(id);
		if (itr != m_mpMenuItems.end())
		{
			fn = itr->second.m_strScript;
			CFLua::CLuaProxy::Ins().DoFile( fn.c_str() );
		}
	}

	void CGlfwProxy::DisplayLog( const char* s , int tp )
	{
		if (m_pMainFrm)
		{
			CWxMainFrm* mf = (CWxMainFrm*)m_pMainFrm;
			mf->DisplayLog( s );
		}
	}

	void CGlfwProxy::MessageBox(const char* s)
	{
		wxMessageBox(wxString(s), wxString(""));
	}

	void CGlfwProxy::OnMainFrmMoved(wxPoint pos, wxSize sz)
	{

	}
}

////
void PrintInfo()
{
	const char* ver = (const char*)glGetString(GL_VERSION);

	GLenum err = glewInit();

	if (err != GLEW_OK)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		exit(-2);
	}

	int NumberOfExtensions;
	glGetIntegerv(GL_NUM_EXTENSIONS, &NumberOfExtensions);
	for (int i = 0; i<NumberOfExtensions; i++)
	{
		const GLubyte *ccc = glGetStringi(GL_EXTENSIONS, i);
		//Now, do something with ccc  
		std::cout << ccc << std::endl;
	}
}

void MouseBtnFunc(GLFWwindow* wnd, int btn, int action, int flg)
{
	double x;
	double y;
	glfwGetCursorPos(wnd, &x, &y);

	if (action == GLFW_PRESS)
		CFInput::CInputMngr::Ins().OnMouseDown(btn, x, y, flg);
	else if (action == GLFW_RELEASE)
		CFInput::CInputMngr::Ins().OnMouseUp(btn, x, y, flg);
}

void MouseMoveFunc(GLFWwindow* wnd, double x, double y)
{
	CFInput::CInputMngr::Ins().OnMouseMove(x, y, 0);
}

void MouseEnterFunc(GLFWwindow* wnd, int){}

void MouseWheelFunc(GLFWwindow* wnd, double x, double y)
{
	double px;
	double py;

	glfwGetCursorPos(wnd, &px, &py);

	CFInput::CInputMngr::Ins().OnMouseWheel((int)(x + y), px, py, 0);
}

void KeyFunc(GLFWwindow* wnd, int key, int scanCode, int action, int flg)
{
	if (action == GLFW_PRESS)
	{
		CFInput::CInputMngr::Ins().OnKeyDown(key);
	}
	else if (action == GLFW_RELEASE)
	{
		CFInput::CInputMngr::Ins().OnKeyUp(key);
	}
}
