#include "scnNode.h"

namespace CFScn
{
	CScnNode::CScnNode()
	{}

	CScnNode::CScnNode(CScnNode* parent)
	:m_pParent(parent){}

	CScnNode::~CScnNode()
	{
	}

	bool CScnNode::AddChild(CScnNode* ptr)
	{
		if (HasChild(ptr, true))
			return false;

		ptr->SetParent(this);
		m_vecChildren.push_back(ptr);

		return true;
	}
	
	bool CScnNode::HasChild(CScnNode* ptr, bool itr )
	{
		if (!itr)
		{
			for (int i = 0; i < m_vecChildren.size(); i++)
			{
				if (m_vecChildren[i] == ptr)
					return true;
			}

			return false;
		}

		for (int i = 0; i < m_vecChildren.size(); i++)
		{
			if (m_vecChildren[i] == ptr)
				return true;

			if( m_vecChildren[i]->HasChild(ptr, true) )
				return true;
		}

		return false;
	}

	bool CScnNode::DetachChild( CScnNode* chld, bool itr )
	{
		if (!itr)
		{
			for (int i = 0; i < m_vecChildren.size(); i ++ )
			{
				if (m_vecChildren[i] == chld)
				{
					std::vector<CScnNode*>::iterator itr = m_vecChildren.begin();
					std::advance(itr, i);
					m_vecChildren.erase(itr);
					chld->SetParent(NULL);
					return true ;
				}
			}

			return false ;
		}

		for (int i = 0; i < m_vecChildren.size(); i++)
		{
			if (m_vecChildren[i] == chld)
			{
				std::vector<CScnNode*>::iterator itr = m_vecChildren.begin();
				std::advance(itr, i);
				m_vecChildren.erase(itr);
				chld->SetParent(NULL);
				return true;
			}

			if (m_vecChildren[i]->DetachChild(chld, true))
				return true;
		}

		return false ;
	}
}
