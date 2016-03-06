// GlewTest.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include "glfw3.h"
#include "glfw3native.h"

#include "input/InputMngr.h"
#include "input/InputEventLsnr_debug.h"

#include "wx/wx.h"
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

void PrintInfo()
{
	const char* ver = (const char*)glGetString(GL_VERSION);

	GLenum err = glewInit();

	if (err != GLEW_OK)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		exit(-2);

	}
	int NumberOfExtensions;
	glGetIntegerv(GL_NUM_EXTENSIONS, &NumberOfExtensions);
	for (int i = 0; i<NumberOfExtensions; i++)
	{
		const GLubyte *ccc = glGetStringi(GL_EXTENSIONS, i);
		//Now, do something with ccc  
		cout << ccc << endl;
	}
}

void MouseBtnFunc(GLFWwindow* wnd, int btn , int action , int flg )
{
	double x;
	double y;
	glfwGetCursorPos(wnd, &x, &y);

	if (action == GLFW_PRESS)
		CFInput::CInputMngr::Ins().OnMouseDown( btn , x , y , flg );
	else if ( action == GLFW_RELEASE)
		CFInput::CInputMngr::Ins().OnMouseUp(btn, x, y, flg);
}

void MouseMoveFunc(GLFWwindow* wnd, double x, double y)
{
	CFInput::CInputMngr::Ins().OnMouseMove(x, y, 0);
}

void MouseEnterFunc(GLFWwindow* wnd, int){}

void MouseWheelFunc(GLFWwindow* wnd , double x , double y)
{
	double px;
	double py;
	
	glfwGetCursorPos(wnd, &px , &py);

	CFInput::CInputMngr::Ins().OnMouseWheel((int)(x + y), px, py , 0);
}

void KeyFunc(GLFWwindow* wnd, int key , int scanCode , int action , int flg )
{
	if (action == GLFW_PRESS)
	{
		CFInput::CInputMngr::Ins().OnKeyDown(key);
	}
	else if (action == GLFW_RELEASE)
	{
		CFInput::CInputMngr::Ins().OnKeyUp(key);
	}
}
#endif