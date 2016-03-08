#ifndef _CF_SCN_NODE_H_
#define _CF_SCN_NODE_H_

#include <vector>
#include "../math/cfMath.h"

namespace CFScn
{
	class CScnNode
	{
	public:
		CScnNode();
		CScnNode(CScnNode* parent); 
		virtual ~CScnNode();

		void SetParent(CScnNode* prnt)
		{
			if (m_pParent)
				return;

			m_pParent = prnt;
			prnt->AddChild(this);
		}

		CScnNode* GetParent(){ return m_pParent; }
		bool AddChild(CScnNode* );
		bool HasChild(CScnNode*, bool itr = false);
		bool DetachChild(CScnNode* chld, bool itr);
		int GetChildCnt()	{ return m_vecChildren.size(); }
		CScnNode* GetChild(int index)
		{
			if (index < 0 || index >= m_vecChildren.size())
				return NULL;
			return m_vecChildren[index];
		}
	protected:
		CScnNode		*m_pParent;

		std::vector<CScnNode*>	m_vecChildren;

		CFMath::Vec3f		m_vPos;

	};
}

#endif