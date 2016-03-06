#ifndef _CF_GL_WND_H_
#define _CF_GL_WND_H_

/*
	此类用来包装GLFWWindow，代理其功能，以及管理相关的输入和命令。
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