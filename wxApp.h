#ifndef _CF_WX_APP_H_
#define _CF_WX_APP_H_

#include<wx/wx.h>

class CFEditorApp: public wxApp
{
public:
	virtual bool OnInit();
	virtual bool ProcessIdle() ;
protected:
	wxFrame	*m_pMainFrm;
};

//DECLARE_APP(CFEditorApp)
#endif