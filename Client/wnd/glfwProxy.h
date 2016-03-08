#ifndef _CF_GLFW_PROXY_H_
#define _CF_GLFW_PROXY_H_

#include <string>
#include <vector>
#include <map>
#include "wx/wx.h"
#include <GL/glew.h>
#include "glfw3.h"
#include "glfw3native.h"

namespace CFGui
{
	class MenuItem
	{
	public:
		std::string		m_text;
		std::string		m_strScript;
	};

	class CGlfwProxy
	{
	public:
		static CGlfwProxy& Ins()
		{
			static CGlfwProxy s_ins;
			return s_ins;
		}

		bool Init();

		void SetMainFrame(wxFrame* frm)		{ m_pMainFrm = frm; }
		int AddMenu( const char* menuText , const char* script );

		void OnMenuItemEvent(int id);
		void DisplayLog(const char* s, int tp = 0);		// for temp use

		void MessageBox(const char*);

		void OnMainFrmMoved(wxPoint pos, wxSize sz);
	protected:
		CGlfwProxy();
		virtual ~CGlfwProxy();

		bool _createOpengl();

		std::map< int, MenuItem >		m_mpMenuItems;

		int		m_nNextMenuItemID;
		int _NextMenuItemID(){ return m_nNextMenuItemID++; }

		wxFrame		*m_pMainFrm;
		wxMenuItem* _addMenuItem( wxMenu* parent , std::vector<std::string>& txts );

		//
		GLFWwindow*			m_glWnd ;

	};
}

#endif