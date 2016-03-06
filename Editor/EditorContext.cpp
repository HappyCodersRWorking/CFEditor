#include "EditorContext.h"

CFEditor::CEditorContext* g_pEditorContext = NULL ;

namespace CFEditor
{
	CEditorContext::CEditorContext()
	{
		g_pEditorContext = this;
	}

	CEditorContext::~CEditorContext(){}


	int CEditorContext::EnterEditMode(int prm)
	{
		GLWndPtrArray::iterator itr = m_glWndProxy.begin();
		for (; itr != m_glWndProxy.end(); itr++)
		{
			CFGui::CGLWndProxy* wnd = *itr;
			//wnd->
		}
		return  0;
	}

	int CEditorContext::QuitEditMode()
	{
		return 0;
	}

	int CEditorContext::ChangeViewMode(const char* s)
	{
		return 0;
	}

	int CEditorContext::ChangeSelMode(const char* s)
	{
		return 0;
	}
}

/*
extern "C" int _EnterEditMode(CFEditor::CEditorContext* ptr, int prm)
{
	return ptr->EnterEditMode(prm);
}

extern "C" int _QuitEditMode(CFEditor::CEditorContext* ptr)
{
	return ptr->QuitEditMode();
}

extern "C" int _ChangeViewMode(CFEditor::CEditorContext* ptr, const char* s)
{
	return ptr->ChangeViewMode(s);
}

extern "C" int _ChangeSelMode(CFEditor::CEditorContext* ptr, const char* s)
{
	return ptr->ChangeSelMode(s);
}
*/