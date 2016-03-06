#ifndef _WX_MAIN_FRM_H_
#define _WX_MAIN_FRM_H_

#include "wx/wx.h"

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

		wxStaticText		*m_pLogText;


		DECLARE_EVENT_TABLE()
	};
}

#endif