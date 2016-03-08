#include "wxMainFrm.h"
//#include "glfwProxy.h"

namespace CFGui
{
	BEGIN_EVENT_TABLE(CWxMainFrm, wxFrame)
		EVT_MENU_RANGE(100, 500, OnMenuItemClicked)
		EVT_SIZE(OnWndSize)
		EVT_SIZING(OnWndSizing)
		EVT_MOVE(OnWndMove)
		EVT_MOVING(OnWndMoving)
		EVT_MOVE_START(OnWndMoveStart)
		EVT_MOVE_END(OnWndMoveEnd)

	END_EVENT_TABLE()

	CWxMainFrm::CWxMainFrm(const wxChar *title, int xpos,
		int ypos, int width, int height)
		: wxFrame((wxFrame *)NULL, -1, title, wxPoint(xpos, ypos),
		wxSize(width, height))
	{
		//CGlfwProxy::Ins().SetMainFrame(this);

		wxMenuBar* bar = new wxMenuBar();
		this->SetMenuBar( bar );

		//
		m_pLogText = new wxStaticText(this, wxID_ANY, _T("for test"));

		m_pLstBox = new wxListBox(this, wxID_ANY , wxPoint(-1,-1));

		int attribs[] = { WX_GL_RGBA, WX_GL_DOUBLEBUFFER, 0 };

		m_pGlCanvas = new CGLWnd(this, attribs);
		m_pGlCntxt = new CFGLContext(m_pGlCanvas);
		m_pGlCanvas->SetContext(m_pGlCntxt);

		m_pGlCanvas->SetCurrent(*m_pGlCntxt);

		Centre();
	}

	CWxMainFrm::~CWxMainFrm() { }
	
	void CWxMainFrm::DisplayLog(wxString s)
	{
		if (m_pLogText)
			m_pLogText->SetLabelText(s);

		if (m_pLstBox)
		{
			m_pLstBox->Insert(s,0);

			int cnt = 0;
			while ((cnt = m_pLstBox->GetStrings().size()) > 100)
			{
				m_pLstBox->Delete(99);
			}
		}
	}

	void CWxMainFrm::OnMenuItemClicked(wxCommandEvent& evt)
	{
		wxString s = wxString::Format("MenuItem clicked : %d", evt.GetId());
		DisplayLog(s);
		//CFGui::CGlfwProxy::Ins().OnMenuItemEvent(evt.GetId());
	}

	void CWxMainFrm::OnWndSize(wxSizeEvent& evt)
	{
		DisplayLog(_T("OnWndSize"));
	}

	void CWxMainFrm::OnWndSizing(wxSizeEvent& evt)
	{
		DisplayLog(_T("OnWndSizing"));

		wxSize sz = this->GetSize();
		if (m_pLstBox)
		{
			m_pLstBox->SetPosition(wxPoint(5, 0));
			m_pLstBox->SetSize((sz.x - 10)/2, sz.y - 90);
		}

		if (m_pGlCanvas)
		{
			m_pGlCanvas->SetPosition(wxPoint(5 + (sz.x - 10) / 2, 0));
			m_pGlCanvas->SetSize((sz.x - 10) / 2, sz.y - 90);
		}

		if (m_pLogText)
		{
			m_pLogText->SetPosition(wxPoint(5, sz.y - 80));
			m_pLogText->SetSize(sz.x - 10, 20);
		}
	}

	void CWxMainFrm::OnWndMove(wxMoveEvent& evt)
	{
		DisplayLog(_T("OnWndMove"));
	}

	void CWxMainFrm::OnWndMoving(wxMoveEvent& evt)
	{
		DisplayLog(_T("OnWndMoving"));
	}

	void CWxMainFrm::OnWndMoveStart(wxMoveEvent& evt)
	{
		DisplayLog(_T("OnWndMoveStart"));
	}

	void CWxMainFrm::OnWndMoveEnd(wxMoveEvent& evt)
	{
		DisplayLog(_T("OnWndMoveEnd"));
		
		wxPoint p= this->GetPosition();
		wxSize sz = this->GetSize();
		//CFGui::CGlfwProxy::Ins().OnMainFrmMoved( p , sz);
	}
}