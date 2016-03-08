#ifndef _CF_GL_EDIT_WINDOW_CONTEXT_H_
#define _CF_GL_EDIT_WINDOW_CONTEXT_H_

/*
	GL 窗口编辑状态的上下文
*/

#include <string>
#include <map>
#include <vector>
#include <list>
#include "Editable.h"

namespace CFEditor
{
	class CGLEditWndContext
	{
	public:
		CGLEditWndContext();
		virtual ~CGLEditWndContext();
		void Reset();
	protected:
		std::map<int, std::vector<CEditable> >		m_mpLayer2Editable;
	};
}

#endif