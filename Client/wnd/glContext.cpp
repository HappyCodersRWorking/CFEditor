#include "glContext.h"

static void CheckGLError()
{
	GLenum errLast = GL_NO_ERROR;

	for (;;)
	{
		GLenum err = glGetError();
		if (err == GL_NO_ERROR)
			return;

		// normally the error is reset by the call to glGetError() but if
		// glGetError() itself returns an error, we risk looping forever here
		// so check that we get a different error than the last time
		if (err == errLast)
		{
			wxLogError(wxT("OpenGL error state couldn't be reset."));
			return;
		}

		errLast = err;

		wxLogError(wxT("OpenGL error %d"), err);
	}
}

namespace CFGui
{
	CFGLContext::CFGLContext(wxGLCanvas *canvas)
	: wxGLContext(canvas)
	{
		SetCurrent(*canvas);

		// set up the parameters we want to use
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_TEXTURE_2D);

		// add slightly more light, the default lighting is rather dark
		GLfloat ambient[] = { 0.5, 0.5, 0.5, 0.5 };
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

		// set viewing projection
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-0.5f, 0.5f, -0.5f, 0.5f, 1.0f, 3.0f);

		// create the textures to use for cube sides: they will be reused by all
		// canvases (which is probably not critical in the case of simple textures
		// we use here but could be really important for a real application where
		// each texture could take many megabytes)
		glGenTextures(WXSIZEOF(m_textures), m_textures);

		for (unsigned i = 0; i < WXSIZEOF(m_textures); i++)
		{
			glBindTexture(GL_TEXTURE_2D, m_textures[i]);

			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			/*
			const wxImage img(DrawDice(256, i + 1));

			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.GetWidth(), img.GetHeight(),
				0, GL_RGB, GL_UNSIGNED_BYTE, img.GetData());*/
		}

		CheckGLError();
	}

	void CFGLContext::Paint()
	{
		m_scnMngr.Render(&m_glRenderContext);
	}
}
