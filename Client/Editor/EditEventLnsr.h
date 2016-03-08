#ifndef _CF_EDIT_EVENT_LSNR_H_
#define _CF_EDIT_EVENT_LSNR_H_

#include "EditorEvent.h"

namespace CFEditor
{
	class EditEvenLsnr
	{
	public:
		virtual void OnEditorEvent(const EditorEvent& evt)=0;
	};
}

#endif