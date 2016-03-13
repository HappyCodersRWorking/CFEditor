#include "stdio.h"
#include "stdlib.h"
#include "model.h"
#include <string>
#include "../../tinyxml/tinyxml.h"
#include "../../logger/logger.h"
#include "../../common/tiny_str.h"
#include "../../common/tools.h"

namespace CFStaticRes
{
	CModelDataBlock_Vec3f::CModelDataBlock_Vec3f()
	{
	}

	CModelDataBlock_Vec3f::~CModelDataBlock_Vec3f()
	{
	}

	void CModelDataBlock_Vec3f::SetData(std::vector<CFMath::Vec3f>* data)
	{
		if (!data)
			return;

		m_values.clear();
		m_values.assign(data->begin(), data->end());
	}

	int CModelDataBlock_Vec3f::WriteToFile(FILE* f)
	{
		if (!f)
			return 0;

		fwrite(m_4ByteFlag, 4, 1, f);

		int typeFlg = 0;						// mins float .
		int subFlg = 0;						// reserved .
		int dataLen = m_values.size() * 3;		// count of float ...

		fwrite(&typeFlg, sizeof(int), 1, f);
		fwrite(&subFlg, sizeof(int), 1, f);

		/*
		float* flts = new float[dataLen];
		for (int i = 0; i < m_posArray.size(); i++)
		{
		flts[i * 3] = m_posArray[i].X();
		flts[i * 3 + 1] = m_posArray[i].Y();
		flts[i * 3 + 2] = m_posArray[i].Z();
		}
		*/

		fwrite(&(m_values[0]), sizeof(float)* m_values.size() * 3, 1, f);

		return 4 + 3 * sizeof(int)+m_values.size() * 3 * sizeof(float);
	}

	int CModelDataBlock_Vec3f::ReadFromFile(FILE* f)
	{
		if (!f)
			return 0;

		char buf[4];

		fread(buf, 4, 1, f);
		if (buf[0] == 'P' && buf[1] == 'O' && buf[2] == 'S' && buf[3] == 'I')
		{
			CF::CLogger::Ins().LogMsg("CModelDataBlock_Pos::ReadFromFile(...)");
		}
		else
		{
			CF::CLogger::Ins().LogMsg("CModelDataBlock_Pos::ReadFromFile(...)", "string flag is wrong .");
			::fseek(f, -4, SEEK_CUR);
			return 0;
		}

		int tpFlg = 0;
		int subFlg = 0;
		int cnt = 0;

		fread(&tpFlg, 4, 1, f);
		fread(&subFlg, 4, 1, f);
		fread(&cnt, 4, 1, f);

		if (tpFlg != 0 || subFlg != 0 || cnt < 0)
		{
			CF::CLogger::Ins().LogMsg("CModelDataBlock_Pos::ReadFromFile(...)", "type flag / subflag / data length is wrong .");
			::fseek(f, -(4 + 3 * sizeof(int)), SEEK_CUR);
			return 0;
		}

		m_values.clear();

		float* flts = new float[cnt];
		fread(flts, cnt * sizeof(float), 1, f);

		CFMath::Vec3f vPos;
		int posCnt = cnt / 3;
		for (int i = 0; i < posCnt; i++)
		{
			vPos.Set(flts[i * 3], flts[i * 3 + 1], flts[i * 3 + 2]);
			m_values.push_back(vPos);
		}

		delete[]flts;

		return 4 + 3 * sizeof(int)+cnt * sizeof(float);
	}

	int CModelDataBlock_Vec3f::WriteToXml(TiXmlElement* parent)
	{
		if (!parent)
			return 0;

		char tmpBf[256];

		TiXmlElement* valueRoot = new TiXmlElement(m_4ByteFlag);
		parent->LinkEndChild(valueRoot);

		for (int i = 0; i < m_values.size(); i++)
		{
			TiXmlElement* valEle = new TiXmlElement("v");
			valueRoot->LinkEndChild(valEle);

			sprintf_s(tmpBf, 250, "%0.5f", m_values[i].X());
			valEle->SetAttribute("x", tmpBf);

			sprintf_s(tmpBf, 250, "%0.5f", m_values[i].Y());
			valEle->SetAttribute("y", tmpBf);

			sprintf_s(tmpBf, 250, "%0.5f", m_values[i].Z());
			valEle->SetAttribute("z", tmpBf);
		}

		return m_values.size();
	}

