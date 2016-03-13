#ifndef _CF_RES_MODEL_H_
#define _CF_RES_MODEL_H_

#include <vector>
#include "../../math/cfMath.h"
#include "../../tinyxml/tinyxml.h"

namespace CFStaticRes
{
	class CModelDataBlock
	{
	public:
		CModelDataBlock(){}
		virtual ~CModelDataBlock(){}
		virtual int WriteToFile(FILE*) = 0;
		virtual int ReadFromFile(FILE*) = 0;

		virtual int WriteToXml(TiXmlElement* parent)= 0;
		virtual int ReadFromXml(TiXmlElement* parent) = 0;

		const char* TypeFlag4Bytes() { return m_4ByteFlag ; }
	protected:

		char		m_4ByteFlag[4];
	};

	class CModelDataBlock_Vec3f : public CModelDataBlock
	{
	public:
		CModelDataBlock_Vec3f();
		virtual ~CModelDataBlock_Vec3f();
		virtual void SetData(std::vector<CFMath::Vec3f>*);
		virtual int WriteToFile(FILE*);
		virtual int ReadFromFile(FILE*) ;
		virtual int WriteToXml(TiXmlElement* parent) ;
		virtual int ReadFromXml(TiXmlElement* parent) ;
		virtual int GetValueCnt(){ return m_values.size(); }
		CFMath::Vec3f* GetValue(int ind)
		{
			if (ind < 0 || ind >= m_values.size())
				return NULL;

			return &(m_values[ind]);
		}
	protected:
		std::vector<CFMath::Vec3f>		m_values;
	};

	//
	class CModelDataBlock_Pos : public CModelDataBlock_Vec3f
	{
	public:
		CModelDataBlock_Pos();
		virtual ~CModelDataBlock_Pos();
	protected:
	};

	//
	class CModelDataBlock_Nor : public CModelDataBlock_Vec3f
	{
	public:
		CModelDataBlock_Nor();
		virtual ~CModelDataBlock_Nor();
	protected:
	};

	class CModelDataBlock_Tan : public CModelDataBlock_Vec3f
	{
	public:
		CModelDataBlock_Tan();
		virtual ~CModelDataBlock_Tan();
	protected:
	};

	////
	class CModelDataBlock_Vec4f : public CModelDataBlock
	{
	public:
		CModelDataBlock_Vec4f();
		virtual ~CModelDataBlock_Vec4f();
		virtual void SetData(std::vector<CFMath::Vec4f>*);
		virtual int WriteToFile(FILE*);
		virtual int ReadFromFile(FILE*);
		virtual int WriteToXml(TiXmlElement* parent);
		virtual int ReadFromXml(TiXmlElement* parent);
		virtual int GetEleCnt()	{ return m_values.size(); }
		CFMath::Vec4f* GetValue(int ind)
		{
			if (ind < 0 || ind >= m_values.size())
				return NULL;
			return &(m_values[ind]);
		}
	protected:
		std::vector<CFMath::Vec4f>		m_values;
	};

	class CModelDataBlock_Color : public CModelDataBlock_Vec4f
	{
	public:
		CModelDataBlock_Color();
		virtual ~CModelDataBlock_Color();
	protected:
	};

	class CModelDataBlock_UV : public CModelDataBlock
	{
	public:
		CModelDataBlock_UV();
		virtual ~CModelDataBlock_UV();
		virtual void SetData(int layer , std::vector<CFMath::Vec2f>*);
		virtual int WriteToFile(FILE*);
		virtual int ReadFromFile(FILE*);
		virtual int WriteToXml(TiXmlElement* parent);
		virtual int ReadFromXml(TiXmlElement* parent);
		virtual int GetEleCnt()	{ return m_values[0].size(); }
		CFMath::Vec2f* GetValue( int layer , int ind)
		{
			if (layer < 0 || layer >= LayerCnt)
				return NULL;

			if (ind < 0 || ind >= m_values[0].size())
				return NULL;

			return &(m_values[layer][ind]);
		}
		static const int LayerCnt = 4;
	protected:
		std::vector<CFMath::Vec2f>		m_values[LayerCnt];
	};

	/////////////////////////////////////////////////////////////////////
	struct ModelFileHead
	{
		char		strFlg[4] ;	// must be "MODL" ...
		int			nEdition ;	// edition ...
		unsigned short	year;	//
		char	month;
		char	day;
		char	hour;
		char	minutes;
		char	second;
		unsigned short miniSec;

		static const int AUTHOR_NAME_LEN = 32;
		char	author[AUTHOR_NAME_LEN];
		static const int DESC_LEN = 128;
		char	description[DESC_LEN];

		ModelFileHead()
		{
			strFlg[0] = 'M' ;
			strFlg[1] = 'O' ;
			strFlg[2] = 'D' ;
			strFlg[3] = 'L' ;

			nEdition = 1001 ;

			memset( author , 0 , AUTHOR_NAME_LEN ) ;
			memset( description , 0 , DESC_LEN ) ;
		}
	};

	/////////////////////////////////////////////////////////////////////
	class CModel
	{
	public:
		class TriangleInfo
		{
			int ind[3];
		};

		class TriangleGroup
		{
			std::vector<TriangleInfo>		m_triangles;
		};

		static const int MAX_BONE_PER_VERT = 8;
		struct VertBoneWeight
		{
			int		boneID[MAX_BONE_PER_VERT];
			float	weight[MAX_BONE_PER_VERT];
		};

		CModel();
		virtual ~CModel();

		bool FromXml( const char* fn );
		bool ToXml(const char* fn);

		bool FromBinaryFile(const char* fn);
		bool ToBinaryFile(const char* fn);
	protected:
		std::vector<CFMath::Vec3f>		m_vertPos ;
		std::vector<CFMath::Vec3f>		m_vertNor ;
		std::vector<CFMath::Vec3f>		m_vertTan ;
		std::vector<CFMath::Vec4f>		m_vertClr ;
		std::vector<CFMath::Vec2f>		m_vertUV[4] ;

		std::vector<VertBoneWeight>		m_boneWeights ;
		int _readBoneWeightFromFile(FILE*);
		int _writeBoneWeightToFile(FILE*);

		int _readBoneWeightFromXml(TiXmlElement*);
		int _writeBoneWeightToXml(TiXmlElement*);

		std::vector<TriangleGroup>		m_triangleGroups ;

		const int				m_nEditionNum = 1001;

		ModelFileHead			m_fileHead;
		int _writeFileHeadToXml( TiXmlElement* );
		int _readFileHeadFromXml( TiXmlElement* );
	};
}

#endif