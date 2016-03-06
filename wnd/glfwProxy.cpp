#include "glfwProxy.h"
#include "assert.h"
#include <string>
#include <fstream>
#include <sstream>
#include <streambuf>
#include "../common/tools.h"
#include "../luaProxy/luaProxy.h"
#include "wxMainFrm.h"

namespace CFGui
{
	CGlfwProxy::CGlfwProxy() 
		:m_nNextMenuItemID(100)
		,m_pMainFrm(NULL)
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
}