	int CModelDataBlock_Vec3f::ReadFromXml(TiXmlElement* parent)
	{
		if (!parent)
			return 0;

		TiXmlElement* valRoot = parent->FirstChildElement(m_4ByteFlag);
		if (!valRoot)
		{
			return 0;
		}

		m_values.clear();

		float x, y, z;

		TiXmlElement* valEle = valRoot->FirstChildElement();
		while (valEle)
		{
			valEle->QueryFloatAttribute("x", &x);
			valEle->QueryFloatAttribute("y", &y);
			valEle->QueryFloatAttribute("z", &z);

			CFMath::Vec3f v(x, y, z);
			m_values.push_back(v);

			valEle = valEle->NextSiblingElement();
		}

		return m_values.size();
	}

	CModelDataBlock_Pos::CModelDataBlock_Pos()
	{
		memcpy(m_4ByteFlag, "POSI", 4);
	}

	CModelDataBlock_Pos::~CModelDataBlock_Pos(){}

	CModelDataBlock_Nor::CModelDataBlock_Nor()
	{
		memcpy(m_4ByteFlag, "NORM", 4);
	}

	CModelDataBlock_Nor::~CModelDataBlock_Nor()
	{
	}

	CModelDataBlock_Tan::CModelDataBlock_Tan()
	{
		memcpy(m_4ByteFlag, "TANG", 4);
	}

	CModelDataBlock_Tan::~CModelDataBlock_Tan()
	{
	}

	/////////////////////////////////////
	CModelDataBlock_Vec4f::CModelDataBlock_Vec4f()
	{

	}

	CModelDataBlock_Vec4f::~CModelDataBlock_Vec4f()
	{
	}

	void CModelDataBlock_Vec4f::SetData(std::vector<CFMath::Vec4f>*)
	{
	}

	int CModelDataBlock_Vec4f::WriteToFile(FILE*)
	{
	}

	int CModelDataBlock_Vec4f::ReadFromFile(FILE*)
	{
	}

	int CModelDataBlock_Vec4f::WriteToXml(TiXmlElement* parent)
	{
	}

	int CModelDataBlock_Vec4f::ReadFromXml(TiXmlElement* parent)
	{
	}

	/////////////////////////////////////
	CModelDataBlock_Color::CModelDataBlock_Color()
	{
		memcpy(m_4ByteFlag, "CLR_", 4);
	}

	CModelDataBlock_Color::~CModelDataBlock_Color()
	{
	}

	/////////////////////////////////////
	CModelDataBlock_UV::CModelDataBlock_UV()
	{
		memcpy(m_4ByteFlag, "_UV_", 4);
	}

	CModelDataBlock_UV::~CModelDataBlock_UV()
	{
	}

	void CModelDataBlock_UV::SetData(int layer, std::vector<CFMath::Vec2f>* vals)
	{
		if (layer < 0 || layer >= LayerCnt)
			return;

		m_values[layer].clear();
		m_values[layer].assign(vals->begin(), vals->end());
	}

	int CModelDataBlock_UV::WriteToFile(FILE* f)
	{
		if (!f)
			return 0;

		fwrite(m_4ByteFlag, 4, 1, f);

		int typeFlg = 0;							// mins float .
		int subFlg = 0;								// reserved .
		int dataLen = m_values[0].size() * 4;		// count of float every layer ...

		fwrite(&typeFlg, sizeof(int), 1, f);
		fwrite(&subFlg, sizeof(int), 1, f);

		/*
		float* flts = new float[dataLen];
		for (int i = 0; i < m_posArray.size(); i++)
		{
		flts[i * 3] = m_posArray[i].X();
		flts[i * 3 + 1] = m_posArray[i].Y();
		flts[i * 3 + 2] = m_posArray[i].Z();
		}
		*/

		for (int i = 0; i < LayerCnt; i++)
		{
			fwrite(&(m_values[i][0]), sizeof(float)* dataLen, 1, f);
		}

		return 4 + 3 * sizeof(int)+dataLen * sizeof(float)* LayerCnt;
	}

