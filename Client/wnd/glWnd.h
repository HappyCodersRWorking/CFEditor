#ifndef _CF_GL_WND_H_
#define _CF_GL_WND_H_

#include "wx/glcanvas.h"
#include "wx/timer.h"

namespace CFGui
{
	class CFGLContext;
	class CGLWnd : public wxGLCanvas
	{
	public:
		CGLWnd(wxWindow *parent, int *attribList = NULL);
		~CGLWnd();

		void SetContext(CFGLContext *cntxt)	{ m_pContext = cntxt; }

	private:
		void OnPaint(wxPaintEvent& event);
		void Spin(float xSpin, float ySpin);
		void OnKeyDown(wxKeyEvent& event);
		void OnSpinTimer(wxTimerEvent& WXUNUSED(event));

		void OnPaintTmr(wxTimerEvent& WXUNUSED(event));

		CFGLContext		*m_pContext;

		// angles of rotation around x- and y- axis
		float m_xangle,
			m_yangle;

		wxTimer	m_paintTmr;
		wxTimer m_spinTimer;
		bool m_useStereo,
			m_stereoWarningAlreadyDisplayed;

		wxDECLARE_EVENT_TABLE();
	};
}

#endif