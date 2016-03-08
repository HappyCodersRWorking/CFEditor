#ifndef _EDITOR_CONTEXT_H_
#define _EDITOR_CONTEXT_H_

#include <vector>
#include "../wnd/glWndProxy.h"

namespace CFEditor
{
	class CEditorContext
	{
	public:
		static CEditorContext& Ins()
		{
			static CEditorContext s_ins;
			return s_ins;
		}

		int EnterEditMode( int prm );
		int QuitEditMode();
		int ChangeViewMode( const char* );
		int ChangeSelMode(const char*);
	protected:
		CEditorContext();
		virtual ~CEditorContext();

		typedef std::vector<CFGui::CGLWndProxy*> GLWndPtrArray;
		GLWndPtrArray		m_glWndProxy;
	};
}

#endif