	int CModelDataBlock_UV::ReadFromFile(FILE* f)
	{
		if (!f)
			return 0;

		char buf[4];

		fread(buf, 4, 1, f);
		if (buf[0] == '_' && buf[1] == 'U' && buf[2] == 'V' && buf[3] == '_')
		{
			CF::CLogger::Ins().LogMsg("CModelDataBlock_UV::ReadFromFile(...)");
		}
		else
		{
			CF::CLogger::Ins().LogMsg("CModelDataBlock_UV::ReadFromFile(...)", "string flag is wrong .");
			::fseek(f, -4, SEEK_CUR);
			return 0;
		}

		int tpFlg = 0;
		int subFlg = 0;
		int cnt = 0;

		fread(&tpFlg, 4, 1, f);
		fread(&subFlg, 4, 1, f);
		fread(&cnt, 4, 1, f);

		if (tpFlg != 0 || subFlg != 0 || cnt < 0)
		{
			CF::CLogger::Ins().LogMsg("CModelDataBlock_UV::ReadFromFile(...)", "type flag / subflag / data length is wrong .");
			::fseek(f, -(4 + 3 * sizeof(int)), SEEK_CUR);
			return 0;
		}

		for (int i = 0; i < LayerCnt; i++)
			m_values[i].clear();

		float* flts = new float[cnt];
		fread(flts, cnt * sizeof(float), 1, f);

		CFMath::Vec2f clr;
		int clrCnt = cnt / LayerCnt / 2;
		for (int i = 0; i < clrCnt; i++)
		{
			float* cur = flts;
			cur += i * LayerCnt * 2;

			for (int jj = 0; jj < LayerCnt; jj++)
			{
				clr.Set(cur[jj * 2], cur[jj * 2 + 1]);
				m_values[jj].push_back(clr);
			}
		}

		delete[]flts;

		return 4 + 3 * sizeof(int)+cnt * sizeof(float);
	}

	int CModelDataBlock_UV::WriteToXml(TiXmlElement* parent)
	{
		if (!parent)
			return 0;

		TiXmlElement* valRoot = new TiXmlElement(m_4ByteFlag);
		parent->LinkEndChild(valRoot);

		char bf[64];

		for (int i = 0; i < LayerCnt; i++)
		{
			sprintf_s(bf, 64, "Layer_%d", i);
			TiXmlElement* layerEle = new TiXmlElement(bf);
			valRoot->LinkEndChild(layerEle);

			for (int jj = 0; jj < m_values[i].size(); jj++)
			{
				TiXmlElement* ele = new TiXmlElement("clr");
				layerEle->LinkEndChild(ele);

				sprintf_s(bf, 64, "%0.5f", m_values[i][jj].X());
				ele->SetAttribute("u", bf);

				sprintf_s(bf, 64, "%0.5f", m_values[i][jj].Y());
				ele->SetAttribute("v", bf);
			}
		}

		return m_values[0].size();
	}

	int CModelDataBlock_UV::ReadFromXml(TiXmlElement* parent)
	{
		if (!parent)
			return 0;

		TiXmlElement* rt = parent->FirstChildElement(m_4ByteFlag);
		if (!rt)
		{
			CF::CLogger::Ins().LogErr("CModelDataBlock_UV::ReadFromXml(...) , value root not found : ", m_4ByteFlag);
			return 0;
		}

		//
		for (int i = 0; i < LayerCnt; i++)
			m_values[i].clear();

		//
		CFMath::Vec2f	val;
		float u, v;
		TiXmlElement* layerEle = rt->FirstChildElement();
		int curLyr = 0;
		while (layerEle)
		{
			TiXmlElement* valEle = layerEle->FirstChildElement();
			while (valEle)
			{
				valEle->QueryFloatAttribute("u", &u);
				valEle->QueryFloatAttribute("v", &v);
				val.Set(u, v);

				m_values[curLyr].push_back(val);

				valEle = valEle->NextSiblingElement();
			}

			layerEle = layerEle->NextSiblingElement();
			curLyr++;
			if (curLyr >= LayerCnt)
				break;
		}

		return m_values[0].size();
	}

	/////////////////////////////////////

	CModel::CModel(){}
	CModel::~CModel(){}

	bool CModel::FromXml(const char* fn)
	{
		TiXmlDocument doc;
		if (!doc.LoadFile(fn))
		{
			CF::CLogger::Ins().LogErr("CModel::FromXml failed: ", fn);
			return false;
		}

		return true;
	}

	bool CModel::ToXml(const char* fn)
	{
		TiXmlDocument doc;

		char buf[256];
		CF::CTiStrA s("Model");
		s += _itoa_s(m_nEditionNum, buf, 250, 10);

		TiXmlElement* pRoot = new TiXmlElement(s.GetPtr());
		doc.LinkEndChild(pRoot);

		//
		CModelDataBlock_Pos posiBlk;
		posiBlk.SetData(&m_vertPos);

		CModelDataBlock_Nor normBlk;
		normBlk.SetData(&m_vertNor);

		CModelDataBlock_Tan tangBlk;
		tangBlk.SetData(&m_vertTan);

		if (!doc.SaveFile(fn))
		{
			CF::CLogger::Ins().LogErr("CModel::ToXml failed: ", fn);
			return false;
		}

		return true;
	}

