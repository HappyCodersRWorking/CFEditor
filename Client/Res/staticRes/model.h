#ifndef _CF_RES_MODEL_H_
#define _CF_RES_MODEL_H_

#include <vector>
#include "../../math/cfMath.h"

namespace CFStaticRes
{

	class CModel
	{
	public:
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
		std::vector<CFMath::Vec3f>		m_vertPos;
		std::vector<CFMath::Vec3f>		m_vertNor;
		std::vector<CFMath::Vec3f>		m_vertTan;
		std::vector<CFMath::Vec4f>		m_vertClr;
		std::vector<CFMath::Vec2f>		m_vertUV[4];

		std::vector<VertBoneWeight>		m_boneWeights;
	};
}

#endif