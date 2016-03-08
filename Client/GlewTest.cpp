// GlewTest.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <iostream>

#include "wx/wx.h"
#include <GL/glew.h>

#include "glfw3.h"
#include "glfw3native.h"

#include "input/InputMngr.h"
#include "input/InputEventLsnr_debug.h"

#include "wnd/wxGuiMngr.h"

using namespace std;

double g_dSysTime = 0;

#ifdef sdjfosifjio

void PrintInfo();

void MouseBtnFunc(GLFWwindow* wnd, int, int, int);
void MouseMoveFunc(GLFWwindow* wnd, double, double);
void MouseEnterFunc(GLFWwindow* wnd, int);
void MouseWheelFunc(GLFWwindow* wnd, double, double);
void KeyFunc(GLFWwindow* wnd, int, int, int, int);


int _tmain(int argc, _TCHAR* argv[])
{
	GLFWwindow* window;

	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	PrintInfo();

	int w, h;
	glfwGetWindowSize(window, &w, &h);

	int x, y;
	glfwGetWindowPos(window, &x, &y);

	glfwSetWindowTitle(window, "OK,this is a window.");

	HWND hdl = glfwGetWin32Window(window);

	LONG style = ::GetWindowLong(hdl, GWL_STYLE);
	style &= (~WS_BORDER);
	style &= (~WS_CAPTION);
	style &= (~WS_DLGFRAME);
	style &= (~WS_SYSMENU);
	style &= (~WS_THICKFRAME);
	style &= (~WS_MINIMIZEBOX);
	style &= (~WS_MAXIMIZEBOX);
	::SetWindowLong(hdl, GWL_STYLE, style);

	glfwSetMouseButtonCallback( window , MouseBtnFunc);
	glfwSetCursorPosCallback(window, MouseMoveFunc);
	glfwSetScrollCallback(window, MouseWheelFunc);
	glfwSetKeyCallback(window, KeyFunc);

	//
	CFInput::InputEventLsnr_Debug lsnr;
	
	CFInput::CInputMngr::Ins().RegisterEventLsnr(CFInput::MouseDown, &lsnr);
	CFInput::CInputMngr::Ins().RegisterEventLsnr(CFInput::MouseUp, &lsnr);
	CFInput::CInputMngr::Ins().RegisterEventLsnr(CFInput::MouseMove, &lsnr);
	CFInput::CInputMngr::Ins().RegisterEventLsnr(CFInput::MouseWheel, &lsnr);
	CFInput::CInputMngr::Ins().RegisterEventLsnr(CFInput::KeyDown, &lsnr);
	CFInput::CInputMngr::Ins().RegisterEventLsnr(CFInput::KeyUp, &lsnr);
	//

	CFGui::CWXGuiMngr mgr;
	mgr.TestFunc001();

	while (!glfwWindowShouldClose(window))
	{
		g_dSysTime = glfwGetTime();

		//glfwSetWindowPos( window , sinf(t)* 200 + 400 , cosf(t) * 300 + 500 );

		/* Render here */

		glClearColor(0.5f + sinf(g_dSysTime) * 0.5f, 1.0f, 0.5f, 1.0f);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		_sleep(20);
	}

	glfwTerminate();

	system("pause");

	return 0;
}

#endif
