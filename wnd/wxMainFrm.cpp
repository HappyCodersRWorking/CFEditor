#include "wxMainFrm.h"
#include "glfwProxy.h"

namespace CFGui
{
	BEGIN_EVENT_TABLE(CWxMainFrm, wxFrame)
		EVT_MENU_RANGE(100, 500, OnMenuItemClicked)
	END_EVENT_TABLE()

	CWxMainFrm::CWxMainFrm(const wxChar *title, int xpos,
		int ypos, int width, int height)
		: wxFrame((wxFrame *)NULL, -1, title, wxPoint(xpos, ypos),
		wxSize(width, height))
	{
		CGlfwProxy::Ins().SetMainFrame(this);

		wxMenuBar* bar = new wxMenuBar();
		this->SetMenuBar( bar );

		//
		m_pLogText = new wxStaticText(this, wxID_ANY, _T("for test"));
	}

	CWxMainFrm::~CWxMainFrm() { }
	
	void CWxMainFrm::DisplayLog(wxString s)
	{
		if (m_pLogText)
			m_pLogText->SetLabelText(s);
	}

	void CWxMainFrm::OnMenuItemClicked(wxCommandEvent& evt)
	{
		wxString s = wxString::Format("MenuItem clicked : %d", evt.GetId());
		DisplayLog(s);
		CFGui::CGlfwProxy::Ins().OnMenuItemEvent(evt.GetId());
	}
}