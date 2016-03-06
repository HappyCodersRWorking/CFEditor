#ifndef _CF_MESH_EDIT_EVENT_H_
#define _CF_MESH_EDIT_EVENT_H_

#include "../EditorEvent.h"
#include "EditableMeshDef.h"

/*
	mesh在编辑时候产生的事件
*/

namespace CFEditor 
{
	class CMeshEditEvent : public EditorEvent
	{
	public:
		enum EventType
		{
			SelModeChanged,
			ViewModeChanged,
			SelectCanceled,

			ElementsSelected,
			ElementsDeselected,
			ElementsCreated,
			ElementsMoved,
			ElementsRotated,		// 
			ElementsScaled,			// 
			ElementsDeleted,
		};

		CMeshEditEvent(EditableMeshElementType eleType , EventType tp) 
			:m_eEleType(eleType)
			,m_eEventType(tp){}

	protected:
		EditableMeshElementType		m_eEleType;
		EventType					m_eEventType;
	};
}

#endif