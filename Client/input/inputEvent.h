#ifndef _CF_INPUT_EVENT_H_
#define _CF_INPUT_EVENT_H_

#include "../math/vec2.h"

namespace CFInput
{
	enum InputEventType
	{
		MouseDown,
		MouseUp,
		MouseMove,
		MouseWheel,
		KeyDown,
		KeyUp,
	};

	class InputEvent
	{
	protected:
		double				dTime;
		InputEventType		eType;
		LinearMath::Vec2f	vMousePos;
		int					nMouseBtn;
		int					nKey;
		int					nFlg;
		int					nDelta;

	public:
		InputEvent(){}
		InputEvent(InputEventType tp) :eType(tp){}
		const InputEvent& operator=(const InputEvent& o)
		{
			dTime = o.dTime;
			eType = o.eType;
			vMousePos = o.vMousePos;
			nMouseBtn = o.nMouseBtn;
			nKey = o.nKey;
			nFlg = o.nFlg;
			nDelta = o.nDelta;

			return *this;
		}

		double GetTime() const	{ return dTime; }
		void SetTime(double val)	{ dTime = val; }

		InputEventType GetType() const { return  eType; }
		void SetType(InputEventType tp)	{ eType = tp; }

		LinearMath::Vec2f GetMousePos() const { return vMousePos; }
		void SetMousePos(const LinearMath::Vec2f& val) { vMousePos = val; }

		int GetMouseBtn()	const { return nMouseBtn; }
		void SetMouseBtn(int val)	{ nMouseBtn = val; }

		int GetKey()	const	{ return nKey; }
		void SetKey(int ky)	{ nKey = ky; }

		int GetFlg()	const	{ return nFlg; }
		void SetFlg(int val)	{ nFlg = val; }

		int GetDelta()	const	{ return nDelta; }
		void SetDelta(int val)	{ nDelta = val; }
	};
}

#endif