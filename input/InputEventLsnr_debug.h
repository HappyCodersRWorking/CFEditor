#ifndef _INPUT_EVENT_LSNR_DEBUG_H_
#define _INPUT_EVENT_LSNR_DEBUG_H_

#include "stdlib.h"
#include "stdio.h"
#include "InputEventLsnr.h"

namespace CFInput
{
	class InputEventLsnr_Debug :public InputEventLsnr
	{
	public:
		virtual void OnInputEvent(const InputEvent& ie)
		{
			printf("InputEvent : %d\n", ie.GetType());
		}
	};
}

#endif