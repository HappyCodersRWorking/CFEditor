#ifndef _CF_EDITABLE_MESH_H_
#define _CF_EDITABLE_MESH_H_

#include "../Editable.h"

namespace CFEditor
{
	class CEditableMesh : CEditable
	{
	public:
		CEditableMesh();
		~CEditableMesh();

		virtual void BeginEdit() ;
		virtual void EndEdit() ;
	};
}

#endif