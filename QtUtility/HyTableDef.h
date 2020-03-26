#ifndef HyTableDef_h
#define HyTableDef_h

#include <QString>
#include <QMetaType>
#pragma pack(push,8)

#define Column_Count 4
#define Hy_Row_Count 5
#define JX_Row_Count 7
#define Hy_Table_Show_Count (Column_Count*Hy_Row_Count)
#define Jx_Table_Show_Count (Column_Count*JX_Row_Count)

#define HyWidth 69

enum ETable
{
	ETableNone = -1,
	ETableNormal = 0,
	ETableJX,
	ETableSH
};

//将星属性存在一定有兽魂属性,有兽魂属性不一定有将星属性，EHyType的作用在点击兽魂界面时有用
enum EHyShowType
{
	eHyShowNone = 0,
	eHyShowNormal,
	eHyShowSH,
};

enum EListViewShowType
{
	eListViewShowNone = 0,
	eListViewShowJX,
	eListViewShowSH
};

enum ECamp
{
	eCampShu,//蜀国
	eCampWei,//魏国
	eCampZL,//中立
	eCampOwned,//已拥有
	eCampAll,
};

enum ERace
{
	eRaceQL,//青龙
	eRaceBH,//白虎
	eRaceZQ,//朱雀
	eRaceXW,//玄武
	eRaceAll,
};

enum EJXShowState
{
	eJXShowStateTable,
	eJXShowStateList,
};

enum EGroup
{
	eGroupColor,//魂玉颜色属性
	eGroupCamp,//将星阵营
	eGroupRace,//兽魂种类
};

struct STJX
{
	int nNum;
	ECamp eCamp;
	QString strJXName;
	QString strJXEng;
	///将星头像图片路径
	QString strImgPath;
	///将星图鉴图片路径
	QString strIllustratedImgPath;
	int nLock;
	//QVector<STATIC_EFF> vecEff;
	STJX()
	{
		nNum = 0;
		nLock = 0;
		eCamp = eCampShu;
		strJXName = QString("");
		strImgPath = QString("");
		strIllustratedImgPath = QString("");
	}
};
Q_DECLARE_METATYPE(STJX);

struct STSH
{
	int nNum;
	QString strSHName;
	//QVector<STATIC_EFF> vecSHEff;
	STSH()
	{
		nNum = 0;
		strSHName = QString("");
	}
};
Q_DECLARE_METATYPE(STSH);

#pragma pack(pop)

#endif