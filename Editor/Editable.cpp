#include "Editable.h"

namespace CFEditor
{
	CEditable::CEditable(EditEvenLsnr* lsnr)
		:m_pEventLnsr(lsnr)
	{
	}

	CEditable::~CEditable()
	{
	}
}