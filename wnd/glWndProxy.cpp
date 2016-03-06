#include "glWndProxy.h"

namespace CFGui
{
	CGLWndProxy::CGLWndProxy(GLFWwindow* pWnd)
		:m_pWnd(pWnd)
	{
	}

	CGLWndProxy::~CGLWndProxy()
	{
	}

	void CGLWndProxy::OnInputEvent(const CFInput::InputEvent& ie)
	{
		switch (ie.GetType())
		{
		case CFInput::KeyDown:
			break;
		case CFInput::KeyUp:
			break;
		case CFInput::MouseDown:
			break;
		case CFInput::MouseUp:
			break;
		case CFInput::MouseMove:
			break;
		case CFInput::MouseWheel:
			break;
		}
	}
}