	bool CModel::FromBinaryFile(const char* fn)
	{
		FILE* pf = NULL;
		errno_t err = fopen_s(&pf, fn, "rb");
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
		FILE* pf = NULL;
		fopen_s( &pf , fn, "wb+");
		if (!pf)
		{
			CF::CLogger::Ins().LogErr("CModel::ToBinaryFile failed: ", fn);
			return false;
		}


		fclose(pf);
		return true;
	}

	int CModel::_readBoneWeightFromFile(FILE* f)
	{
		char strFlg[5] = { ' ', ' ', ' ', ' ', 0 };
		fread(strFlg, 4, 1, f);
		if (strFlg[0] == 'B' && strFlg[1] == 'O' && strFlg[2] == 'W' && strFlg[3] == 'E')
		{

		}
		else
		{
			CF::CLogger::Ins().LogErr("CModel::_readBoneWeightFromFile(...) , 4 bytes' flag is wrong : ", strFlg);
			fseek(f, -4, SEEK_CUR);
			return 0;
		}

		int flg = 0;
		int subFlg = 0;
		int cnt = 0;

		fread(&flg, sizeof(int), 1, f);
		fread(&subFlg, sizeof(int), 1, f);
		fread(&cnt, sizeof(int), 1, f);

		char bf[256];
		if (cnt < 0)
		{
			sprintf_s(bf, 250, "%d , %d , %d", flg, subFlg, cnt);
			CF::CLogger::Ins().LogErr("CModel::_readBoneWeightFromFile(...) , flg/subFlg/cnt is wrong : ", bf);
			fseek(f, -(4 + 3 * sizeof(int)), SEEK_CUR);
			return 0;
		}

		m_boneWeights.clear();

		VertBoneWeight* data = new VertBoneWeight[cnt];
		fread(data, sizeof(VertBoneWeight)* cnt, 1, f);

		for (int i = 0; i < cnt; i++)
			m_boneWeights.push_back(data[i]);

		delete[] data;

		return cnt;
	}

	int CModel::_writeBoneWeightToFile(FILE* f)
	{
		if (!f)
		{
			CF::CLogger::Ins().LogErr("CModel::_writeBoneWeightToFile(...) input FILE*  is NULL.");
			return 0;
		}

		char chFlg[4] = { 'B', 'O', 'W', 'E' };
		int flg = 0;
		int subFlg = 0;
		int cnt = m_boneWeights.size();

		fwrite(chFlg, 4, 1, f);
		fwrite(&flg, sizeof(int), 1, f);
		fwrite(&subFlg, sizeof(int), 1, f);
		fwrite(&cnt, sizeof(int), 1, f);

		fwrite(&(m_boneWeights[0]), sizeof(VertBoneWeight)* m_boneWeights.size(), 1, f);

		return 4 + 3 * sizeof(int)+sizeof(VertBoneWeight)* m_boneWeights.size();
	}

	int CModel::_readBoneWeightFromXml(TiXmlElement* parent)
	{
		if (!parent)
		{
			CF::CLogger::Ins().LogErr("CModel::_readBoneWeightFromXml(...) parent node is NULL.");
			return 0;
		}

		TiXmlElement* bwRoot = parent->FirstChildElement("BOWE");
		if (!bwRoot)
		{
			CF::CLogger::Ins().LogErr("CModel::_readBoneWeightFromXml(...) bone weight's node not found.");
			return 0;
		}

		m_boneWeights.clear();

		TiXmlElement* vertEle = bwRoot->FirstChildElement();
		while (vertEle)
		{
			int ind = 0;
			vertEle->QueryIntAttribute("index", &ind);

			VertBoneWeight vbw;

			int boneId = 0;
			float weightVal = 0.0f;

			int weightInd = 0;
			TiXmlElement *weightEle = vertEle->FirstChildElement();
			while (weightEle)
			{
				weightEle->QueryIntAttribute("boneIndex", &boneId);
				weightEle->QueryFloatAttribute("weight", &weightVal);

				vbw.boneID[weightInd] = boneId;
				vbw.weight[weightInd] = weightVal;

				weightEle = weightEle->NextSiblingElement();
				weightInd++;
				if (weightInd >= MAX_BONE_PER_VERT)
					break;
			}

			m_boneWeights.push_back(vbw);

			vertEle = vertEle->NextSiblingElement();
		}

		return 1;
	}

