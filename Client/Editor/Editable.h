#ifndef _CF_EDITABLE_H_
#define _CF_EDITABLE_H_

#include <string>
#include <map>
#include <list>
#include "../common/cfObject.h"
#include "../math/cfMath.h"
#include "EditEventLnsr.h"

/*
	CEditable ��Ϊ���пɱ༭����Ļ���
*/

namespace CFEditor
{
	class CEditable : CF::Object
	{
	public:
		CEditable(EditEvenLsnr* lsnr= NULL);
		virtual ~CEditable();

		virtual void BeginEdit() = 0;
		virtual void EndEdit() = 0;
	protected:

		EditEvenLsnr	*m_pEventLnsr;
	};
}

#endif