#include "tools.h"

int CFTools::SplitString( const std::string& inS , char ch , std::vector<std::string>& outLst )
{
	int p = 0;
	std::string ts = inS;
	std::string tmp = "";
	while ((p = ts.find(ch)) != std::string::npos)
	{
		tmp = ts.substr( 0 , p );
		outLst.push_back(tmp);
		ts = ts.substr(p + 1);
	}

	outLst.push_back(ts);

	return outLst.size();
}

wxString CFTools::StdStrToWxStr(const std::string& s)
{
	wxString v(s.c_str());
	return v;
}
