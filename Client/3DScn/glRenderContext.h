#ifndef _CF_GL_RENDER_CONTEXT_H_
#define _CF_GL_RENDER_CONTEXT_H_

#include "renderContext.h"

namespace CFScn
{
	class CGLRenderContext : public CRenderContext
	{
	public:
		CGLRenderContext(){}
		virtual ~CGLRenderContext(){}
	};
}

#endif