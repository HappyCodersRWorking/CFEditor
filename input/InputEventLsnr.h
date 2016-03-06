#ifndef _INPUT_EVENT_LSNR_H_
#define _INPUT_EVENT_LSNR_H_

#include "inputEvent.h"

namespace CFInput
{
	class InputEventLsnr
	{
	public:
		virtual void OnInputEvent(const InputEvent&) = 0;
	};
}

#endif