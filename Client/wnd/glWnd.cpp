#include "glWnd.h"
#include "wx/frame.h"
#include "wx/dcclient.h"
#include "glContext.h"

wxBEGIN_EVENT_TABLE(CFGui::CGLWnd, wxGLCanvas)
EVT_PAINT(CFGui::CGLWnd::OnPaint)
EVT_KEY_DOWN(CFGui::CGLWnd::OnKeyDown)
EVT_TIMER(5, CFGui::CGLWnd::OnPaintTmr)
wxEND_EVENT_TABLE()

namespace CFGui
{
CGLWnd::CGLWnd(wxWindow *parent, int *attribList)
// With perspective OpenGL graphics, the wxFULL_REPAINT_ON_RESIZE style
// flag should always be set, because even making the canvas smaller should
// be followed by a paint event that updates the entire canvas with new
// viewport settings.
: wxGLCanvas(parent, wxID_ANY, attribList,
wxDefaultPosition, wxDefaultSize,
wxFULL_REPAINT_ON_RESIZE),
m_xangle(30.0),
m_yangle(30.0),
//m_spinTimer(this, SpinTimer),
m_paintTmr(this,5),
m_useStereo(false),
m_stereoWarningAlreadyDisplayed(false),
m_pContext(NULL)
{
	if (attribList)
	{
		int i = 0;
		while (attribList[i] != 0)
		{
			if (attribList[i] == WX_GL_STEREO)
				m_useStereo = true;
			++i;
		}
	}

	m_paintTmr.Start(20);
}

CGLWnd::~CGLWnd()
{
	if (m_pContext)
		delete m_pContext;
}

void CGLWnd::OnPaint(wxPaintEvent& WXUNUSED(event))
{
	return;
	// This is required even though dc is not used otherwise.
	wxPaintDC dc(this);

	// Set the OpenGL viewport according to the client size of this canvas.
	// This is done here rather than in a wxSizeEvent handler because our
	// OpenGL rendering context (and thus viewport setting) is used with
	// multiple canvases: If we updated the viewport in the wxSizeEvent
	// handler, changing the size of one canvas causes a viewport setting that
	// is wrong when next another canvas is repainted.
	const wxSize ClientSize = GetClientSize();

	//TestGLContext& canvas = wxGetApp().GetContext(this, m_useStereo);
	glViewport(0, 0, ClientSize.x, ClientSize.y);

	// Render the graphics and swap the buffers.
	GLboolean quadStereoSupported;
	glGetBooleanv(GL_STEREO, &quadStereoSupported);
	if (quadStereoSupported)
	{
		glDrawBuffer(GL_BACK_LEFT);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-0.47f, 0.53f, -0.5f, 0.5f, 1.0f, 3.0f);
		//canvas.DrawRotatedCube(m_xangle, m_yangle);
		//CheckGLError();
		glDrawBuffer(GL_BACK_RIGHT);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-0.53f, 0.47f, -0.5f, 0.5f, 1.0f, 3.0f);
		//canvas.DrawRotatedCube(m_xangle, m_yangle);
		//CheckGLError();
	}
	else
	{
		//canvas.DrawRotatedCube(m_xangle, m_yangle);
		if (m_useStereo && !m_stereoWarningAlreadyDisplayed)
		{
			m_stereoWarningAlreadyDisplayed = true;
			wxLogError("Stereo not supported by the graphics card.");
		}
	}

	glClearColor(0.5, 0.2, 0.2, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	SwapBuffers();
}

void CGLWnd::Spin(float xSpin, float ySpin)
{
	m_xangle += xSpin;
	m_yangle += ySpin;

	Refresh(false);
}

void CGLWnd::OnKeyDown(wxKeyEvent& event)
{
	float angle = 5.0;

	switch (event.GetKeyCode())
	{
	case WXK_RIGHT:
		Spin(0.0, -angle);
		break;

	case WXK_LEFT:
		Spin(0.0, angle);
		break;

	case WXK_DOWN:
		Spin(-angle, 0.0);
		break;

	case WXK_UP:
		Spin(angle, 0.0);
		break;

	case WXK_SPACE:
		if (m_spinTimer.IsRunning())
			m_spinTimer.Stop();
		else
			m_spinTimer.Start(25);
		break;

	default:
		event.Skip();
		return;
	}
}

void CGLWnd::OnSpinTimer(wxTimerEvent& WXUNUSED(event))
{
	Spin(0.0, 4.0);
}

void CGLWnd::OnPaintTmr(wxTimerEvent& WXUNUSED(event))
{
	glClearColor(0.5, 0.2, 0.2, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	if (m_pContext)
		m_pContext->Paint();

	SwapBuffers();
}
}
