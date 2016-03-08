#ifndef _CF_TOOLS_H_
#define _CF_TOOLS_H_

#include <string>
#include <vector>
#include <list>
#include "wx/wx.h"

class CFTools
{
public:
	static int SplitString(const std::string& inS, char ch , std::vector<std::string>&);
	static wxString StdStrToWxStr( const std::string& s );
};

#endif