	int CModel::_writeBoneWeightToXml(TiXmlElement* parent)
	{
		if (!parent)
		{
			CF::CLogger::Ins().LogErr("CModel::_writeBoneWeightToXml(...) parent node is NULL.");
			return 0;
		}

		char bf[256];

		TiXmlElement* bwRoot = new TiXmlElement("BOWE");
		parent->LinkEndChild(bwRoot);

		for (int i = 0; i < m_boneWeights.size(); i++)
		{
			TiXmlElement* vertEle = new TiXmlElement("vert");
			bwRoot->LinkEndChild(vertEle);

			vertEle->SetAttribute("index", i);

			for (int jj = 0; jj < MAX_BONE_PER_VERT; jj++)
			{
				VertBoneWeight& vbw = m_boneWeights[jj];

				TiXmlElement* weightEle = new TiXmlElement("Value");
				weightEle->SetAttribute("boneIndex", vbw.boneID[jj]);

				sprintf_s(bf, 250, "%0.5f", vbw.weight[jj]);
				weightEle->SetAttribute("weight", bf);
			}
		}

		return m_boneWeights.size();
	}

	int CModel::_writeFileHeadToXml( TiXmlElement* parent )
	{
		if (!parent)
		{
			CF::CLogger::Ins().LogErr("CModel::_writeFileHeadToXml(...) parent node is NULL.");
			return 0;
		}

		TiXmlElement* headEle = new TiXmlElement("FileHead") ;
		parent->LinkEndChild( headEle ) ;

		headEle->SetAttribute( "StringFlag" , m_fileHead.strFlg ) ;
		headEle->SetAttribute( "Edition" , m_fileHead.nEdition ) ;
		headEle->SetAttribute( "Author" , m_fileHead.author ) ;
		headEle->SetAttribute( "Description" , m_fileHead.description ) ;

		char buf[256] ;
		sprintf_s( buf , "%d_%d_%d_%d_%d_%d_%d" , 
			m_fileHead.year , m_fileHead.month , m_fileHead.day ,
			m_fileHead.hour , m_fileHead.minutes , 
			m_fileHead.second , m_fileHead.miniSec ) ;

		headEle->SetAttribute("Date", buf) ;

		return 1 ;
	}

	int CModel::_readFileHeadFromXml( TiXmlElement* parent )
	{
		if (!parent)
		{
			CF::CLogger::Ins().LogErr("CModel::_readFileHeadFromXml(...) parent node is NULL.");
			return 0;
		}

		TiXmlElement* headEle = parent->FirstChildElement("FileHead");
		if (!headEle)
		{
			CF::CLogger::Ins().LogErr("CModel::_readFileHeadFromXml(...) , FileHead node is not found .");
			return 0;
		}

		const char* strFlg = headEle->Attribute("StringFlag") ;
		if( strncmp( strFlg , "MODL" , 4 ) != 0 )
		{
			CF::CLogger::Ins().LogErr("CModel::_readFileHeadFromXml(...) , StringFlag is wrong .") ;
			return 0 ;
		}

		headEle->QueryIntAttribute("Edition", &(m_fileHead.nEdition));
		
		const char* author = headEle->Attribute("Author");
		strncpy_s(m_fileHead.author, 32, author, 32);

		const char* desc = headEle->Attribute("Description") ;
		strncpy_s( m_fileHead.description , 128 , desc , 128 ) ;

		const char* date = headEle->Attribute("Date") ;
		std::string ts = date;

		std::vector<std::string>		outS;
		int c = CFTools::SplitString(ts, '_', outS);
		if (c != 7)
		{
			CF::CLogger::Ins().LogWrn( "CModel::_readFileHeadFromXml(...) date string is wrong ." ,
				ts.c_str() );
		}

		for (int i = 0; i < outS.size(); i++)
		{
			if (i == 0)		m_fileHead.year = atoi(outS[i].c_str());
			if (i == 1)		m_fileHead.month = atoi(outS[i].c_str());
			if (i == 2)		m_fileHead.day = atoi(outS[i].c_str());
			if (i == 3)		m_fileHead.hour = atoi(outS[i].c_str());
			if (i == 4)		m_fileHead.minutes = atoi(outS[i].c_str());
			if (i == 5)		m_fileHead.second = atoi(outS[i].c_str());
			if (i == 6)		m_fileHead.miniSec = atoi(outS[i].c_str());
		}

		return 1;
	}
}