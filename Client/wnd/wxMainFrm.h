#ifndef _WX_MAIN_FRM_H_
#define _WX_MAIN_FRM_H_

#include "wx/wx.h"
#include "wx/glcanvas.h"
#include "glContext.h"
#include "glWnd.h"

namespace CFGui
{
	class CWxMainFrm : public wxFrame
	{
	public:
		CWxMainFrm(const wxChar *title, int xpos, int ypos,int width, int height);
		~CWxMainFrm();
		void DisplayLog(wxString s);
	protected:

		void OnMenuItemClicked(wxCommandEvent& evt);

		void OnWndSize(wxSizeEvent& evt);
		void OnWndSizing(wxSizeEvent& evt);
		void OnWndMove(wxMoveEvent& evt);
		void OnWndMoving(wxMoveEvent& evt);
		void OnWndMoveStart(wxMoveEvent& evt);
		void OnWndMoveEnd(wxMoveEvent& evt);

		void formatInternalCtrls();

		wxStaticText		*m_pLogText;

		wxListBox			*m_pLstBox;

		CGLWnd				*m_pGlCanvas;
		CFGLContext			*m_pGlCntxt;

		DECLARE_EVENT_TABLE()
	};
}

#endif