#include "scnMngr.h"

namespace CFScn
{
	CScnMngr::CScnMngr() :m_pRootNode(NULL)
	{
	}
	
	CScnMngr::~CScnMngr()
	{
	}

	bool CScnMngr::Init()
	{
		if (!m_pRootNode)
			m_pRootNode = new CScnNode();

		return true;
	}

	void CScnMngr::Render(CRenderContext* cntxt)
	{
		if (!m_pRootNode)
			return;

		m_pRootNode->Render(cntxt);
	}
}