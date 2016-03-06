#ifndef _CF_GL_WND_H_
#define _CF_GL_WND_H_

/*
	����������װGLFWWindow�������书�ܣ��Լ�������ص���������
*/

#include "glfw3.h"
#include "../command/cmdGen.h"
#include "../input/InputEventLsnr.h"
#include "../Editor/GLEditWndContext.h"

namespace CFGui
{
	class CGLWndProxy : public CFInput::InputEventLsnr, public CFCommand::CmdGen
	{
	public:
		CGLWndProxy(GLFWwindow* pWnd);
		virtual ~CGLWndProxy();
		virtual void OnInputEvent(const CFInput::InputEvent&) ;
	protected:
		GLFWwindow					*m_pWnd;
		CFEditor::CGLEditWndContext	*m_pEditContext;
	};
}


#endif