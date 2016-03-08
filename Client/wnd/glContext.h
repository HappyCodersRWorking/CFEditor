#ifndef _CF_GL_CONTEXT_H_
#define _CF_GL_CONTEXT_H_

#include "wx/glcanvas.h"

namespace CFGui
{
	class CFGLContext : public wxGLContext
	{
	public:
		CFGLContext(wxGLCanvas *canvas);

		// render the cube showing it at given angles
		void DrawRotatedCube(float xangle, float yangle);

	private:
		// textures for the cube faces
		GLuint m_textures[6];
	};
}

#endif