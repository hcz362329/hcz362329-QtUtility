#ifndef SELECT_HERO_DEF_H
#define SELECT_HERO_DEF_H
#pragma pack(push,1)
#define HERO_NAME_LEN 16
#define Hero_Column_Count 9
#define IMAGE_LEN 128
#define SKILL_NAME_LEN 64
#define SKILL_INFO_LEN 256
#define Camp_Fixed 1 //阵营固定
#include <QMetaType>
#include <QVector>
enum ECamp
{
	eCampNone=0,
	eCampShu=1,//蜀国
	eCampWei=2,//魏国
};

struct STHero
{
	int nHeroType;
	int nHeroId;
	int nHeroCamp;
	int ulBeginSecond;
	int nStatus;//0可选,1不可选
	wchar_t strHeroName[HERO_NAME_LEN];
	STHero()
	{
		nHeroType = nHeroId = nHeroCamp =ulBeginSecond=nStatus=0;
		memset(strHeroName,0,_countof(strHeroName));
	}
};
Q_DECLARE_METATYPE(STHero);


enum ETableType
{
	eTableTypeNone=0,
};

#pragma pack(pop)


#endif