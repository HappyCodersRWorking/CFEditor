#ifndef _CF_INPUT_MANAGER_H_
#define _CF_INPUT_MANAGER_H_

#include "../math/vec2.h"
#include <map>
#include <vector>
#include <list>
#include "InputEventLsnr.h"

namespace CFInput
{

	class CInputMngr
	{
	public:
		static CInputMngr& Ins()
		{
			static CInputMngr s_ins;
			return s_ins;
		}

		void OnMouseDown( int ky , float x , float y , int flg );
		void OnMouseUp(int ky, float x, float y, int flg);
		void OnMouseMove( float x, float y, int flg);
		void OnMouseWheel(int delta, float x, float y, int flg);

		void OnKeyDown(int key);
		void OnKeyUp(int key);

		bool RegisterEventLsnr(InputEventType tp, InputEventLsnr* lsnr );
		bool UnRegisterEventLsnr(InputEventType tp, InputEventLsnr* lsnr);
	protected:
		CInputMngr();
		virtual ~CInputMngr();
		typedef std::map< InputEventType, std::vector<InputEventLsnr*> > EventLsnrMap;
		EventLsnrMap		m_mpEventLsnrs;

		std::list<InputEvent>		m_lstInputEvents;

		void noticeLsnr(InputEvent ie);
	};
}

#endif