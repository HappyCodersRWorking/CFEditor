#include "InputMngr.h"
#include <assert.h>

extern double g_dSysTime;

namespace CFInput
{
	CInputMngr::CInputMngr()
	{
	}

	CInputMngr::~CInputMngr()
	{
	}

	bool CInputMngr::RegisterEventLsnr(InputEventType tp, InputEventLsnr* lsnr)
	{
		EventLsnrMap::iterator itr = m_mpEventLsnrs.find(tp);
		if (itr == m_mpEventLsnrs.end())
		{
			m_mpEventLsnrs[tp].push_back(lsnr);
		}
		else
		{
			std::vector<InputEventLsnr*>& lsnrs = itr->second;
			if (std::find(lsnrs.begin(), lsnrs.end(), lsnr) == lsnrs.end())
			{
				lsnrs.push_back(lsnr);
			}
			else
			{
				assert( 0 && "RegisterEventLsnr() , conflict ..." );
				return false;
			}
		}

		return true;
	}

	bool CInputMngr::UnRegisterEventLsnr( InputEventType tp, InputEventLsnr* lsnr )
	{
		if (!lsnr)
		{
			assert(0 && "CInputMngr::UnRegisterEventLsnr() , parameter is NULL !!!");
			return false;
		}

		EventLsnrMap::iterator itr = m_mpEventLsnrs.find(tp);
		if (itr == m_mpEventLsnrs.end())
		{
			assert(0 && "CInputMngr::UnRegisterEventLsnr() , NOT FOUND !!!");
			return false;
		}

		std::vector<InputEventLsnr*>& lsnrs = itr->second;

		for (int i = 0; i < lsnrs.size(); i++)
		{
			if (lsnrs[i] == lsnr)
			{
				std::vector<InputEventLsnr*>::iterator tmpI = lsnrs.begin();
				std::advance(tmpI, i);
				lsnrs.erase(tmpI);
				return true;
			}
		}

		return false;
	}

	void CInputMngr::OnMouseDown(int ky, float x, float y, int flg)
	{
		InputEvent ie(MouseDown);
		ie.SetTime(g_dSysTime);
		ie.SetFlg(flg);
		ie.SetMouseBtn(ky);
		ie.SetMousePos(LinearMath::Vec2f(x, y));

		noticeLsnr(ie);

		m_lstInputEvents.push_back(ie);
	}

	void CInputMngr::OnMouseUp(int ky, float x, float y, int flg)
	{
		InputEvent ie(MouseUp);
		ie.SetTime(g_dSysTime);
		ie.SetFlg(flg);
		ie.SetMouseBtn(ky);
		ie.SetMousePos(LinearMath::Vec2f(x, y));

		noticeLsnr(ie);
		
		m_lstInputEvents.push_back(ie);
	}

	void CInputMngr::OnMouseMove(float x, float y, int flg)
	{
		InputEvent ie(MouseUp);
		ie.SetTime(g_dSysTime);
		ie.SetFlg(flg);
		ie.SetMousePos(LinearMath::Vec2f(x, y));

		noticeLsnr(ie);
		
		m_lstInputEvents.push_back(ie);
	}

	void CInputMngr::OnMouseWheel(int delta, float x, float y, int flg)
	{
		InputEvent ie(MouseWheel);
		ie.SetTime(g_dSysTime);
		ie.SetMousePos(LinearMath::Vec2f(x, y));
		ie.SetFlg(flg);
		ie.SetDelta(delta);

		noticeLsnr(ie);
		
		m_lstInputEvents.push_back(ie);
	}

	void CInputMngr::OnKeyDown(int key)
	{
		InputEvent ie(KeyDown);
		ie.SetTime(g_dSysTime);
		ie.SetKey(key);

		noticeLsnr(ie);
		
		m_lstInputEvents.push_back(ie);
	}

	void CInputMngr::OnKeyUp(int key)
	{
		InputEvent ie(KeyUp);
		ie.SetTime(g_dSysTime);
		ie.SetKey(key);

		noticeLsnr(ie);
		
		m_lstInputEvents.push_back(ie);
	}

	void CInputMngr::noticeLsnr(InputEvent ie)
	{
		InputEventType iet = ie.GetType();
		EventLsnrMap::iterator itr = m_mpEventLsnrs.find(iet);
		if (itr == m_mpEventLsnrs.end())
			return;

		std::vector<InputEventLsnr*>& lsnrs = itr->second;
		for (int i = 0; i < lsnrs.size(); i++)
		{
			InputEventLsnr* lsnr = lsnrs[i];
			lsnr->OnInputEvent(ie);
		}
	}
}
