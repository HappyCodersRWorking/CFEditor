#ifndef _CF_EDITALBLE_MESH_DEF_H_
#define _CF_EDITALBLE_MESH_DEF_H_

namespace CFEditor
{
	class EditableMeshElementType
	{
	public:
		enum ElementType
		{
			ET_VERTEX,
			ET_EDGE,
			ET_FACE,
			ET_ENTITY,
			ET_MESH,
		};
	};
	// view mode .
	class EditableMeshViewMode
	{
	public:
		enum Mode
		{
			VM_OBJECT,
			VM_ENTITY,
			VM_FACE,
			VM_EDGE,
			VM_VERTEX,
		};
	};

	// select mode .
	class EditableMeshSelectMode
	{
	public:
		enum Mode
		{
			SM_OBJECT,
			SM_ENTITY,
			SM_FACE,
			SM_EDGE,
			SM_VERTEX,
		};
	};
}

#endif