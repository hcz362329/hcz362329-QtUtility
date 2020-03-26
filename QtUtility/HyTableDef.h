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

//�������Դ���һ�����޻�����,���޻����Բ�һ���н������ԣ�EHyType�������ڵ���޻����ʱ����
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
	eCampShu,//���
	eCampWei,//κ��
	eCampZL,//����
	eCampOwned,//��ӵ��
	eCampAll,
};

enum ERace
{
	eRaceQL,//����
	eRaceBH,//�׻�
	eRaceZQ,//��ȸ
	eRaceXW,//����
	eRaceAll,
};

enum EJXShowState
{
	eJXShowStateTable,
	eJXShowStateList,
};

enum EGroup
{
	eGroupColor,//������ɫ����
	eGroupCamp,//������Ӫ
	eGroupRace,//�޻�����
};

struct STJX
{
	int nNum;
	ECamp eCamp;
	QString strJXName;
	QString strJXEng;
	///����ͷ��ͼƬ·��
	QString strImgPath;
	///����ͼ��ͼƬ·��
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