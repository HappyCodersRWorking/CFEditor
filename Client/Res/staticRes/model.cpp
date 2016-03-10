#include "model.h"
#include "../../tinyxml/tinyxml.h"
#include "../../logger/logger.h"

namespace CFStaticRes
{
	CModel::CModel(){}
	CModel::~CModel(){}

	bool CModel::FromXml( const char* fn )
	{
		TiXmlDocument doc;
		if (!doc.LoadFile(fn))
		{
			CF::CLogger::Ins().LogErr( "CModel::FromXml failed: " , fn );
			return false;
		}

		return true;
	}

	bool CModel::ToXml(const char* fn)
	{
		TiXmlDocument doc;




		if (!doc.SaveFile(fn))
		{
			CF::CLogger::Ins().LogErr("CModel::ToXml failed: ", fn);
			return false;
		}

		return true;
	}

	bool CModel::FromBinaryFile(const char* fn)
	{
		FILE* pf = fopen(fn, "rb");
		if (!pf)
		{
			CF::CLogger::Ins().LogErr("CModel::FromBinaryFile failed: ", fn);
			return false;
		}


		fclose(pf);
		return true;
	}

	bool CModel::ToBinaryFile(const char* fn)
	{
		FILE* pf = fopen(fn, "wb+");
		if (!pf)
		{
			CF::CLogger::Ins().LogErr("CModel::ToBinaryFile failed: ", fn);
			return false;
		}


		fclose(pf);
		return true;
	}

}